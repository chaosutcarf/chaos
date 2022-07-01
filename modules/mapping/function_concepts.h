#pragma once

#include <concepts>

#include "common/type.h"

namespace chaos::mapping::function_concepts {

#define has_member(Type, Mem, mem)           \
  template <typename T>                      \
  concept HasMember##Mem = requires {        \
    { T::mem } -> std::convertible_to<Type>; \
  };

has_member(int, Xdim, xdim);
has_member(int, Fdim, fdim);
has_member(int, Pdim, pdim);
has_member(index_t, Xorder, xorder);
has_member(index_t, Porder, porder);
#undef has_member

#define has_runtime_op(Type, Op, op)             \
  template <typename T>                          \
  concept HasRuntime##Op = requires(const T a) { \
    { a.op() } -> std::convertible_to<Type>;     \
  };
has_runtime_op(int, Nx, _nx);
has_runtime_op(int, Nf, _nf);
has_runtime_op(int, Np, _np);
has_runtime_op(index_t, Xorder, _xorder);
has_runtime_op(index_t, Porder, _porder);
#undef has_runtime_op

template <typename T>
concept FunctionLike = requires(T a) {
  a+a;
  //-> CompileTimeNx or RuntimeNx
  //-> CompileTimeNf or RuntimeNf
  //-> [optional] Np. 0 by default.

  //-> CompileTimeXorder or RuntimeXorder
  //-> [optional] If Np provide and is non-zero, then CompileTimePorder or RuntimePorder. INF by default.

  //-> <EVAL_LEVEL>_eval.
  //-> [optional] Hpatt, Jpatt.
};

}  // namespace chaos::mapping::function_concepts
