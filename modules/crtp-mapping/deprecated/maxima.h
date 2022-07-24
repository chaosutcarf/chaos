#pragma once

#include <cstddef>
#include <type_traits>

#include "mapping/function.h"
#include "mapping/function_traits.h"
#include "utils/logger/logger.h"
namespace chaos::mapping {

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
struct maxima_wrapper_t
    : public function_base<maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>> {
  FUNCTION_INTERFACE(Xdim, Fdim, Xorder);
  maxima_wrapper_t(FuncPtr val_impl, FuncPtr jac_impl, FuncPtr hes_impl)
      : _val_func(val_impl), _jac_func(jac_impl), _hes_func(hes_impl) {
    static_assert(xdim > 0 && fdim > 0,
                  "currently not support dynamic dim setting");
  }

  FUNCTION_SPLIT_IMPL()
 private:
  template <typename OutVptr, typename Wrt, typename... Args>
  void _val_impl(OutVptr valptr, const Wrt &wrt, const Args &...args) const;
  template <typename OutJptr, typename Wrt, typename... Args>
  void _jac_impl(OutJptr jacptr, const Wrt &wrt, const Args &...args) const;
  template <typename OutHptr, typename Wrt, typename... Args>
  void _hes_impl(OutHptr hesptr, const Wrt &wrt, const Args &...args) const;

  FuncPtr _val_func, _jac_func, _hes_func;
};

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
template <typename OutVptr, typename Wrt, typename... Args>
void maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>::_val_impl(
    OutVptr valptr, const Wrt &wrt, const Args &...args) const {
  CHAOS_DEBUG_ASSERT(_val_func != nullptr);

  if constexpr (fdim == 1) {
    real_t val;
    (*_val_func)(&val, wrt.data(), args...);
    valptr->fill(0, val);
  } else {
    Eigen::Vector<real_t, fdim> val;
    if constexpr (details::function_traits::is_dynamic_dim(fdim)) {
      val.resize(this->Nf());
    }
    (*_val_func)(val.data(), wrt.data(), args...);
    valptr->template batch_fill(val);
  }
}

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
template <typename OutJptr, typename Wrt, typename... Args>
void maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>::_jac_impl(
    OutJptr jacptr, const Wrt &wrt, const Args &...args) const {
  CHAOS_DEBUG_ASSERT(_jac_func != nullptr);

  Eigen::Matrix<real_t, fdim, xdim> J;
  if constexpr (details::function_traits::is_dynamic_dim(fdim) ||
                details::function_traits::is_dynamic_dim(xdim)) {
    J.resize(this->Nf(), this->Nx());
  }
  (*_jac_func)(J.data(), wrt.data(), args...);
  jacptr->template batch_fill(J);
}

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
template <typename OutHptr, typename Wrt, typename... Args>
void maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>::_hes_impl(
    OutHptr hesptr, const Wrt &wrt, const Args &...args) const {
  CHAOS_DEBUG_ASSERT(_hes_func != nullptr);

#define RUN(H)                                 \
  (*_hes_func)(H.data(), wrt.data(), args...); \
  hesptr->template batch_fill(H);

  if constexpr (details::function_traits::is_dynamic_dim(fdim) ||
                details::function_traits::is_dynamic_dim(xdim)) {
    Eigen::Matrix<real_t, -1, xdim> H;
    H.resize(this->Nf() * this->Nx(), this->Nx());
    RUN(H);
  } else {
    Eigen::Matrix<real_t, fdim * xdim, xdim> H;
    RUN(H);
  }
#undef RUN
}
}  // namespace chaos::mapping
