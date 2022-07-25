#pragma once

#include "mapping/data_filler.h"

namespace chaos::mapping {
template <ArithmeticType T, bool _Override = true, bool _AllowGetData = true>
struct scalar_filler_t {
  using Traits = OneDimTraits<_Override, _AllowGetData>;

  scalar_filler_t(T &data) : m_data(data) {}
  inline void setZero() { m_data = 0; }
  inline index_t size() const { return 1; }
  template <bool is_override>
  inline void fill(index_t, real_t val) FILLER_FILL_REQUIRES {
    fill<is_override>(val);
  }
  template <bool is_override, ArithmeticType U>
  inline void fill(const U &val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data = val;
    } else {
      m_data += val;
    }
  }

  inline T *data() FILLER_DATA_REQUIRES { return &m_data; }

 private:
  T &m_data;
};

template <UnaryAssignable T, bool _Override = true, bool _AllowGetData = true,
          bool _Parallel = true>
struct vector_filler_t {
  using Traits = OneDimTraits<_Override, _AllowGetData, _Parallel>;
  vector_filler_t(T &data) : m_data(data) {}
  //-> TODO. check setZero interface.
  inline void setZero() { m_data.setZero(); }
  //-> TODO. check data interface.
  inline auto data() FILLER_DATA_REQUIRES { return m_data.data(); }
  inline index_t size() const { return m_data.size(); }

  template <bool is_override>
  inline void fill(index_t p, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }

  template <bool is_override, UnaryAccessible DerivedV>
  inline void fill(const DerivedV &vec) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data = vec;
    } else {
      m_data += vec;
    }
  }

 private:
  T &m_data;
};

//->Eigen::DenseBase
template <EigenDenseMatrixConcept T,
          MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _Parallel = true,
          bool _AllowGetData = true>
struct mat_filler_t {
  using Traits =
      TwoDimTraits<_MatFillMode, _Override, _AllowGetData, _Parallel>;
  mat_filler_t(T &data) : m_data(data) {}
  inline void setZero() { m_data.setZero(); }
  inline auto data() FILLER_DATA_REQUIRES { return m_data.data(); }
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }

  template <bool is_override>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
#define FILL(r, c, val)        \
  if constexpr (is_override) { \
    m_data(r, c) = val;        \
  } else {                     \
    m_data(r, c) += val;       \
  }
    if constexpr (_MatFillMode == MATRIX_FILL_MODE::FULL) {
      FILL(r, c, val);
    } else if constexpr (_MatFillMode == MATRIX_FILL_MODE::LOWER) {
      if (r >= c) {
        FILL(r, c, val);
      }
    } else {
      if (r <= c) {
        FILL(r, c, val);
      }
    }
#undef FILL
  }

  template <bool is_override, EigenDenseMatrixConcept DerivedH>
  inline void fill(const DerivedH &H) FILLER_FILL_REQUIRES {
#define FILL(H)                             \
  if constexpr (is_override && _Override) { \
    m_data = H;                             \
  } else {                                  \
    m_data += H;                            \
  }

    if constexpr (_MatFillMode == MATRIX_FILL_MODE::FULL) {
      FILL(H);
    } else if constexpr (_MatFillMode == MATRIX_FILL_MODE::LOWER) {
      FILL(H.template triangularView<Eigen::Lower>());
    } else {
      FILL(H.template triangularView<Eigen::Upper>());
    }
#undef FILL
  }

 private:
  T &m_data;
};

template <EigenSparseMatrixConcept T,
          MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _Parallel = true>
struct spmat_filler_t {
  using Traits = TwoDimTraits<_MatFillMode, _Override, false, _Parallel>;
  spmat_filler_t(T &data) : m_data(data) {}
  inline void setZero() {
    //-> keep pattern.
    std::fill_n(m_data.valuePtr(), m_data.nonZeros(), 0);
  }
  inline index_t rows() const { return m_data.rows(); }
  inline index_t cols() const { return m_data.cols(); }

  template <bool is_override>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
    if constexpr (is_override) {
      m_data.coeffRef(r, c) = val;
    } else {
      m_data.coeffRef(r, c) += val;
    }
  }

 private:
  T &m_data;
};
//-> coo_list
template <typename T, MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL>
struct coo_filler_t {
  using Traits = TwoDimTraits<_MatFillMode, false, false, false>;
  coo_filler_t(T &data, index_t rows, index_t cols)
      : m_data(data), m_rows(rows), m_cols(cols) {}

  inline index_t rows() const { return m_rows; }
  inline index_t cols() const { return m_cols; }
  inline void setZero() const { m_data.clear(); }

  template <bool is_override>
  inline void fill(index_t r, index_t c, real_t val) FILLER_FILL_REQUIRES {
#define FILL(r, c, val) m_data.emplace_back(r, c, val);
    if constexpr (_MatFillMode == MATRIX_FILL_MODE::FULL) {
      FILL(r, c, val);
    } else if constexpr (_MatFillMode == MATRIX_FILL_MODE::LOWER) {
      if (r >= c) {
        FILL(r, c, val);
      }
    } else {
      if (r <= c) {
        FILL(r, c, val);
      }
    }
#undef FILL
  }

 private:
  T &m_data;
  index_t m_rows, m_cols;
};
}  // namespace chaos::mapping
