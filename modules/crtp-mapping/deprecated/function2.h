#pragma once

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler.h"
#include "mapping/function_concepts.h"
#include "mapping/patt_helper.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

template <typename Derived>
struct function_base {
  CRTP_derived_interface(Derived, function_base);
  using patt_t = patt_helper::patt_t;
  function_base() {
    static_assert(function_concepts::FunctionConcept<Derived>,
                  "Check FunctionConcept");
  }
  //-> CompileTime.
  // clang-format off
  constexpr int CompileTimeNx() const;
  constexpr int CompileTimeNf() const;
  constexpr int CompileTimeNp() const;
  constexpr index_t CompileTimeXorder() const;
  constexpr index_t CompileTimePorder() const;
  constexpr bool CompileTimeIsValConstantWrtX() const {return CompileTimeXorder() == 0;}
  constexpr bool CompileTimeIsJacConstantWrtX() const {return CompileTimeXorder() <= 1;}
  constexpr bool CompileTimeIsHesConstantWrtX() const {return CompileTimeXorder() <= 2;}
  constexpr bool CompileTimeIsValConstantWrtP() const {return CompileTimePorder() == 0;}
  constexpr bool CompileTimeIsJacConstantWrtP() const {return CompileTimePorder() <= 1;}
  constexpr bool CompileTimeIsHesConstantWrtP() const {return CompileTimePorder() <= 2;}
  //-> Runtime.
  // dimension ////////////////////////////////////////////////////////////////
  inline int Nx() const;
  inline int Nf() const;
  inline int Np() const;
  // order ////////////////////////////////////////////////////////////////////
  inline index_t Xorder() const;
  inline index_t Porder() const;
  inline bool is_val_const_wrt_x() const {return Xorder() == 0;}
  inline bool is_jac_const_wrt_x() const {return Xorder() <= 1;}
  inline bool is_hes_const_wrt_x() const {return Xorder() <= 2;}
  inline bool is_val_const_wrt_p() const {return Porder() == 0;}
  inline bool is_jac_const_wrt_p() const {return Porder() <= 1;}
  inline bool is_hes_const_wrt_p() const {return Porder() <= 2;}

  // evaluation
  // ///////////////////////////////////////////////////////////////
  template <typename Out, typename Wrt, typename... Args>
  inline void Val(Out &&val, const Wrt &wrt, const Args &...args) const;
  template <typename Out, typename Wrt, typename... Args>
  inline void Jac(Out &&jac, const Wrt &wrt, const Args &...args) const;
  template <typename Out, typename Wrt, typename... Args>
  inline void Hes(Out &&hes, const Wrt &wrt, const Args &...args) const;
  //-> call together.
  template <typename OutV, typename OutJ, typename Wrt, typename... Args>
  inline void ValJac(
      OutV &&val, OutJ &&jac, const Wrt &wrt, const Args &...args) const;
  template <typename OutV, typename OutH, typename Wrt, typename... Args>
  inline void ValHes(
      OutV &&val, OutH &&hes, const Wrt &wrt, const Args &...args) const;
  template <typename OutJ, typename OutH, typename Wrt, typename... Args>
  inline void JacHes(
      OutJ &&jac, OutH &&hes, const Wrt &wrt, const Args &...args) const;
  template <typename OutV, typename OutJ, typename OutH, typename Wrt,
            typename... Args>
  inline void ValJacHes(
      OutV &&val, OutJ &&jac, OutH &&hes, const Wrt &wrt, const Args &...args) const;

  // pattern //////////////////////////////////////////////////////////////////
  inline patt_t *Hpatt() const;
  inline patt_t *Jpatt() const;
  // clang-format on
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////
template <typename Derived>
auto inline function_base<Derived>::Hpatt() const -> patt_t * {
  if constexpr (function_concepts::HasRuntimeHpatt<Derived>) {
    return derived()._Hpatt();
  } else {
    return nullptr;
  }
}
template <typename Derived>
auto inline function_base<Derived>::Jpatt() const -> patt_t * {
  if constexpr (function_concepts::HasRuntimeJpatt<Derived>) {
    return derived()._Jpatt();
  } else {
    return nullptr;
  }
}
template <typename Derived>
constexpr int function_base<Derived>::CompileTimeNx() const {
  if constexpr (function_concepts::HasMemberXdim<Derived>) {
    return Derived::xdim;
  } else {
    return -1;
  }
}
template <typename Derived>
constexpr int function_base<Derived>::CompileTimeNf() const {
  if constexpr (function_concepts::HasMemberFdim<Derived>) {
    return Derived::fdim;
  } else {
    return -1;
  }
}
template <typename Derived>
constexpr int function_base<Derived>::CompileTimeNp() const {
  if constexpr (function_concepts::HasMemberPdim<Derived>) {
    return Derived::pdim;
  } else if constexpr (function_concepts::HasRuntimeNp<Derived>) {
    return -1;
  } else {
    return 0;
  }
}
template <typename Derived>
constexpr index_t function_base<Derived>::CompileTimeXorder() const {
  if constexpr (function_concepts::HasMemberXorder<Derived>) {
    return Derived::xorder;
  } else {
    return -1;
  }
}
template <typename Derived>
constexpr index_t function_base<Derived>::CompileTimePorder() const {
  if constexpr (function_concepts::HasMemberPorder<Derived>) {
    return Derived::porder;
  } else {
    return -1;
  }
}
template <typename Derived>
inline int function_base<Derived>::Nx() const {
  if constexpr (CompileTimeNx() != -1) {
    return CompileTimeNx();
  } else {
    return derived()._nx();
  }
}
template <typename Derived>
inline int function_base<Derived>::Nf() const {
  if constexpr (CompileTimeNf() != -1) {
    return CompileTimeNf();
  } else {
    return derived()._nf();
  }
}
template <typename Derived>
inline int function_base<Derived>::Np() const {
  if constexpr (CompileTimeNp() != -1) {
    return CompileTimeNp();
  } else {
    return derived()._np();
  }
}
template <typename Derived>
inline index_t function_base<Derived>::Xorder() const {
  if constexpr (CompileTimeXorder() != -1) {
    return CompileTimeXorder();
  } else {
    return derived()._xorder();
  }
}
template <typename Derived>
inline index_t function_base<Derived>::Porder() const {
  if constexpr (CompileTimePorder() != -1) {
    return CompileTimePorder();
  } else {
    return derived()._porder();
  }
}
}  // namespace chaos::mapping
