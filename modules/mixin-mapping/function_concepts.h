#pragma once

#include <concepts>
#include <ratio>

#include "common/type.h"
#include "filler/one_dim_filler.h"
#include "filler/two_dim_filler.h"
#include "mapping/patt_helper.h"

namespace chaos::mapping {
// using type.
using dim_t = int;
using order_t = index_t;
using patt_t = patt_helper::patt_t;
constexpr order_t inf_order = -1;

//-> check nullptr_t.
template <typename T>
constexpr bool not_nullptr() {
  return !std::is_same_v<T, std::nullptr_t>;
}

template <typename T>
constexpr bool not_nullptr(const T &) {
  return not_nullptr<T>();
}

namespace function_concepts {

//-> check HasFunction.
#define DECLARE_CONST_HAS_FUNCTION(RetType, Func)   \
  template <typename T>                             \
  concept HasFunction##Func = requires(const T a) { \
    { a.Func() } -> std::convertible_to<RetType>;   \
  }
DECLARE_CONST_HAS_FUNCTION(patt_t *, Jpatt);
DECLARE_CONST_HAS_FUNCTION(patt_t *, Hpatt);
DECLARE_CONST_HAS_FUNCTION(order_t, Xorder);

#define DECLARE_DIM_CONCEPT(f)                                \
  template <typename T>                                       \
  concept CompileTimeN##f##Concept = T::f##dim > 0;           \
                                                              \
  DECLARE_CONST_HAS_FUNCTION(dim_t, N##f);                    \
                                                              \
  template <typename T>                                       \
  concept N##f##Concept =                                     \
      (CompileTimeN##f##Concept<T> || HasFunctionN##f<T>)&&!( \
          CompileTimeN##f##Concept<T> && HasFunctionN##f<T>);

//-> declare NxConcept and NfConcept.
DECLARE_DIM_CONCEPT(x);
DECLARE_DIM_CONCEPT(f);

#undef DECLARE_DIM_CONCEPT
#undef DECLARE_CONST_HAS_FUNCTION

template <typename T>
concept HasMemberXorder = requires {
  T::xorder;
};

template <typename T>
concept CompileTimeXorderConcept = HasMemberXorder<T> || !HasFunctionXorder<T>;

template <typename T>
concept XorderConcept = !(HasMemberXorder<T> && HasFunctionXorder<T>);

//-> EvalConcept.
template <typename T>
concept NoArgsEvalConcept = requires(const T a, vec_filler_t<vecxr_t> *val,
                                     mat_filler_t<matxr_t> *jac,
                                     mat_filler_t<matxr_t> *hes,
                                     const vecxr_t &x) {
  a.eval(val, jac, hes, x);
};

template <typename T>
concept WithArgsEvalConcept = requires(const T a) {
  true;
};

template <typename T>
concept EvalConecpt = NoArgsEvalConcept<T> || WithArgsEvalConcept<T>;

template <typename T>
concept FunctionConcept =
    NxConcept<T> && NfConcept<T> && XorderConcept<T> && EvalConecpt<T>;

}  // namespace function_concepts
}  // namespace chaos::mapping
