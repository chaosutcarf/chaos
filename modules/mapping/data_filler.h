#pragma once

#include <omp.h>

#include <set>
#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_traits.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {
/*
 * fill_mode
 * override_mode
 * can_parallel
 * _fill_impl
 * _batch_fill [optional]
 * data [optional]
 */
template <typename Derived>
struct one_dim_filler_base {
  one_dim_filler_base() {
    static_assert(details::data_filler_traits::has_one_dim_fill_impl_v<Derived>,
                  "one dim filler should provide _fill_impl(id, val)");
    static_assert(
        details::data_filler_traits::has_member_override_mode_v<Derived>,
        "one dim filler should provide override_mode");
  }

  CRTP_derived_interface(Derived, one_dim_filler_base);
  //-> interface.
  inline void fill(index_t pos, real_t val) {
    CHAOS_DEBUG_ASSERT(pos < size());
    derived()._fill_impl(pos, val);
  }

  template <typename DerivedV>
  void batch_fill(const DerivedV &vec);

  inline index_t size() const { return derived().size(); }
};

template <typename Derived>
struct two_dim_filler_base {
  two_dim_filler_base() {
    static_assert(details::data_filler_traits::has_two_dim_fill_impl_v<Derived>,
                  "two dim filler should provide _fill_impl(p, q, val)");
    static_assert(details::data_filler_traits::has_member_fill_mode_v<Derived>,
                  "two dim filler should provide fill mode: LOWER/UPPER/FULL");
    static_assert(
        details::data_filler_traits::has_member_override_mode_v<Derived>,
        "one dim filler should provide override_mode");
  }
  //-> has traits: fill.upper/lower/full
  CRTP_derived_interface(Derived, two_dim_filler_base);
  //-> interface.
  inline void fill(index_t p, index_t q, real_t val) {
    CHAOS_DEBUG_ASSERT(p < rows() && q < cols());
    derived()._fill_impl(p, q, val);
  }

  template <typename DerivedH>
  void batch_fill(const DerivedH &H);

  inline index_t rows() const { return derived().rows(); }
  inline index_t cols() const { return derived().cols(); }
};

////////////////////////////////////////////////////////////////////////
//                       some filler type                             //
////////////////////////////////////////////////////////////////////////
#define ONE_DIM_INTERFACE(Override, Parallel, Getdata)      \
  static constexpr bool override_mode = Override;           \
  static constexpr bool can_parallel = Parallel;            \
  static constexpr bool can_get_data = Override && Getdata; \
  inline index_t size() const;                              \
  inline void _fill_impl(index_t p, real_t val);

template <typename T, bool Override = true, bool Parallel = true,
          bool Getdata = true>
struct one_dim_filler_t
    : public one_dim_filler_base<
          one_dim_filler_t<T, Override, Parallel, Getdata>> {
  one_dim_filler_t(T &data);
  ONE_DIM_INTERFACE(Override, Parallel, Getdata);

  template <bool _1 = override_mode, std::enable_if_t<_1 == true, bool> = true,
            bool _2 = can_get_data, std::enable_if_t<_2 == true, bool> = true>
  inline real_t *data();

 private:
  T &m_data;
};

#define TWO_DIM_INTERFACE(Override, Parallel, Fillmode, Getdata)  \
  static constexpr bool override_mode = Override;                 \
  static constexpr bool can_parallel = Parallel;                  \
  static constexpr MATRIX_FILL_MODE fill_mode = Fillmode;         \
  static constexpr bool can_get_data =                            \
      fill_mode == MATRIX_FILL_MODE::FULL && Override && Getdata; \
  inline index_t rows() const;                                    \
  inline index_t cols() const;                                    \
  inline void _fill_impl(index_t p, index_t q, real_t val);

//-> Eigen::DenseBase.
template <typename T, MATRIX_FILL_MODE Fillmode = MATRIX_FILL_MODE::FULL,
          bool Override = true, bool Parallel = true, bool Getdata = true>
