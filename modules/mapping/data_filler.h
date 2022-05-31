#pragma once

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
  offset_1d_filler_t(T &&filler, index_t offset);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, false);

 private:
  T &&filler;
  index_t offset;
};

template <typename T>
struct offset_2d_filler_t : public two_dim_filler_base<offset_2d_filler_t<T>> {
  offset_2d_filler_t(T &&filler, index_t off_r, index_t off_c);
  offset_2d_filler_t(T &&filler, index_t off)
      : offset_2d_filler_t(filler, off, off) {}
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode, false);

 private:
  T &&filler;
  index_t off_r, off_c;
};

template <typename T, typename IndexList>
struct idmap_1d_filler_t
    : public two_dim_filler_base<idmap_1d_filler_t<T, IndexList>> {
  idmap_1d_filler_t(T &&filler, const IndexList &idmap);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, false);

 private:
  T &&filler;
  const IndexList &idmap;
};

template <typename T, typename IndexList>
struct idmap_2d_filler_t
    : public two_dim_filler_base<idmap_2d_filler_t<T, IndexList>> {
  idmap_2d_filler_t(T &&filler, const IndexList &idmap);
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode, false);

 private:
  T &&filler;
  const IndexList &idmap;
};

template <typename T>
struct weight_1d_filler_t : public two_dim_filler_base<weight_1d_filler_t<T>> {
  weight_1d_filler_t(T &&filler, real_t w);
  ONE_DIM_INTERFACE(T::override_mode, T::can_parallel, T::can_get_data);

 private:
  T &&filler;
  real_t w;
};

template <typename T>
struct weight_2d_filler_t : public two_dim_filler_base<weight_2d_filler_t<T>> {
  weight_2d_filler_t(T &&filler, real_t w);
  TWO_DIM_INTERFACE(T::override_mode, T::can_parallel, T::fill_mode,
                    T::can_get_data);

 private:
  T &&filler;
  real_t w;
};

}  // namespace chaos::mapping
#include "mapping/data_filler.imp"
