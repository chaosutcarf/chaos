#pragma once

#include "common/type.h"
#include "common/type_traits.h"

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
//-> xdim
//-> fdim
}
}  // namespace chaos::mapping::details