struct mat_filler_t
    : public two_dim_filler_base<
          mat_filler_t<T, Fillmode, Override, Parallel, Getdata>> {
  mat_filler_t(T &data);

  TWO_DIM_INTERFACE(Override, Parallel, Fillmode, Getdata);
  template <bool _1 = override_mode, std::enable_if_t<_1 == true, bool> = true,
            bool _2 = can_get_data, std::enable_if_t<_2 == true, bool> = true,
            MATRIX_FILL_MODE _3 = Fillmode,
            std::enable_if_t<_3 == MATRIX_FILL_MODE::FULL, bool> = true>
  inline real_t *data();

 private:
  T &m_data;
};
template <typename T, bool Override = true, bool Parallel = true,
          bool Getdata = true>
struct gra_filler_t
    : public two_dim_filler_base<gra_filler_t<T, Override, Parallel, Getdata>> {
  gra_filler_t(T &data);

  TWO_DIM_INTERFACE(Override, Parallel, MATRIX_FILL_MODE::FULL, Getdata);
  template <bool _1 = override_mode, std::enable_if_t<_1 == true, bool> = true,
            bool _2 = can_get_data, std::enable_if_t<_2 == true, bool> = true>
  inline real_t *data();

 private:
  T &m_data;
};

//-> Eigen::SparseBase.
template <typename T, MATRIX_FILL_MODE Fillmode = MATRIX_FILL_MODE::FULL,
          bool Override = true, bool Parallel = true>
struct spmat_filler_t : public two_dim_filler_base<
                            spmat_filler_t<T, Fillmode, Override, Parallel>> {
  spmat_filler_t(T &data);
  TWO_DIM_INTERFACE(Override, Parallel, Fillmode, false);

 private:
  T &m_data;
};

//-> coo_list.
template <typename T, MATRIX_FILL_MODE Fillmode = MATRIX_FILL_MODE::FULL>
struct coo_filler_t : public two_dim_filler_base<coo_filler_t<T, Fillmode>> {
  coo_filler_t(T &data, index_t rows, index_t cols);
  TWO_DIM_INTERFACE(false, false, Fillmode, false);

 private:
  T &m_data;
  index_t m_rows, m_cols;
};

//-> Wrapper.
// #define OBF_T()
//   template <typename U, typename _ = T,
//             std::enable_if_t<
//                 details::data_filler_traits::has_override_batch_fill_v<_>,
//                 bool> = true>
//   inline void _batch_fill(const U &u);
#define DATA_T()                                                          \
  template <typename _1 = T,                                              \
            std::enable_if_t<details::data_filler_traits::has_data_v<_1>, \
                             bool> = true>                                \
  inline real_t *data();

template <typename T>
struct offset_1d_filler_t : public one_dim_filler_base<offset_1d_filler_t<T>> {
  offset_1d_filler_t(T &filler, index_t offset);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, false);

 private:
  T &filler;
  index_t offset;
};

template <typename T>
struct offset_2d_filler_t : public two_dim_filler_base<offset_2d_filler_t<T>> {
  offset_2d_filler_t(T &filler, index_t off_r, index_t off_c);
  offset_2d_filler_t(T &filler, index_t off)
      : offset_2d_filler_t(filler, off, off) {}
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode, false);

 private:
  T &filler;
  index_t off_r, off_c;
};

template <typename T, typename IndexList>
struct idmap_1d_filler_t
    : public two_dim_filler_base<idmap_1d_filler_t<T, IndexList>> {
  idmap_1d_filler_t(T &filler, const IndexList &idmap);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, false);

 private:
  T &filler;
  const IndexList &idmap;
};

template <typename T, typename IndexList>
struct idmap_2d_filler_t
    : public two_dim_filler_base<idmap_2d_filler_t<T, IndexList>> {
  idmap_2d_filler_t(T &filler, const IndexList &idmap);
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode, false);

 private:
  T &filler;
  const IndexList &idmap;
};

template <typename T>
struct weight_1d_filler_t : public two_dim_filler_base<weight_1d_filler_t<T>> {
  weight_1d_filler_t(T &filler, real_t w);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, T::can_get_data);

 private:
  T &filler;
  real_t w;
};

