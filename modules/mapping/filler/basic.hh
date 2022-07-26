#pragma once

#include "common/type.h"
#include "mapping/filler.hh"
namespace chaos::mapping {
#define SIMPLE_BATCH_FILL(T)                                         \
  template <bool isOverride, typename U>                             \
  inline void fill(const U &rhs)                                     \
      FILLER_FILL_REQUIRES &&AssignableConcept<isOverride, T &, U> { \
    if constexpr (isOverride) {                                      \
      m_data = rhs;                                                  \
    } else {                                                         \
      m_data += rhs;                                                 \
    }                                                                \
  }
// scalar wrapper.
template <ArithmeticType T, bool Override, bool AllowGetData>
struct ScalarFillerCore {
  using Traits = OneDimTraits<Override, AllowGetData, false>;
  ScalarFillerCore(T &data) : m_data(data) {}
  inline void setZero() { m_data = 0; }
  static constexpr index_t size() { return 1; }
  template <bool isOverride>
  inline void fill(index_t, real_t val) FILLER_FILL_REQUIRES {
    fill<isOverride>(val);
  }

  SIMPLE_BATCH_FILL(T);
  inline T *data() FILLER_DATA_REQUIRES { return &m_data; }

 private:
  T &m_data;
};

template <ArithmeticType T, bool Override = true, bool AllowGetData = true>
auto ScalarFiller(T &data) {
  return OneDimFiller<ScalarFillerCore<T, Override, AllowGetData>>(data);
}

template <typename T, bool Override = true, bool AllowGetData = true>
struct VectorFillerCore {
  using Traits = OneDimTraits<Override, AllowGetData, true>;
  VectorFillerCore(T &data) : m_data(data) {
    //-> data should has setZero/size/=/+=
  }
  inline void setZero() { m_data.setZero(); }
  inline index_t size() const { return m_data.size(); }
  template <bool isOverride>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (isOverride) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }
  SIMPLE_BATCH_FILL(T);
  inline auto data() FILLER_DATA_REQUIRES { return m_data.data(); }

 private:
  T &m_data;
};
template <typename T, bool Override = true, bool AllowGetData = true>
auto VectorFiller(T &data) {
  return OneDimFiller<VectorFillerCore<T, Override, AllowGetData>>(data);
}

#define MAT_EACH_FILL(r, c, val)                                 \
  if constexpr (MatFillMode == MATRIX_FILL_MODE::FULL) {         \
    FILL(r, c, val);                                             \
  } else if constexpr (MatFillMode == MATRIX_FILL_MODE::LOWER) { \
    if (r >= c) {                                                \
      FILL(r, c, val);                                           \
    }                                                            \
  } else if constexpr (MatFillMode == MATRIX_FILL_MODE::UPPER) { \
    if (r <= c) {                                                \
      FILL(r, c, val);                                           \
    }                                                            \
  }

template <typename T, MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::FULL,
          bool Override = true, bool AllowGetData = true>
struct DenseMatrixFillerCore {
  using Traits = TwoDimTraits<MatFillMode, Override, AllowGetData, true>;
  DenseMatrixFillerCore(T &data) : m_data(data) {
    //-> data should has setZero/rows/cols/=/+=
  }
  inline void setZero() { m_data.setZero(); }
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }
  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
#define FILL(r, c, val)       \
  if constexpr (isOverride) { \
    m_data(r, c) = val;       \
  } else {                    \
    m_data(r, c) += val;      \
  }
    MAT_EACH_FILL(r, c, val);
#undef FILL
  }
  template <bool isOverride, EigenDenseMatrixConcept U>
  inline void fill(const U &rhs)
      FILLER_FILL_REQUIRES &&AssignableConcept<isOverride, T, U> {
#define FILL(H)                           \
  if constexpr (isOverride && Override) { \
    m_data = H;                           \
  } else {                                \
    m_data += H;                          \
  }
    if constexpr (MatFillMode == MATRIX_FILL_MODE::FULL) {
      FILL(rhs);
    } else if constexpr (MatFillMode == MATRIX_FILL_MODE::LOWER) {
      FILL(rhs.template triangularView<Eigen::Lower>());
    } else if constexpr (MatFillMode == MATRIX_FILL_MODE::UPPER) {
      FILL(rhs.template triangularView<Eigen::Upper>());
    }
#undef FILL
  }
  inline auto data() FILLER_DATA_REQUIRES { return m_data.data(); }

 private:
  T &m_data;
};
template <typename T, MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::FULL,
          bool Override = true, bool AllowGetData = true>
