#pragma once

#include <concepts>
#include <ratio>

#include "common/type.h"
#include "mapping/patt_helper.h"

namespace chaos::mapping {
using dim_t = int;
using order_t = index_t;
using patt_t = patt_helper::patt_t;
constexpr order_t inf_order = -1;

template <typename T>
constexpr bool not_nullptr() {
  return !std::is_same_v<T, std::nullptr_t>;
}

template <typename T>
constexpr bool not_nullptr(const T &) {
  return not_nullptr<T>();
}

namespace function_concepts {
#define has_function(RetType, Op, op)             \
  template <typename T>                           \
  concept HasFunction##Op = requires(const T a) { \
    { a.op() } -> std::convertible_to<RetType>;   \
  }

has_function(patt_helper::patt_t *, Hpatt, _Hpatt);
has_function(patt_helper::patt_t *, Jpatt, _Jpatt);
#undef has_function

#define DeclareDimConcept(f)                                       \
  template <typename T>                                            \
  concept CompileTimeN##f##Concept = T::f##dim > 0;                \
  template <typename T>                                            \
  concept RuntimeN##f##Concept = requires(const T a) {             \
    { a._N##f() } -> std::convertible_to<dim_t>;                   \
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
  { a._Xorder() } -> std::convertible_to<order_t>;
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