template <typename T>
struct weight_2d_filler_t : public two_dim_filler_base<weight_2d_filler_t<T>> {
  weight_2d_filler_t(T &filler, real_t w);
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode,
                    T::can_get_data);

 private:
  T &filler;
  real_t w;
};

////////////////////////////////////////////////////////////////////////
//                          template implementation                   //
////////////////////////////////////////////////////////////////////////

template <typename Derived>
template <typename DerivedV>
inline void one_dim_filler_base<Derived>::batch_fill(const DerivedV &vec) {
  //-> check DerivedV has interface: size(), operator[]
  static_assert(details::data_filler_traits::has_size_v<DerivedV> &&
                    details::data_filler_traits::has_unary_access_v<DerivedV>,
                "DerivedV should has interface: size() and operator[i]");
  CHAOS_ASSERT(vec.size() == size(), vec.size(), size());
  //-> check derived() has _batch_fill or not.
  if constexpr (details::data_filler_traits::has_override_batch_fill_v<
                    Derived>) {
    derived().template _batch_fill(vec);
  } else {
    //-> if not exist, simply for loop to fill.
#define RUN()                            \
  for (index_t i = 0; i < size(); ++i) { \
    derived()._fill_impl(i, vec[i]);     \
  }
    if constexpr (Derived::can_parallel) {
#pragma omp parallel for default(none) shared(vec)
      RUN();
    } else {
      RUN();
    }
#undef RUN
  }
}

template <typename Derived>
template <typename DerivedH>
inline void two_dim_filler_base<Derived>::batch_fill(const DerivedH &H) {
  //-> H should has rows()/cols() and can be access by(i, j).
  static_assert(details::data_filler_traits::has_rows_v<DerivedH> &&
                    details::data_filler_traits::has_cols_v<DerivedH> &&
                    details::data_filler_traits::has_binary_access_v<DerivedH>,
                "DerivedH should has interface: rows(),cols(), operator(i, j)");
  CHAOS_ASSERT(H.rows() == rows() && H.cols() == cols(), H.rows(), H.cols(),
               rows(), cols());
  //-> check derived() has _batch_fill or not.
  if constexpr (details::data_filler_traits::has_override_batch_fill_v<
                    Derived>) {
    derived().template _batch_fill(H);
  } else {
    //-> default behaviour.
#define RUN()                                                             \
  for (index_t i = 0; i < rows(); ++i) {                                  \
    index_t j, end;                                                       \
    if constexpr (Derived::fill_mode == MATRIX_FILL_MODE::FULL) {         \
      j = 0, end = cols();                                                \
    } else if constexpr (Derived::fill_mode == MATRIX_FILL_MODE::LOWER) { \
      j = 0, end = i + 1;                                                 \
    } else {                                                              \
      j = i, end = cols();                                                \
    }                                                                     \
    for (; j < end; ++j) {                                                \
      derived()._fill_impl(i, j, H(i, j));                                \
    }                                                                     \
  }
    if constexpr (Derived::can_parallel) {
#pragma omp parallel for default(none) shared(H)
      RUN();
    } else {
      RUN();
    }
#undef RUN
  }
}

////////////////////////////////////////////////////////////////////////
//                    one_dim_filler implementation                   //
////////////////////////////////////////////////////////////////////////
#define ONE_DIM_WRAPPER_CHECK()                               \
  static_assert(std::is_base_of_v<one_dim_filler_base<T>, T>, \
                "Filler should be one_dim_filler_base!");
#define TWO_DIM_WRAPPER_CHECK()                               \
  static_assert(std::is_base_of_v<two_dim_filler_base<T>, T>, \
                "Filler should be two_dim_filler_base!");
template <typename T>
offset_1d_filler_t<T>::offset_1d_filler_t(T &filler, index_t offset)
    : filler(filler), offset(offset) {
  ONE_DIM_WRAPPER_CHECK();
  CHAOS_DEBUG_ASSERT(offset < filler.size(), offset, filler.size());
}

template <typename T>
inline index_t offset_1d_filler_t<T>::size() const {
  return filler.size() - offset;
}

