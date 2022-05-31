#pragma once
#include "mapping/function.h"
//clang-format off
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>
//clang-format on

namespace chaos::mapping {

template <typename Derived, int xdim, int fdim>
struct autodiff_function_base : public function_base<Derived> {
  //-> if fdim is 1
  //-> Derived Class should implement this function.
  // template <typename T>
  // T mapsto(const Eigen::Ref<const vec_t<T>> &x,
  //          const function_cache_t *cache = nullptr) const {}
  //-> else
  // vec_t<T> mapsto(const Eigen::Ref<const vec_t<T>> &x,
  //          const function_cache_t *cache = nullptr) const {}

 private:
  friend class function_base<Derived>;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                         const Wrt &wrt, const Args &...args) const;

  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _check_validity(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                       const Wrt &wrt, const Args &...args) const;
  // clang-format off
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr, typename Wrt, typename... Args>
  void _eval_hes_1(OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr, typename Wrt, typename... Args>
  void _eval_hes_x(OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename OutJptr, typename Wrt, typename... Args>
  void _eval_jac_1(OutVptr valptr, OutJptr jacptr, const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename OutJptr, typename Wrt, typename... Args>
  void _eval_jac_x(OutVptr valptr, OutJptr jacptr, const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename Wrt, typename... Args>
  void _eval_val_1(OutVptr valptr, const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename Wrt, typename... Args>
  void _eval_val_x(OutVptr valptr, const Wrt &wrt, const Args &...args) const;
  // clang-format on

  template <int order>
  using dual_t = autodiff::HigherOrderDual<order, real_t>;
};

}  // namespace chaos::mapping
#include "mapping/autodiff.imp"
