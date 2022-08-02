#pragma once

#include "mapping/filler.hh"

namespace chaos::mapping {
#define CONSTEXPR_VAR(name) static constexpr decltype(_##name) name{_##name};

//-> scalar filler.
template <ArithmeticType T, bool _Override = true>
struct ScalarFiller {
  CONSTEXPR_VAR(Override);
  static constexpr bool AllowGetData{true};
  using Traits = FillerTraits<ScalarFiller<T, Override>>;
  using Scalar = T;

  ScalarFiller(T &data) : m_data(data) {}
  static constexpr index_t size() { return 1; }
  static constexpr index_t cols() { return 1; }
  static constexpr index_t rows() { return 1; }
  inline Scalar *data() FILLER_DATA_REQUIRES { return &m_data; }
  inline void setZero() { m_data = 0; }

  template <bool isOverride = Override>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    CHECK_1D_FILL(p, Override, isOverride);
    _fill<isOverride>(val);
  }

  template <bool isOverride = Override>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
    CHECK_2D_FILL(r, c, Override, isOverride);
    _fill<isOverride>(val);
  }

  template <bool isOverride = Override, typename U>
  inline void fill(const U &rhs) FILLER_FILL_REQUIRES {
    constexpr bool isScalar = ArithmeticType<U>;
    constexpr bool isVector = UnaryAccessible<U>;
    constexpr bool isMatrix = BinaryAccessible<U>;
    static_assert(
        isScalar || isVector || isMatrix,
        "U should be ArithmeticType | UnaryAccessible | BinaryAccessible");
    if constexpr (isScalar) {
      _fill<isOverride>(rhs);
    } else if constexpr (isVector) {
      CHAOS_DEBUG_ASSERT(rhs.size() == 1, rhs.size());
      _fill<isOverride>(rhs[0]);
    } else if constexpr (isMatrix) {
      CHAOS_DEBUG_ASSERT(rhs.rows() == 1 && rhs.cols() == 1, rhs.rows(),
                         rhs.cols());
      _fill<isOverride>(rhs(0, 0));
    }
  }

 private:
  template <bool isOverride>
  inline void _fill(real_t val) FILLER_FILL_REQUIRES {
    if constexpr (isOverride) {
      m_data = val;
    } else {
      m_data += val;
    }
  }
  T &m_data;
};

//-> vector filler.
template <typename T, bool _Override = true>
struct VectorFiller {
  CONSTEXPR_VAR(Override);
  static constexpr bool CanParallel{true};
  static constexpr bool AllowGetData{HasFunctionData<T>};
  using Scalar = typename T::Scalar;
  using Traits = FillerTraits<VectorFiller<T, Override>>;

  VectorFiller(T &data) : m_data(data) {}
  inline Scalar *data() FILLER_DATA_REQUIRES { return m_data.data(); }
  inline index_t size() const { return m_data.size(); }
  inline void setZero() { m_data.setZero(); }

  template <bool isOverride = Override>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    CHECK_1D_FILL(p, Override, isOverride);
    if constexpr (isOverride) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }

 private:
  T &m_data;
};

//-> matrix filler.
#define MAT_EACH_FILL(MatFillMode, r, c, cmd)                    \
  if constexpr (MatFillMode == MATRIX_FILL_MODE::FULL) {         \
    cmd;                                                         \
  } else if constexpr (MatFillMode == MATRIX_FILL_MODE::LOWER) { \
    if (r >= c) {                                                \
      cmd;                                                       \
    }                                                            \
  } else if constexpr (MatFillMode == MATRIX_FILL_MODE::UPPER) { \
    if (r <= c) {                                                \
      cmd;                                                       \
    }                                                            \
  }
//->FIXME: if the type is sparsematrix,
//->       then the pattern should prepared before,
//->       otherwise, parallel is not
template <typename T, MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _CanParallel = true>
requires EigenDenseMatrixConcept<T> || EigenSparseMatrixConcept<T>
struct MatrixFiller {
  CONSTEXPR_VAR(MatFillMode);
  CONSTEXPR_VAR(Override);
  CONSTEXPR_VAR(CanParallel);
  static constexpr bool isDense{EigenDenseMatrixConcept<T>};
  static constexpr bool AllowGetData{HasFunctionData<T>};
  using Scalar = typename T::Scalar;
  using Traits =
      FillerTraits<MatrixFiller<T, MatFillMode, Override, CanParallel>>;

  MatrixFiller(T &data) : m_data(data) {}
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }
  inline Scalar *data() FILLER_DATA_REQUIRES { return m_data.data(); }
  inline void setZero() {
    if constexpr (isDense) {
      m_data.setZero();
    } else {
      //-> keep the pattern.
      std::fill_n(m_data.valuePtr(), m_data.nonZeros(), 0);
    }
  }

  template <bool isOverride = Override>
  inline void fill(index_t r, index_t c, real_t val) {
    CHECK_2D_FILL(r, c, Override, isOverride);
    MAT_EACH_FILL(MatFillMode, r, c, _fill<isOverride>(r, c, val););
  }

 private:
  template <bool isOverride>
  inline void _fill(index_t r, index_t c, real_t val) {
    if constexpr (isOverride) {
      if constexpr (isDense) {
        m_data(r, c) = val;
      } else {
        m_data.coeffRef(r, c) = val;
      }
    } else {
      if constexpr (isDense) {
        m_data(r, c) += val;
      } else {
        m_data.coeffRef(r, c) += val;
      }
    }
  }

  T &m_data;
};

//-> coo filler.
template <typename T, MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL>
struct COOFiller {
  CONSTEXPR_VAR(MatFillMode);
  static constexpr bool Override{false};
  static constexpr bool CanParallel{false};

  COOFiller(T &data, index_t rows, index_t cols)
      : m_data(data), m_rows(rows), m_cols(cols) {}
  inline index_t rows() const { return m_rows; }
  inline index_t cols() const { return m_cols; }
  inline void setZero() { m_data.clear(); }

  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) {
    CHECK_2D_FILL(r, c, Override, isOverride);
    MAT_EACH_FILL(MatFillMode, r, c, _fill(r, c, val));
  }

 private:
  inline void _fill(index_t r, index_t c, real_t val) {
    m_data.emplace_back(r, c, val);
  }
  T &m_data;
  index_t m_rows, m_cols;
};
#undef MAT_EACH_FILL
}  // namespace chaos::mapping