template <typename T>
inline void offset_1d_filler_t<T>::_fill_impl(index_t p, real_t val) {
  filler._fill_impl(p + offset, val);
}

template <typename T>
offset_2d_filler_t<T>::offset_2d_filler_t(T &filler, index_t off_r,
                                          index_t off_c)
    : filler(filler), off_r(off_r), off_c(off_c) {
  TWO_DIM_WRAPPER_CHECK();
  CHAOS_DEBUG_ASSERT(off_r < filler.rows() && off_c < filler.cols(), off_r,
                     off_c, filler.rows(), filler.cols());
}

template <typename T>
inline index_t offset_2d_filler_t<T>::rows() const {
  return filler.rows() - off_r;
}
template <typename T>
inline index_t offset_2d_filler_t<T>::cols() const {
  return filler.cols() - off_c;
}

template <typename T>
inline void offset_2d_filler_t<T>::_fill_impl(index_t p, index_t q,
                                              real_t val) {
  filler._fill_impl(p + off_r, q + off_c, val);
}

#ifndef NDEBUG
#define IDMAP_CHECK()                                                 \
  static_assert(                                                      \
      details::data_filler_traits::has_size_v<IndexList> &&           \
          details::data_filler_traits::has_unary_access_v<IndexList>, \
      "idmap should has size and can unary access");                  \
  std::set<index_t> idset;                                            \
  index_t _max = 0;                                                   \
  for (size_t i = 0; i < idmap.size(); ++i) {                         \
    if (idmap[i] < _max) {                                            \
      _max = idmap[i];                                                \
    }                                                                 \
    idset.insert(idmap[i]);                                           \
  }                                                                   \
  CHAOS_DEBUG_ASSERT(idset.size() == idmap.size());

#else
#define IDMAP_CHECK()                                                 \
  static_assert(                                                      \
      details::data_filler_traits::has_size_v<IndexList> &&           \
          details::data_filler_traits::has_unary_access_v<IndexList>, \
      "idmap should has size and can unary access");
#endif

template <typename T, typename IndexList>
idmap_1d_filler_t<T, IndexList>::idmap_1d_filler_t(T &filler,
                                                   const IndexList &idmap)
    : filler(filler), idmap(idmap) {
  ONE_DIM_WRAPPER_CHECK();
  IDMAP_CHECK();
#ifndef NDEBUG
  CHAOS_DEBUG_ASSERT(_max < filler.size());
#endif
}

template <typename T, typename IndexList>
inline index_t idmap_1d_filler_t<T, IndexList>::size() const {
  return idmap.size();
}

template <typename T, typename IndexList>
inline void idmap_1d_filler_t<T, IndexList>::_fill_impl(index_t p, real_t val) {
  filler.fill(idmap[p], val);
}

template <typename T, typename IndexList>
idmap_2d_filler_t<T, IndexList>::idmap_2d_filler_t(T &filler,
                                                   const IndexList &idmap)
    : filler(filler), idmap(idmap) {
  TWO_DIM_WRAPPER_CHECK();
  IDMAP_CHECK();
#ifndef NDEBUG
  CHAOS_DEBUG_ASSERT(_max < filler.rows() && _max < filler.cols(), _max,
                     filler.cols(), filler.rows());
#endif
}

template <typename T, typename IndexList>
inline index_t idmap_2d_filler_t<T, IndexList>::rows() const {
  return idmap.size();
}

template <typename T, typename IndexList>
inline index_t idmap_2d_filler_t<T, IndexList>::cols() const {
  return idmap.size();
}
template <typename T, typename IndexList>
inline void idmap_2d_filler_t<T, IndexList>::_fill_impl(index_t p, index_t q,
                                                        real_t val) {
  filler.fill(idmap[p], idmap[q], val);
}

template <typename T>
weight_1d_filler_t<T>::weight_1d_filler_t(T &filler, real_t w)
    : filler(filler), w(w) {
  ONE_DIM_WRAPPER_CHECK();
}

template <typename T>
inline index_t weight_1d_filler_t<T>::size() const {
  return filler.size();
}

template <typename T>
inline void weight_1d_filler_t<T>::_fill_impl(index_t p, real_t val) {
  return filler._fill_impl(p, val * w);
}

