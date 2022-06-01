#pragma once

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler.h"
#include "mapping/function_traits.h"
#include "mapping/patt_helper.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

template <typename Derived>
struct function_base {
  using patt_t = patt_helper::patt_t;
  //-> Derived.traits should include:
  /*
   * xdim: -1 for dynamic
   * fdim: -1 for dynamic
   * pdim: -1 for dynamic
   * xorder: -1 for inf.
   * porder: -1 for inf.
   */
  //-> Derived should provide Nx(), Nf(), _val_jac_hes_impl.
  //-> _Jpatt_impl, _Hpatt_impl [optional]
  CRTP_derived_interface(Derived, function_base);
  inline index_t Nx() const;
  inline index_t Nf() const;
  inline index_t Np() const;  //-> check params number.
  inline patt_t *Jpatt() const;
  inline patt_t *Hpatt() const;

  inline bool is_val_constant() const;
  inline bool is_jac_constant() const;
  inline bool is_hes_constant() const;
  inline index_t get_xorder() const;
  inline bool is_val_constant_to_p() const;
  inline bool is_jac_constant_to_p() const;
  inline bool is_hes_constant_to_p() const;
  inline index_t get_porder() const;

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

template <typename Derived>
template <typename OutV, typename... Args>
void function_base<Derived>::_check_val_params(
    const OutV &val, [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(val.size() == Nx());
}
template <typename Derived>
template <typename OutJ, typename... Args>
void function_base<Derived>::_check_jac_params(
    const OutJ &jac, [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(jac.cols() == Nx());
  CHAOS_DEBUG_ASSERT(jac.rows() == Nf());
}
template <typename Derived>
template <typename OutH, typename... Args>
void function_base<Derived>::_check_hes_params(
    const OutH &hes, [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(hes.rows() == Nf());
  CHAOS_DEBUG_ASSERT(hes.cols() == Nx());
}

template <typename Derived>
template <typename Out, typename... Args>
inline void function_base<Derived>::Val(Out &&val, const Args &...args) const {
  //-> check parameter validity.
  _check_val_params(val, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::VAL>(
      &val, nullptr, nullptr, args...);
}

template <typename Derived>
template <typename Out, typename... Args>
inline void function_base<Derived>::Jac(Out &&jac, const Args &...args) const {
  _check_jac_params(jac, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::JAC>(
      nullptr, &jac, nullptr, args...);
}

template <typename Derived>
template <typename Out, typename... Args>
inline void function_base<Derived>::Hes(Out &&hes, const Args &...args) const {
  _check_hes_params(hes, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::HES>(
      nullptr, nullptr, &hes, args...);
}

template <typename Derived>
template <typename OutV, typename OutJ, typename... Args>
inline void function_base<Derived>::ValJac(OutV &&val, OutJ &&jac,
                                           const Args &...args) const {
  _check_val_params(val, args...);
  _check_jac_params(jac, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::VAL_JAC>(
      &val, &jac, nullptr, args...);
}

template <typename Derived>
template <typename OutV, typename OutH, typename... Args>
inline void function_base<Derived>::ValHes(OutV &&val, OutH &&hes,
                                           const Args &...args) const {
  _check_val_params(val, args...);
  _check_hes_params(hes, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::VAL_HES>(
      &val, &hes, nullptr, args...);
}

template <typename Derived>
template <typename OutJ, typename OutH, typename... Args>
inline void function_base<Derived>::JacHes(OutJ &&jac, OutH &&hes,
                                           const Args &...args) const {
  _check_jac_params(jac, args...);
  _check_hes_params(hes, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::JAC_HES>(
      nullptr, &jac, &hes, args...);
}

template <typename Derived>
template <typename OutV, typename OutJ, typename OutH, typename... Args>
inline void function_base<Derived>::ValJacHes(OutV &&val, OutJ &&jac,
                                              OutH &&hes,
                                              const Args &...args) const {
  _check_val_params(val, args...);
  _check_jac_params(jac, args...);
  _check_hes_params(hes, args...);
  derived().template _val_jac_hes_impl<details::eval_traits::VAL_JAC_HES>(
      &val, &jac, &hes, args...);
}

}  // namespace chaos::mapping
