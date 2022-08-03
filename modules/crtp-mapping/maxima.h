#pragma once

#include <cstddef>

#include "mapping/function.h"
#include "mapping/function_concepts.h"
#include "utils/logger/logger.h"

namespace chaos::mapping {

template <typename FuncPtr, dim_t Xdim, dim_t Fdim, order_t Xorder = inf_order>
struct maxima_wrapper_t
    : public function_base<maxima_wrapper_t<FuncPtr, Xdim, Fdim, Xorder>> {
  DECLARE_COMPILETIME_XDIM(Xdim);
  DECLARE_COMPILETIME_FDIM(Fdim);
  DECLARE_COMPILETIME_XORDER(Xorder);

  maxima_wrapper_t(FuncPtr val_impl, FuncPtr jac_impl, FuncPtr hes_impl)
      : m_val_impl(val_impl), m_jac_impl(jac_impl), m_hes_impl(hes_impl) {
    static_assert(xdim > 0 && fdim > 0,
                  "currently not support dynamic dim setting!");
  }

  FUNCTION_SPLIT_IMPL();

 private:
  template <typename Vptr, typename Wrt, typename... Args>
  void _eval_val(Vptr vptr, const Wrt &wrt, const Args &...args) const {
    CHAOS_DEBUG_ASSERT(m_val_impl != nullptr);
    static_assert(fdim > 0, "currently, fdim should be > 0 here.");
    if constexpr (fdim == 1) {
      real_t val;
      (*m_val_impl)(&val, wrt.data(), args...);
      vptr->fill(val);
    } else {
      Eigen::Vector<real_t, fdim> val;
      (*m_val_impl)(val.data(), wrt.data(), args...);
      vptr->fill(val);
    }
  }
  template <typename Jptr, typename Wrt, typename... Args>
  void _eval_jac(Jptr jptr, const Wrt &wrt, const Args &...args) const {
    CHAOS_DEBUG_ASSERT(m_jac_impl != nullptr);
    static_assert(fdim > 0 && xdim > 0, "fdim > 0 anad xdim > 0");
    Eigen::Matrix<real_t, fdim, xdim> jac;
    (*m_jac_impl)(jac.data(), wrt.data(), args...);
    jptr->fill(jac);
  }

  template <typename Hptr, typename Wrt, typename... Args>
  void _eval_hes(Hptr hptr, const Wrt &wrt, const Args &...args) const {
    CHAOS_DEBUG_ASSERT(m_hes_impl != nullptr);
    static_assert(fdim > 0 && xdim > 0, "fdim > 0 and xdim > 0");
    Eigen::Matrix<real_t, xdim * fdim, xdim> hes;
    (*m_hes_impl)(hes.data(), wrt.data(), args...);
    hptr->fill(hes);
  }

  FuncPtr m_val_impl, m_jac_impl, m_hes_impl;
};

}  // namespace chaos::mapping
