#pragma once

#include <omp.h>

#include <set>
#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler_traits.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

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


#undef ONE_DIM_WRAPPER_CHECK
#undef TWO_DIM_WRAPPER_CHECK
#undef IDMAP_CHECK
}  // namespace chaos::mapping
