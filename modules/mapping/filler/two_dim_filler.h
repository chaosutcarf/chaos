#pragma once

#include "common/type.h"
#include "mapping/data_filler.h"

namespace chaos::mapping {
#define TWO_DIM_INTERFACE(_Override, _Parallel, _FillMode, _GetData) \
  static constexpr bool Override = _Override;                        \
  static constexpr bool CanParallel = _Parallel;                     \
  static constexpr MATRIX_FILL_MODE FillMode = _FillMode;            \
  static constexpr bool CanGetData =                                 \
      _Override && _FillMode == MATRIX_FILL_MODE::FULL && _GetData;

//-> Eigen::DenseBase
template <data_filler_concepts::EigenDenseMatrixBase T,
          MATRIX_FILL_MODE _FillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _Parallel = true, bool _GetData = true>
struct mat_filler_t
    : public two_dim_filler_base<
          mat_filler_t<T, _FillMode, _Override, _Parallel, _GetData>> {
  TWO_DIM_INTERFACE(_Override, _Parallel, _FillMode, _GetData);

  mat_filler_t(T &data) : m_data(data) {}
  inline real_t *data() requires
      data_filler_concepts::CanGetData<mat_filler_t> {
    return m_data.data();
  }
  inline void setZero() { m_data.setZero(); }

  inline index_t _rows() const { return m_data.rows(); }
  inline index_t _cols() const { return m_data.cols(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
#define FILL(r, c, val)                    \
  if constexpr (is_override && Override) { \
    m_data(r, c) = val;                    \
  } else {                                 \
    m_data(r, c) += val;                   \
  }

    if constexpr (FillMode == MATRIX_FILL_MODE::FULL) {
      FILL(r, c, val);
    } else if constexpr (FillMode == MATRIX_FILL_MODE::LOWER) {
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

  template <bool is_override,
            data_filler_concepts::EigenDenseMatrixBase DerivedH>
  inline void _batch_fill(const DerivedH &H) {
#define FILL(H)                             \
  if constexpr (is_override && _Override) { \
    m_data = H;                             \
  } else {                                  \
    m_data += H;                            \
  }

    if constexpr (FillMode == MATRIX_FILL_MODE::FULL) {
      FILL(H);
    } else if constexpr (FillMode == MATRIX_FILL_MODE::LOWER) {
      FILL(H.template triangularView<Eigen::Lower>());
    } else {
      FILL(H.template triangularView<Eigen::Upper>());
    }

#undef FILL
  }

 private:
  T &m_data;
};

template <data_filler_concepts::EigenDenseMatrixBase T, bool _Override = true,
          bool _Parallel = true, bool _GetData = true>
struct gra_filler_t : public two_dim_filler_base<
                          gra_filler_t<T, _Override, _Parallel, _GetData>> {
  static constexpr bool Override = _Override;
  static constexpr bool CanParallel = _Parallel;
  static constexpr bool CanGetData = _Override && _GetData;

  gra_filler_t(T &data) : m_data(data) {}
  inline real_t *data() requires
      data_filler_concepts::CanGetData<gra_filler_t> {
    return m_data.data();
  }
  inline void setZero() { m_data.setZero(); }

  inline index_t _rows() const { return 1; }
  inline index_t _cols() const { return m_data.size(); }

  template <bool is_override>
  inline void _fill(index_t, index_t c, real_t val) {
    if constexpr (is_override && Override) {
      m_data[c] = val;
    } else {
      m_data[c] += val;
    }
  }

  template <bool is_override, data_filler_concepts::UnaryAccessible DerivedV>
  inline void _batch_fill(const DerivedV &V) {
#pragma omp parallel for
    for (index_t i = 0; i < V.size(); ++i) {
      _fill(0, i, V[i]);
    }
  }

 private:
  T &m_data;
};

//-> Eigen::SparseBase
template <data_filler_concepts::EigenSparseMatrixBase T,
          MATRIX_FILL_MODE _FillMode = MATRIX_FILL_MODE::FULL,
          bool _Override = true, bool _Parallel = true>
struct spmat_filler_t
    : public two_dim_filler_base<
          spmat_filler_t<T, _FillMode, _Override, _Parallel>> {
  TWO_DIM_INTERFACE(_Override, _Parallel, _FillMode, false);

  spmat_filler_t(T &data) : m_data(data) {}
  inline void setZero() {
    //-> keep pattern.
    std::fill_n(m_data.valuePtr(), m_data.nonZeros(), 0);
  }

  inline index_t _rows() const { return m_data.rows(); }
  inline index_t _cols() const { return m_data.cols(); }

  template <bool is_override>
  inline void _fill(index_t r, index_t c, real_t val) {
    if constexpr (is_override && Override) {
      m_data.coeffRef(r, c) = val;
    } else {
      m_data.CoeffRef(r, c) += val;
    }
  }

 private:
  T &m_data;
};

//-> coo_list
template <typename T, MATRIX_FILL_MODE _FillMode = MATRIX_FILL_MODE::FULL>
struct coo_filler_t : public two_dim_filler_base<coo_filler_t<T, _FillMode>> {
  TWO_DIM_INTERFACE(false, false, _FillMode, false);
  coo_filler_t(T &data, index_t rows, index_t cols)
      : m_data(data), m_rows(rows), m_cols(cols) {}

  inline index_t _rows() const { return m_rows; }
  inline index_t _cols() const { return m_cols; }
  inline void setZero() const { m_data.clear(); }

  template <bool>
  inline void _fill(index_t r, index_t c, real_t val) {
    if constexpr (FillMode == MATRIX_FILL_MODE::FULL) {
      m_data.emplace_back(r, c, val);
    } else if constexpr (FillMode == MATRIX_FILL_MODE::LOWER) {
      if (r >= c) {
        m_data.emplace_back(r, c, val);
      }
    } else {
      if (r <= c) {
        m_data.emplace_back(r, c, val);
      }
    }
  }

 private:
  T &m_data;
  index_t m_rows, m_cols;
};
}  // namespace chaos::mapping
