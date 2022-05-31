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

}  // namespace chaos::mapping

#include "mapping/maxima.imp"
