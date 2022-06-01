#pragma once

#include "mapping/function.h"
namespace chaos::mapping {

template <typename FuncPtr, int xdim, int fdim>
struct maxima_wrapper_t
    : public function_base<maxima_wrapper_t<FuncPtr, xdim, fdim>> {
  maxima_wrapper_t(FuncPtr val_impl, FuncPtr jac_impl, FuncPtr hes_impl)
      : _val_impl(val_impl), _jac_impl(jac_impl), _hes_impl(hes_impl) {
    static_assert(xdim > 0 && fdim > 0,
                  "currently not support dynamic dim setting");
  }

 private:
  friend class function_base<maxima_wrapper_t<FuncPtr, xdim, fdim>>;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                         const Wrt &wrt, const Args &...args) const;
  FuncPtr _val_impl, _jac_impl, _hes_impl;
};

template <typename FuncPtr, int xdim, int fdim>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
void maxima_wrapper_t<FuncPtr, xdim, fdim>::_val_jac_hes_impl(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    CHAOS_DEBUG_ASSERT(_val_impl != nullptr);
    if constexpr (fdim == 1) {
      real_t val;
      (*_val_impl)(&val, wrt.data(), args...);
      valptr->fill(0, val);
    } else {
      Eigen::Vector<real_t, fdim> val;
      (*_val_impl)(val.data(), wrt.data(), args...);
      valptr->template batch_fill(val);
    }
  }
  if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    CHAOS_DEBUG_ASSERT(_jac_impl != nullptr);
    Eigen::Matrix<real_t, fdim, xdim> J;
    (*_jac_impl)(J.data(), wrt.data(), args...);
    jacptr->template batch_fill(J);
  }
  if constexpr (details::eval_traits::has_eval_hes<mode>()) {
    CHAOS_DEBUG_ASSERT(_hes_impl != nullptr);
    Eigen::Matrix<real_t, fdim * xdim, xdim> H;
    (*_hes_impl)(H.data(), wrt.data(), args...);
    hesptr->template batch_fill(H);
  }
}
}  // namespace chaos::mapping
