#pragma once

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler.h"
#include "mapping/patt_helper.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

namespace details {
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
}  // namespace details

template <typename Derived>
struct function_base {
  //-> Derived.traits should include:
  /*
   * xdim: -1 for dynamic
   * fdim: -1 for dynamic
   * pdim: -1 for dynamic
   * xorder: -1 for inf.
   * porder: -1 for inf.
   */
  //-> Derived should provide Nx(), Nf(), _val_jac_hes_impl.
  CRTP_derived_interface(Derived, function_base);
  inline index_t Nx() const { return derived().Nx(); }
  inline index_t Nf() const { return derived().Nf(); }
  inline index_t Np() const;  //-> check params number.

  template <typename Out, typename... Args>
  inline void Val(Out &&val, const Args &...args) const;

  template <typename Out, typename... Args>
  inline void Jac(Out &&jac, const Args &...args) const;

  template <typename Out, typename... Args>
  inline void Hes(Out &&hes, const Args &...args) const;

  //-> call together.
  template <typename OutV, typename OutJ, typename... Args>
  inline void ValJac(OutV &&val, OutJ &&jac, const Args &...args) const;
  template <typename OutV, typename OutH, typename... Args>
  inline void ValHes(OutV &&val, OutH &&hes, const Args &...args) const;
  template <typename OutJ, typename OutH, typename... Args>
  inline void JacHes(OutJ &&jac, OutH &&hes, const Args &...args) const;
  template <typename OutV, typename OutJ, typename OutH, typename... Args>
  inline void ValJacHes(OutV &&val, OutJ &&jac, OutH &&hes,
                        const Args &...args) const;

 private:
  template <typename OutV, typename... Args>
  void _check_val_params(const OutV &val, const Args &...args) const;
  template <typename OutJ, typename... Args>
  void _check_jac_params(const OutJ &jac, const Args &...args) const;
  template <typename OutH, typename... Args>
  void _check_hes_params(const OutH &hes, const Args &...args) const;
};

}  // namespace chaos::mapping
#include "mapping/function.imp"