template <typename T>
weight_2d_filler_t<T>::weight_2d_filler_t(T &filler, real_t w)
    : filler(filler), w(w) {
  TWO_DIM_WRAPPER_CHECK();
}

template <typename T>
inline index_t weight_2d_filler_t<T>::rows() const {
  return filler.rows();
}

template <typename T>
inline index_t weight_2d_filler_t<T>::cols() const {
  return filler.cols();
}

template <typename T>
inline void weight_2d_filler_t<T>::_fill_impl(index_t p, index_t q,
                                              real_t val) {
  return filler._fill_impl(p, q, val * w);
}

template <typename T, bool Override, bool Parallel, bool Getdata>
one_dim_filler_t<T, Override, Parallel, Getdata>::one_dim_filler_t(T &data)
    : m_data(data) {
  static_assert(std::is_floating_point_v<T> ||
                    (details::data_filler_traits::has_size_v<T> &&
                     details::data_filler_traits::has_unary_access_v<T>),
                "data should be a floating type or a vector type!");
}

template <typename T, bool Override, bool Parallel, bool Getdata>
inline index_t one_dim_filler_t<T, Override, Parallel, Getdata>::size() const {
  if constexpr (std::is_floating_point_v<T>) {
    return 1;
  } else {
    return m_data.size();
  }
}

template <typename T, bool Override, bool Parallel, bool Getdata>
inline void one_dim_filler_t<T, Override, Parallel, Getdata>::_fill_impl(
    index_t p, real_t val) {
  if constexpr (std::is_floating_point_v<T>) {
    if constexpr (Override) {
      m_data = val;
    } else {
      m_data += val;
    }
  } else {
    if constexpr (Override) {
      m_data[p] = val;
    } else {
      m_data[p] += val;
    }
  }
}

template <typename T, bool Override, bool Parallel, bool Getdata>
template <bool _1, std::enable_if_t<_1 == true, bool>, bool _2,
          std::enable_if_t<_2 == true, bool>>
