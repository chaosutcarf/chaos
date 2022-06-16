#pragma once

#include <type_traits>

#include "common/type.h"
#include "common/type_traits.h"
#include "mapping/patt_helper.h"

namespace chaos::mapping::details {
namespace eval_traits {
enum {
  VAL = 1,
  JAC = 2,
  VAL_JAC = VAL | JAC,
  HES = 4,
  VAL_HES = VAL | HES,
  JAC_HES = JAC | HES,
  VAL_JAC_HES = VAL | JAC | HES,
};
// clang-format off
template <int mode> constexpr bool has_eval_val() { return (mode & VAL) != 0; }
template <int mode> constexpr bool has_eval_jac() { return (mode & JAC) != 0; }
template <int mode> constexpr bool has_eval_hes() { return (mode & HES) != 0; }
// clang-format on

};  // namespace eval_traits

namespace function_traits {
constexpr index_t dynamic_dim = -1;
constexpr index_t dynamic_order = -1;
constexpr index_t inf_order = -2;

constexpr bool is_dynamic_dim(index_t dim) { return dim == dynamic_dim; }
constexpr bool is_dynamic_order(index_t order) {
  return order == dynamic_order;
}
constexpr bool is_inf_order(index_t order) { return order == inf_order; }

//-> xdim, fdim, pdim
DEFINE_HAS_MEMBER(p, xdim);
DEFINE_HAS_MEMBER(p, fdim);
DEFINE_HAS_MEMBER(p, pdim);
DEFINE_HAS_MEMBER(p, xorder);
DEFINE_HAS_MEMBER(p, porder);

#define HELPER_GET(member, val)                                         \
  template <typename T,                                                 \
            std::enable_if_t<has_member_##member##_v<T>, bool> = true>  \
  constexpr inline index_t get_##member() {                             \
    return T::member;                                                   \
  }                                                                     \
  template <typename T,                                                 \
            std::enable_if_t<!has_member_##member##_v<T>, bool> = true> \
  constexpr inline index_t get_##member() {                             \
    return val;                                                         \
  }

//-> default is dynamic.
HELPER_GET(xdim, dynamic_dim);
HELPER_GET(fdim, dynamic_dim);
//-> default is 0.
HELPER_GET(pdim, 0);
//-> default is inf.
HELPER_GET(xorder, inf_order);
HELPER_GET(porder, inf_order);
#undef HELPER_GET

#define CONST_NO_ARGS_INTERFACE(name, ret)                       \
  template <typename T>                                          \
  class has_##name {                                             \
    template <typename U>                                        \
    using impl_t = decltype(std::declval<const U&>()._##name()); \
                                                                 \
   public:                                                       \
    static constexpr bool value =                                \
        std::is_convertible_v<detected_t<impl_t, T>, ret>;       \
  };                                                             \
  EASY_VALUE(has_##name);
CONST_NO_ARGS_INTERFACE(Jpatt_impl, patt_helper::patt_t*);
CONST_NO_ARGS_INTERFACE(Hpatt_impl, patt_helper::patt_t*)
CONST_NO_ARGS_INTERFACE(nx_impl, index_t);
CONST_NO_ARGS_INTERFACE(nf_impl, index_t);
CONST_NO_ARGS_INTERFACE(np_impl, index_t);
CONST_NO_ARGS_INTERFACE(xorder_impl, index_t);
CONST_NO_ARGS_INTERFACE(porder_impl, index_t);

#undef CONST_NO_ARGS_INTERFACE
}  // namespace function_traits
}  // namespace chaos::mapping::details
