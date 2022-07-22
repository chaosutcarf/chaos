#pragma once

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/basic_data_filler.h"
#include "mapping/data_filler.h"
#include "mapping/filler/one_dim_filler.h"
#include "mapping/filler/two_dim_filler.h"
#include "mapping/function_concepts.h"
#include "mapping/patt_helper.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

template <typename T>
struct CompileTimeInfos {
  //-> check.
  constexpr static bool HasNx() {
    return function_concepts::CompileTimeNxConcept<T>;
  }
  constexpr static bool HasNf() {
    return function_concepts::CompileTimeNfConcept<T>;
  }
  constexpr static bool HasXorder() {
    return !function_concepts::RuntimeXorderConcept<T>;
  }
  //-> eval.
  constexpr static int Nx() {
    if constexpr (HasNx()) {
      return T::xdim;
    } else {
      return -1;
    }
  }
  constexpr static int Nf() {
    if constexpr (HasNf()) {
      return T::fdim;
    } else {
      return -1;
    }
  }
  constexpr static index_t Xorder() {
    static_assert(HasXorder(), "call CompileTimeInfo::Xorder before check!");
    if constexpr (function_concepts::HasMemberXorder<T>) {
      return T::xorder;
    } else {
      //-> neither xorder nor _Xorder() provide.
      return -1;
    }
  }
  constexpr static bool isValConstWrtX() { return Xorder() <= 0; }
  constexpr static bool isJacConstWrtX() { return Xorder() <= 1; }
  constexpr static bool isHesConstWrtX() { return Xorder() <= 2; }
};

template <typename Derived>
struct function_base {
  CRTP_derived_interface(Derived, function_base);
  using patt_t = patt_helper::patt_t;
  function_base() {
    static_assert(function_concepts::FunctionConcept<Derived>,
                  "Check FunctionConcept");
  }
  //-> CompileTime Informations
  using CTI = CompileTimeInfos<Derived>;
  //-> Runtime Informations
  inline int Nx() const;
  inline int Nf() const;
  inline index_t Xorder() const;
  inline bool isValConstWrtX() const { return Xorder() <= 0; }
  inline bool isJacConstWrtX() const { return Xorder() <= 1; }
  inline bool isHesConstWrtX() const { return Xorder() <= 2; }
  //-> Weights

  //-> Evaluations with check.
  template <typename Wrt, typename... Args>
  inline auto Val(const Wrt &wrt, const Args &...args) const;
  template <typename Wrt, typename... Args>
  inline auto Jac(const Wrt &wrt, const Args &...args) const;
  template <typename Wrt, typename... Args>
  inline auto Hes(const Wrt &wrt, const Args &...args) const;

  template <typename Out, typename Wrt, typename... Args>
  inline void Val(Out &&val, const Wrt &wrt, const Args &...args) const;
  template <typename Out, typename Wrt, typename... Args>
  inline void Jac(Out &&jac, const Wrt &wrt, const Args &...args) const;
  template <typename Out, typename Wrt, typename... Args>
  inline void Hes(Out &&hes, const Wrt &wrt, const Args &...args) const;
  //-> call together.
  template <typename OutV, typename OutJ, typename Wrt, typename... Args>
  inline void ValJac(OutV &&val, OutJ &&jac, const Wrt &wrt,
                     const Args &...args) const;
  template <typename OutV, typename OutH, typename Wrt, typename... Args>
  inline void ValHes(OutV &&val, OutH &&hes, const Wrt &wrt,
                     const Args &...args) const;
  template <typename OutJ, typename OutH, typename Wrt, typename... Args>
  inline void JacHes(OutJ &&jac, OutH &&hes, const Wrt &wrt,
                     const Args &...args) const;
  template <typename OutV, typename OutJ, typename OutH, typename Wrt,
            typename... Args>
  inline void ValJacHes(OutV &&val, OutJ &&jac, OutH &&hes, const Wrt &wrt,
                        const Args &...args) const;

