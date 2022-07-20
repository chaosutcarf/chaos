#pragma once

#include <concepts>
#include <ratio>

#include "common/type.h"
#include "mapping/patt_helper.h"

namespace chaos::mapping {

// namespace eval_traits {
// enum {
//   VAL = 1,
//   JAC = 2,
//   VAL_JAC = VAL | JAC,
//   HES = 4,
//   VAL_HES = VAL | HES,
//   JAC_HES = JAC | HES,
//   VAL_JAC_HES = VAL | JAC | HES,
// };
// // clang-format off
// template <int mode> constexpr bool has_eval_val() { return (mode & VAL) != 0; }
// template <int mode> constexpr bool has_eval_jac() { return (mode & JAC) != 0; }
// template <int mode> constexpr bool has_eval_hes() { return (mode & HES) != 0; }
// // clang-format on
// };  // namespace eval_traits

namespace function_concepts {
#define has_function(RetType, Op, op)             \
  template <typename T>                           \
  concept HasFunction##Op = requires(const T a) { \
    { a.op() } -> std::convertible_to<RetType>;   \
  }

has_function(patt_helper::patt_t*, Hpatt, _Hpatt);
has_function(patt_helper::patt_t*, Jpatt, _Jpatt);
#undef has_function

#define DeclareDimConcept(f)                                       \
  template <typename T>                                            \
  concept CompileTimeN##f##Concept = T::f##dim > 0;                \
  template <typename T>                                            \
  concept RuntimeN##f##Concept = requires(const T a) {             \
    { a._N##f() } -> std::convertible_to<int>;                     \
  };                                                               \
  template <typename T>                                            \
  concept N##f##Concept =                                          \
      (CompileTimeN##f##Concept<T> || RuntimeN##f##Concept<T>)&&!( \
          CompileTimeN##f##Concept<T> && RuntimeN##f##Concept<T>);

DeclareDimConcept(f);
DeclareDimConcept(x);
#undef DeclareDimConcept

template <typename T>
concept HasMemberXorder = requires {
  T::xorder;
};

template <typename T>
concept RuntimeXorderConcept = requires(const T a) {
  { a._Xorder() } -> std::convertible_to<index_t>;
};

template <typename T>
concept CompileTimeXorderConcept =
    HasMemberXorder<T> || !RuntimeXorderConcept<T>;

template <typename T>
concept XorderConcept = !(HasMemberXorder<T> && RuntimeXorderConcept<T>);

template <typename T>
concept FunctionConcept = NxConcept<T> && NfConcept<T> && XorderConcept<T>;

}  // namespace function_concepts
}  // namespace chaos::mapping
