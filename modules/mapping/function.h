#pragma once

#include <type_traits>

#include "common/pattern.h"
#include "common/type.h"
#include "mapping/data_filler.h"
#include "mapping/function_traits.h"
#include "mapping/patt_helper.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

#define EASY_GET(m)                                                         \
  inline index_t N##m() const {                                             \
    if constexpr (!details::function_traits::is_dynamic_dim(                \
                      details::function_traits::get_##m##dim<Derived>())) { \
      return details::function_traits::get_##m##dim<Derived>();             \
    } else {                                                                \
      static_assert(details::function_traits::has_n##m##_impl_v<Derived>,   \
                    "Must implement _n" #m "_impl!");                       \
      return derived()._n##m##_impl();                                      \
    }                                                                       \
  }

#define EASY_PATT(patt)                                                     \
  inline patt_t *patt() const {                                             \
    if constexpr (details::function_traits::has_##patt##_impl_v<Derived>) { \
      return derived()._##patt##_impl();                                    \
    } else {                                                                \
      return nullptr;                                                       \
    }                                                                       \
  }

#define FUNCTION_INTERFACE(Xdim, Fdim, Xorder) \
  static constexpr index_t xdim = Xdim;        \
  static constexpr index_t fdim = Fdim;        \
  static constexpr index_t xorder = Xorder;

template <typename Derived>
struct function_base {
  using patt_t = patt_helper::patt_t;
  //-> Derived.traits
  /*
   * xdim: -1 for dynamic by default.
   * fdim: -1 for dynamic by default.
   * pdim: -1 for dynamic by default.
   * xorder: -1 for inf by default.
   * porder: -1 for inf by default.
   */
  //-> Derived should provide _nx_impl(), _nf_impl(), _val_jac_hes_impl.
  //-> _Jpatt_impl, _Hpatt_impl [optional]
  CRTP_derived_interface(Derived, function_base);
  EASY_GET(x);  // Nx
  EASY_GET(f);  // Nf
  EASY_GET(p);  // Np
#undef EASY_GET
  EASY_PATT(Jpatt);  // Jpatt
  EASY_PATT(Hpatt);  // Hpatt
#undef EASY_PATT

  inline bool is_val_constant() const { return get_xorder() == 0; }
  inline bool is_jac_constant() const { return get_xorder() <= 1; }
  inline bool is_hes_constant() const { return get_xorder() <= 2; }
  inline index_t get_xorder() const {
    return details::function_traits::get_xorder<Derived>();
  }
  inline bool is_val_constant_to_p() const { return get_porder() == 0; }
  inline bool is_jac_constant_to_p() const { return get_porder() <= 1; }
  inline bool is_hes_constant_to_p() const { return get_porder() <= 2; }
  inline index_t get_porder() const {
    return details::function_traits::get_porder<Derived>();
  }

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
inline void function_base<Derived>::_check_val_params(
    [[maybe_unused]] const OutV &val,
    [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(val.size() == Nf());
}
template <typename Derived>
template <typename OutJ, typename... Args>
void function_base<Derived>::_check_jac_params(
    [[maybe_unused]] const OutJ &jac,
    [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(jac.cols() == Nx());
  CHAOS_DEBUG_ASSERT(jac.rows() == Nf());
}
template <typename Derived>
template <typename OutH, typename... Args>
void function_base<Derived>::_check_hes_params(
    [[maybe_unused]] const OutH &hes,
    [[maybe_unused]] const Args &...args) const {
  CHAOS_DEBUG_ASSERT(hes.cols() == Nx());
  CHAOS_DEBUG_ASSERT(hes.rows() == Nf() * Nx());
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

#undef EASY_GET

//-> helper.
//-> split impl should impl:
//-> 1. _val_impl
//-> 2. _jac_impl
//-> 3. _hes_impl.
#define FUNCTION_SPLIT_IMPL()                                               \
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr, \
            typename Wrt, typename... Args>                                 \
  void _val_jac_hes_impl(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,    \
                         const Wrt &wrt, const Args &...args) const {       \
    if constexpr (chaos::mapping::details::eval_traits::has_eval_val<       \
                      mode>()) {                                            \
      static_assert(!std::is_same_v<OutVptr, std::nullptr_t>,               \
                    "OutVptr should not be a nullptr");                     \
      _val_impl(valptr, wrt, args...);                                      \
    }                                                                       \
    if constexpr (chaos::mapping::details::eval_traits::has_eval_jac<       \
                      mode>()) {                                            \
      static_assert(!std::is_same_v<OutJptr, std::nullptr_t>,               \
                    "OutJptr should not be a nullptr");                     \
      _jac_impl(jacptr, wrt, args...);                                      \
    }                                                                       \
    if constexpr (chaos::mapping::details::eval_traits::has_eval_hes<       \
                      mode>()) {                                            \
      static_assert(!std::is_same_v<OutHptr, std::nullptr_t>,               \
                    "OutHptr should not be a nullptr");                     \
      _hes_impl(hesptr, wrt, args...);                                      \
    }                                                                       \
  }
}  // namespace chaos::mapping