inline real_t *one_dim_filler_t<T, Override, Parallel, Getdata>::data() {
  static_assert(Override == true && Getdata == true,
                "Only support for override and get data mode");
  if constexpr (std::is_floating_point_v<T>) {
    return &m_data;
  } else {
    return m_data.data();
  }
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel,
          bool Getdata>
mat_filler_t<T, Fillmode, Override, Parallel, Getdata>::mat_filler_t(T &data)
    : m_data(data) {
  static_assert(details::data_filler_traits::has_binary_access_v<T> &&
                    details::data_filler_traits::has_rows_v<T> &&
                    details::data_filler_traits::has_cols_v<T>,
                "data should provide: rows/cols/(i,j) access!");
}
template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel,
          bool Getdata>
inline index_t mat_filler_t<T, Fillmode, Override, Parallel, Getdata>::rows()
    const {
  return m_data.rows();
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel,
          bool Getdata>
inline index_t mat_filler_t<T, Fillmode, Override, Parallel, Getdata>::cols()
    const {
  return m_data.cols();
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel,
          bool Getdata>
inline void mat_filler_t<T, Fillmode, Override, Parallel, Getdata>::_fill_impl(
    index_t p, index_t q, real_t val) {
#define FILL(p, q, val)     \
  if constexpr (Override) { \
    m_data(p, q) = val;     \
  } else {                  \
    m_data(p, q) += val;    \
  }

  if constexpr (Fillmode == MATRIX_FILL_MODE::FULL) {
    FILL(p, q, val);
  } else if constexpr (Fillmode == MATRIX_FILL_MODE::LOWER) {
    if (p >= q) {
      FILL(p, q, val);
    }
  } else {
    if (p <= q) {
      FILL(p, q, val);
    }
  }
#undef FILL
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel,
          bool Getdata>
template <bool _1, std::enable_if_t<_1 == true, bool>, bool _2,
          std::enable_if_t<_2 == true, bool>, MATRIX_FILL_MODE _3,
          std::enable_if_t<_3 == MATRIX_FILL_MODE::FULL, bool>>
inline real_t *mat_filler_t<T, Fillmode, Override, Parallel, Getdata>::data() {
  static_assert(
      Override == true && Getdata == true && Fillmode == MATRIX_FILL_MODE::FULL,
      "only override and can_get_data and Fullfill mode can access data!");
  return m_data.data();
}

template <typename T, bool Override, bool Parallel, bool Getdata>
gra_filler_t<T, Override, Parallel, Getdata>::gra_filler_t(T &data)
    : m_data(data) {
  static_assert(details::data_filler_traits::has_unary_access_v<T> &&
                    details::data_filler_traits::has_size_v<T>,
                "data should provide: size/[i] access!");
}

template <typename T, bool Override, bool Parallel, bool Getdata>
inline index_t gra_filler_t<T, Override, Parallel, Getdata>::rows() const {
  return 1;
}

template <typename T, bool Override, bool Parallel, bool Getdata>
inline index_t gra_filler_t<T, Override, Parallel, Getdata>::cols() const {
  return m_data.size();
}

template <typename T, bool Override, bool Parallel, bool Getdata>
inline void gra_filler_t<T, Override, Parallel, Getdata>::_fill_impl(
    index_t, index_t q, real_t val) {
  if constexpr (Override) {
    m_data[q] = val;
  } else {
    m_data[q] += val;
  }
}

template <typename T, bool Override, bool Parallel, bool Getdata>
template <bool _1, std::enable_if_t<_1 == true, bool>, bool _2,
          std::enable_if_t<_2 == true, bool>>
inline real_t *gra_filler_t<T, Override, Parallel, Getdata>::data() {
  static_assert(Override == true && Getdata == true,
                "only override and can_get_data can access data!");
  return m_data.data();
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel>
spmat_filler_t<T, Fillmode, Override, Parallel>::spmat_filler_t(T &data)
    : m_data(data) {
  static_assert(details::data_filler_traits::has_rows_v<T> &&
                    details::data_filler_traits::has_cols_v<T> &&
                    details::data_filler_traits::has_coeffRef_v<T>,
                "data should provide rows/cols/coeffRef");
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel>
inline index_t spmat_filler_t<T, Fillmode, Override, Parallel>::rows() const {
  return m_data.rows();
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel>
inline index_t spmat_filler_t<T, Fillmode, Override, Parallel>::cols() const {
  return m_data.cols();
}

template <typename T, MATRIX_FILL_MODE Fillmode, bool Override, bool Parallel>
inline void spmat_filler_t<T, Fillmode, Override, Parallel>::_fill_impl(
    index_t p, index_t q, real_t val) {
  if constexpr (Override) {
    m_data.coeffRef(p, q) = val;
  } else {
    m_data.coeffRef(p, q) += val;
  }
}

template <typename T, MATRIX_FILL_MODE Fillmode>
coo_filler_t<T, Fillmode>::coo_filler_t(T &data, index_t rows, index_t cols)
    : m_data(data), m_rows(rows), m_cols(cols) {
  //-> check data interface.
}

template <typename T, MATRIX_FILL_MODE Fillmode>
inline index_t coo_filler_t<T, Fillmode>::rows() const {
  return m_rows;
}

template <typename T, MATRIX_FILL_MODE Fillmode>
inline index_t coo_filler_t<T, Fillmode>::cols() const {
  return m_cols;
}
template <typename T, MATRIX_FILL_MODE Fillmode>
inline void coo_filler_t<T, Fillmode>::_fill_impl(index_t p, index_t q,
                                                  real_t val) {
  if constexpr (Fillmode == MATRIX_FILL_MODE::FULL) {
    m_data.emplace_back(p, q, val);
  } else if constexpr (Fillmode == MATRIX_FILL_MODE::LOWER) {
    if (p >= q) {
      m_data.emplace_back(p, q, val);
    }
  } else {
    if (p <= q) {
      m_data.emplace_back(p, q, val);
    }
  }
}
#undef ONE_DIM_WRAPPER_CHECK
#undef TWO_DIM_WRAPPER_CHECK
#undef IDMAP_CHECK
}  // namespace chaos::mapping
