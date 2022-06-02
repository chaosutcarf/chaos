#pragma once

#include <cstddef>
#include <type_traits>

#include "mapping/function.h"
namespace chaos::mapping {

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
struct maxima_wrapper_t
    : public function_base<maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>> {
  FUNCTION_INTERFACE(Xdim, Fdim, Xorder);
  maxima_wrapper_t(FuncPtr val_impl, FuncPtr jac_impl, FuncPtr hes_impl)
      : _val_impl(val_impl), _jac_impl(jac_impl), _hes_impl(hes_impl) {
    static_assert(xdim > 0 && fdim > 0,
                  "currently not support dynamic dim setting");
  }

 private:
  friend class function_base<maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>>;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                         const Wrt &wrt, const Args &...args) const;
  FuncPtr _val_impl, _jac_impl, _hes_impl;
};

template <typename FuncPtr, int Xdim, int Fdim, int Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
void maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>::_val_jac_hes_impl(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    static_assert(!std::is_same_v<OutVptr, std::nullptr_t>,
                  "OutVptr should not be a nullptr");
    CHAOS_DEBUG_ASSERT(_val_impl != nullptr);
    if constexpr (fdim == 1) {
      real_t val;
      (*_val_impl)(&val, wrt.data(), args...);
      valptr->fill(0, val);
    } else {
      Eigen::Vector<real_t, fdim> val;
      if constexpr (fdim == -1) {
        val.resize(this->Nf());
      }
      (*_val_impl)(val.data(), wrt.data(), args...);
      valptr->template batch_fill(val);
    }
  }
  if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    static_assert(!std::is_same_v<OutJptr, std::nullptr_t>,
                  "OutJptr should not be a nullptr");
    CHAOS_DEBUG_ASSERT(_jac_impl != nullptr);
    Eigen::Matrix<real_t, fdim, xdim> J;
    if constexpr (fdim == -1 || xdim == -1) {
      J.resize(this->Nf(), this->Nx());
    }
    (*_jac_impl)(J.data(), wrt.data(), args...);
    jacptr->template batch_fill(J);
  }
  if constexpr (details::eval_traits::has_eval_hes<mode>()) {
    static_assert(!std::is_same_v<OutHptr, std::nullptr_t>,
                  "OutHptr should not be a nullptr");
    CHAOS_DEBUG_ASSERT(_hes_impl != nullptr);
#define RUN(H)                                 \
  (*_hes_impl)(H.data(), wrt.data(), args...); \
  hesptr->template batch_fill(H);

    if constexpr (fdim == -1 || xdim == -1) {
      Eigen::Matrix<real_t, -1, xdim> H;
      H.resize(this->Nf() * this->Nx(), this->Nx());
      RUN(H);
    } else {
      Eigen::Matrix<real_t, fdim * xdim, xdim> H;
      RUN(H);
    }
#undef RUN
  }
}
}  // namespace chaos::mapping