  //-> pattern.
  inline patt_t *Jpatt() const;
  inline patt_t *Hpatt() const;
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
template <typename Derived>
auto inline function_base<Derived>::Jpatt() const -> patt_t * {
  if constexpr (function_concepts::HasFunctionJpatt<Derived>) {
    return derived()._Jpatt();
  } else {
    return nullptr;
  }
}

template <typename Derived>
auto inline function_base<Derived>::Hpatt() const -> patt_t * {
  if constexpr (function_concepts::HasFunctionHpatt<Derived>) {
    return derived()._Hpatt();
  } else {
    return nullptr;
  }
}

template <typename Derived>
template <typename Wrt, typename... Args>
inline auto function_base<Derived>::Val(const Wrt &wrt,
                                        const Args &...args) const {
  if constexpr (CTI::Nf() == 1) {
    real_t res{0};
    Val(scalar_filler_t(res), wrt, args...);
    return res;
  } else if constexpr (CTI::HasNf()) {
    vec_t<real_t, CTI::Nf()> res;
    res.setZero();
    Val(one_dim_filler_t(res), wrt, args...);
    return res;
  } else {
    vecxr_t res;
    res.setZero(Nf());
    Val(one_dim_filler_t(res), wrt, args...);
    return res;
  }
}

template <typename Derived>
template <typename Wrt, typename... Args>
inline auto function_base<Derived>::Jac(const Wrt &wrt,
                                        const Args &...args) const {
  if constexpr (CTI::HasNf() && CTI::HasNx()) {
    Eigen::Matrix<real_t, CTI::Nf(), CTI::Nx()> res;
    res.setZero();
    Jac(mat_filler_t(res), wrt, args...);
    return res;
  } else {
    matxr_t res;
    res.setZero(Nf(), Nx());
    Jac(mat_filler_t(res), wrt, args...);
    return res;
  }
}

template <typename Derived>
template <typename Wrt, typename... Args>
inline auto function_base<Derived>::Hes(const Wrt &wrt,
                                        const Args &...args) const {
  if constexpr (CTI::HasNx() && CTI::HasNf()) {
    Eigen::Matrix<real_t, CTI::Nf() * CTI::Nx(), CTI::Nx()> res;
    res.setZero();
    Hes(mat_filler_t(res), wrt, args...);
    return res;
  } else {
    matxr_t res;
    res.setZero(Nf() * Nx(), Nx());
    Hes(mat_filler_t(res), wrt, args...);
    return res;
  }
}

#define DefineDim(f)                                     \
  template <typename Derived>                            \
  inline int function_base<Derived>::N##f() const {      \
    static_assert(function_concepts::NfConcept<Derived>, \
                  "Should satisfy N" #f " Concept!");    \
    if constexpr (CTI::HasN##f()) {                      \
      return CTI::N##f();                                \
    } else {                                             \
      return derived()._N##f();                          \
    }                                                    \
  }

DefineDim(f);
DefineDim(x);
#undef DefineDim

template <typename Derived>
inline index_t function_base<Derived>::Xorder() const {
  if constexpr (CTI::HasXorder()) {
    return CTI::Xorder();
  } else {
    return derived()._Xorder();
  }
}

#define CHECK_VAL_PARAMS(Val, In)                                             \
  CHAOS_DEBUG_ASSERT(Val.size() == Nf(), Val.size(), Nf());                   \
  CHAOS_DEBUG_ASSERT(isValConstWrtX() || In.size() == Nx(), isValConstWrtX(), \
                     In.size(), Nx());

#define CHECK_JAC_PARAMS(Jac, In)                                             \
  CHAOS_DEBUG_ASSERT(Jac.cols() == Nx() && Jac.rows() == Nf(), Jac.cols(),    \
                     Jac.rows(), Nx(), Nf());                                 \
  CHAOS_DEBUG_ASSERT(isJacConstWrtX() || In.size() == Nx(), isJacConstWrtX(), \
                     In.size(), Nx());

#define CHECK_HES_PARAMS(Hes, In)                                             \
  CHAOS_DEBUG_ASSERT(Hes.cols() == Nx() && Hes.rows() == Nf() * Nx(),         \
                     Hes.cols(), Hes.rows(), Nx(), Nf(), Nf() * Nx());        \
  CHAOS_DEBUG_ASSERT(isHesConstWrtX() || In.size() == Nx(), isHesConstWrtX(), \
                     In.size(), Nx());

template <typename Derived>
template <typename OutV, typename Wrt, typename... Args>
inline void function_base<Derived>::Val(OutV &&val, const Wrt &wrt,
                                        const Args &...args) const {
  CHECK_VAL_PARAMS(val, wrt);
  derived()._eval(&val, nullptr, nullptr, wrt, args...);
}

template <typename Derived>
template <typename OutJ, typename Wrt, typename... Args>
inline void function_base<Derived>::Jac(OutJ &&jac, const Wrt &wrt,
                                        const Args &...args) const {
  CHECK_JAC_PARAMS(jac, wrt);
  derived()._eval(nullptr, &jac, nullptr, wrt, args...);
}

template <typename Derived>
template <typename OutH, typename Wrt, typename... Args>
inline void function_base<Derived>::Hes(OutH &&hes, const Wrt &wrt,
                                        const Args &...args) const {
  CHECK_HES_PARAMS(hes, wrt);
  derived()._eval(nullptr, nullptr, &hes, wrt, args...);
}

template <typename Derived>
template <typename OutV, typename OutJ, typename Wrt, typename... Args>
inline void function_base<Derived>::ValJac(OutV &&val, OutJ &&jac,
                                           const Wrt &wrt,
                                           const Args &...args) const {
  CHECK_VAL_PARAMS(val, wrt);
  CHECK_JAC_PARAMS(jac, wrt);
  derived()._eval(&val, &jac, nullptr, wrt, args...);
}

template <typename Derived>
template <typename OutV, typename OutH, typename Wrt, typename... Args>
inline void function_base<Derived>::ValHes(OutV &&val, OutH &&hes,
                                           const Wrt &wrt,
                                           const Args &...args) const {
  CHECK_VAL_PARAMS(val, wrt);
  CHECK_HES_PARAMS(hes, wrt);
  derived()._eval(&val, nullptr, &hes, wrt, args...);
}

template <typename Derived>
template <typename OutJ, typename OutH, typename Wrt, typename... Args>
inline void function_base<Derived>::JacHes(OutJ &&jac, OutH &&hes,
                                           const Wrt &wrt,
                                           const Args &...args) const {
  CHECK_JAC_PARAMS(jac, wrt);
  CHECK_HES_PARAMS(hes, wrt);
  derived()._eval(nullptr, &jac, &hes, wrt, args...);
}

template <typename Derived>
template <typename OutV, typename OutJ, typename OutH, typename Wrt,
          typename... Args>
inline void function_base<Derived>::ValJacHes(OutV &&val, OutJ &&jac,
                                              OutH &&hes, const Wrt &wrt,
                                              const Args &...args) const {
  CHECK_VAL_PARAMS(val, wrt);
  CHECK_JAC_PARAMS(jac, wrt);
  CHECK_HES_PARAMS(hes, wrt);
  derived()._eval(&val, &jac, &hes, wrt, args...);
}

#undef CHECK_VAL_PARAMS
#undef CHECK_JAC_PARAMS
#undef CHECK_HES_PARAMS
}  // namespace chaos::mapping

#define FUNCTION_SPLIT_IMPL()                                          \
  template <typename Vptr, typename Jptr, typename Hptr, typename Wrt, \
            typename... Args>                                          \
  void _eval(Vptr vptr, Jptr jptr, Hptr hptr, const Wrt &wrt,          \
             const Args &...args) const {                              \
    if constexpr (not_nullptr(hptr)) {                                 \
      CHAOS_DEBUG_ASSERT(hptr != nullptr);                             \
      _eval_hes(hptr, wrt, args...);                                   \
    }                                                                  \
    if constexpr (not_nullptr(jptr)) {                                 \
      CHAOS_DEBUG_ASSERT(jptr != nullptr);                             \
      _eval_jac(jptr, wrt, args...);                                   \
    }                                                                  \
    if constexpr (not_nullptr(vptr)) {                                 \
      CHAOS_DEBUG_ASSERT(vptr != nullptr);                             \
      _eval_val(vptr, wrt, args...);                                   \
    }                                                                  \
  }