auto DenseMatrixFiller(T &data) {
  return TwoDimFiller<
      DenseMatrixFillerCore<T, MatFillMode, Override, AllowGetData>>(data);
}
//-> transpose the vector.
template <typename T, bool Override = true, bool AllowGetData = true>
struct GraFillerCore {
  using Traits = TwoDimTraits<MATRIX_FILL_MODE::FULL, Override, AllowGetData>;
  GraFillerCore(T &data) : m_data(data) {}
  inline void setZero() { m_data.setZero(); }
  inline index_t rows() const { return 1; }
  inline index_t cols() const { return m_data.size(); }
  template <bool isOverride>
  inline void fill(index_t, index_t c, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (isOverride) {
      m_data[c] = val;
    } else {
      m_data[c] += val;
    }
  }

  template <bool isOverride, UnaryAccessible U>
  inline void fill(const U &rhs) FILLER_FILL_REQUIRES {
#pragma omp parallel for
    for (index_t i = 0; i < rhs.size(); ++i) {
      fill<isOverride>(0, i, rhs[i]);
    }
  }

  inline auto data() FILLER_DATA_REQUIRES { return m_data.data(); }

 private:
  T &m_data;
};
template <typename T, bool Override = true, bool AllowGetData = true>
auto GraFiller(T &data) {
  return TwoDimFiller<GraFillerCore<T, Override, AllowGetData>>(data);
}
//-> SparseMatrix.
template <EigenSparseMatrixConcept T,
          MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::FULL,
          bool Override = true>
struct SparseMatrixFillerCore {
  using Traits = TwoDimTraits<MatFillMode, Override, false, true>;
  SparseMatrixFillerCore(T &data) : m_data(data) {}
  inline void setZero() {
    //-> keep the pattern.
    std::fill_n(m_data.valuePtr(), m_data.nonZeros(), 0);
  }
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }
  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
#define FILL(r, c, val)           \
  if constexpr (isOverride) {     \
    m_data.coeffRef(r, c) = val;  \
  } else {                        \
    m_data.coeffRef(r, c) += val; \
  }
    MAT_EACH_FILL(r, c, val);
#undef FILL
  }

 private:
  T &m_data;
};
template <EigenSparseMatrixConcept T,
          MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::FULL,
          bool Override = true>
auto SparseMatrixFiller(T &data) {
  return TwoDimFiller<SparseMatrixFillerCore<T, MatFillMode, Override>>(data);
}
//-> COO.
template <typename T, MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::UPPER>
struct COOFillerCore {
  using Traits = TwoDimTraits<MatFillMode, false, false, false>;
  COOFillerCore(T &data, index_t rows, index_t cols)
      : m_data(data), m_rows(rows), m_cols(cols) {}
  inline index_t rows() const { return m_rows; }
  inline index_t cols() const { return m_cols; }
  inline void setZero() const { m_data.clear(); }
  template <bool isOverride>
  inline void fill(index_t r, index_t c, real_t val) requires isOverride {
    static_assert(isOverride, "only support override mode!");
#define FILL(r, c, val) m_data.emplace_back(r, c, val);
    MAT_EACH_FILL(r, c, val);
#undef FILL
  }

 private:
  T &m_data;
  index_t m_rows, m_cols;
};
template <typename T, MATRIX_FILL_MODE MatFillMode = MATRIX_FILL_MODE::UPPER>
auto COOFiller(T &data, index_t rows, index_t cols) {
  return TwoDimFiller<COOFillerCore<T, MatFillMode>>(data, rows, cols);
}
#undef MAT_EACH_FILL
#undef SIMPLE_BATCH_FILL
}  // namespace chaos::mapping
