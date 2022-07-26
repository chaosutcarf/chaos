#pragma once
#include "common/type.h"
#include "mapping/function.h"
#include "mapping/function_traits.h"
//clang-format off
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>
#include <cstddef>
#include <type_traits>
//clang-format on

namespace chaos::mapping {

template <typename Derived, int Xdim, int Fdim,
          index_t Xorder = details::function_traits::inf_order>
struct autodiff_function_base : public function_base<Derived> {
  FUNCTION_INTERFACE(Xdim, Fdim, Xorder);
  //-> if fdim is 1
  //-> Derived Class should implement this function.
  // template <typename T, typename... Args>
  // T _mapsto(const Eigen::Ref<const vec_t<T>> &x, const Args&...args) const {}
  //-> else
  // template <typename T, typename... Args>
  // vec_t<T> _mapsto(const Eigen::Ref<const vec_t<T>> &x, const Args&...args)
  // const {}

  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                         const Wrt &wrt, const Args &...args) const;

 private:
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _check_validity(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                       const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl_1(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
                           const Wrt &wrt, const Args &...args) const;
  template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
            typename Wrt, typename... Args>
  void _val_jac_hes_impl_x(OutVptr valptr, OutJptr jacptr, OutHptr hesptr,
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

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void
autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_check_validity(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    [[maybe_unused]] const Args &...args) const {
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    CHAOS_DEBUG_ASSERT(valptr != nullptr);
  }
  if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    CHAOS_DEBUG_ASSERT(jacptr != nullptr);
  }
  if constexpr (details::eval_traits::has_eval_hes<mode>()) {
    CHAOS_DEBUG_ASSERT(hesptr != nullptr);
  }
  static_assert(std::is_base_of_v<Eigen::MatrixBase<std::decay_t<Wrt>>,
                                  std::decay_t<Wrt>>,
                "Wrt should be a eigen matrix base class!");
  //-> add order check
  CHAOS_DEBUG_ASSERT(wrt.size() == this->Nx());
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void
autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_val_jac_hes_impl(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  if constexpr (fdim == 1) {
    return _val_jac_hes_impl_1<mode>(valptr, jacptr, hesptr, wrt, args...);
  } else {
    return _val_jac_hes_impl_x<mode>(valptr, jacptr, hesptr, wrt, args...);
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void
autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_val_jac_hes_impl_1(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  if constexpr (details::eval_traits::has_eval_hes<mode>()) {
    _eval_hes_1<mode>(valptr, jacptr, hesptr, wrt, args...);
  } else if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    _eval_jac_1<mode>(valptr, jacptr, wrt, args...);
  } else {
    _eval_val_1<mode>(valptr, wrt, args...);
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void
autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_val_jac_hes_impl_x(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  if constexpr (details::eval_traits::has_eval_hes<mode>()) {
    _eval_hes_x<mode>(valptr, jacptr, hesptr, wrt, args...);
  } else if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    _eval_jac_x<mode>(valptr, jacptr, wrt, args...);
  } else {
    _eval_val_x<mode>(valptr, wrt, args...);
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_hes_1(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  static_assert(details::eval_traits::has_eval_hes<mode>(),
                "mode should have eval_hes part!");
  static_assert(!std::is_same_v<OutHptr, std::nullptr_t>,
                "OutHptr cannot be nullptr");
  static_assert(fdim == 1, "fdim should be a compile time variable!");

  Eigen::Matrix<real_t, fdim, xdim> G;
  Eigen::Matrix<real_t, xdim, xdim> H;

  if constexpr (details::function_traits::is_dynamic_dim(xdim)) {
    G.resize(1, this->Nx());
    H.resize(this->Nx(), this->Nx());
  }

  dual_t<2> _2;
  auto X = wrt.template cast<dual_t<2>>().eval();
  autodiff::hessian(
      [this](const auto &x, const Args &...args) {
        return this->derived().template _mapsto<dual_t<2>>(x, args...);
      },
      autodiff::wrt(X), autodiff::at(X, args...), _2, G, H);
  hesptr->template batch_fill(H);
  if constexpr (details::eval_traits::has_eval_jac<mode>()) {
    jacptr->template batch_fill(G);
  }
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    valptr->fill(0, _2.val.val);
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename OutHptr,
          typename Wrt, typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_hes_x(
    OutVptr valptr, OutJptr jacptr, OutHptr hesptr, const Wrt &wrt,
    const Args &...args) const {
  static_assert(details::eval_traits::has_eval_hes<mode>(),
                "mode should have eval_hes part!");
  static_assert(!std::is_same_v<OutHptr, std::nullptr_t>,
                "OutHptr should not be nullptr!");

#define RUN(J, H)                                                            \
  dual_t<2> _2;                                                              \
  auto X = wrt.template cast<dual_t<2>>().eval();                            \
  auto rH = H.reshaped(this->Nf(), this->Nx() * this->Nx());                 \
  for (size_t i = 0; i < this->Nf(); ++i) {                                  \
    auto &&Ji = J.row(i);                                                    \
    auto &&Hi = rH.row(i).reshaped(this->Nx(), this->Nx());                  \
    autodiff::hessian(                                                       \
        [&i, this](const auto &x, const Args &...args) {                     \
          return this->derived().template _mapsto<dual_t<2>>(x, args...)[i]; \
        },                                                                   \
        autodiff::wrt(X), autodiff::at(X, args...), _2, Ji, Hi);             \
    if constexpr (details::eval_traits::has_eval_val<mode>()) {              \
      valptr->fill(i, _2.val.val);                                           \
    }                                                                        \
  }                                                                          \
  hesptr->template batch_fill(H);                                            \
  if constexpr (details::eval_traits::has_eval_jac<mode>()) {                \
    jacptr->template batch_fill(J);                                          \
  }

  Eigen::Matrix<real_t, fdim, xdim> J;
  if constexpr (details::function_traits::is_dynamic_dim(fdim) ||
                details::function_traits::is_dynamic_dim(xdim)) {
    Eigen::Matrix<real_t, -1, xdim> H;
    H.resize(this->Nf() * this->Nx(), this->Nx());
    J.resize(this->Nf(), this->Nx());
    RUN(J, H);
  } else {
    Eigen::Matrix<real_t, fdim * xdim, xdim> H;
    RUN(J, H);
  }
#undef RUN
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename Wrt,
          typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_jac_1(
    OutVptr valptr, OutJptr jacptr, const Wrt &wrt, const Args &...args) const {
  static_assert(details::eval_traits::has_eval_jac<mode>(),
                "mode should have eval_jac part!");
  static_assert(!std::is_same_v<OutJptr, std::nullptr_t>,
                "OutJptr should not be nullptr");
  static_assert(fdim == 1, "fdim should be a compile time variable!");
  auto X = wrt.template cast<dual_t<1>>().eval();
  dual_t<1> _1;
  Eigen::Matrix<real_t, fdim, xdim> J;
  if constexpr (details::function_traits::is_dynamic_dim(xdim)) {
    J.resize(fdim, this->Nx());
  }
  autodiff::gradient(
      [&](const auto &x, const Args &...args) {
        return this->derived().template _mapsto<dual_t<1>>(x, args...);
      },
      autodiff::wrt(X), autodiff::at(X, args...), _1, J);
  jacptr->template batch_fill(J);
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    valptr->fill(0, _1.val);
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename OutJptr, typename Wrt,
          typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_jac_x(
    OutVptr valptr, OutJptr jacptr, const Wrt &wrt, const Args &...args) const {
  static_assert(details::eval_traits::has_eval_jac<mode>(),
                "mode should have eval_jac part!");
  static_assert(!std::is_same_v<OutJptr, std::nullptr_t>,
                "OutJptr should not be nullptr");

  auto X = wrt.template cast<dual_t<1>>().eval();
  Eigen::Vector<dual_t<1>, fdim> _1;
  Eigen::Matrix<real_t, fdim, xdim> J;
  if constexpr (details::function_traits::is_dynamic_dim(fdim)) {
    _1.resize(this->Nf());
  }
  if constexpr (details::function_traits::is_dynamic_dim(fdim) ||
                details::function_traits::is_dynamic_dim(xdim)) {
    J.resize(this->Nf(), this->Nx());
  }
  autodiff::jacobian(
      [&](const auto &x, const Args &...args) {
        return this->derived().template _mapsto<dual_t<1>>(x, args...);
      },
      autodiff::wrt(X), autodiff::at(X, args...), _1, J);
  jacptr->template batch_fill(J);
  if constexpr (details::eval_traits::has_eval_val<mode>()) {
    valptr->template batch_fill(_1.template cast<real_t>());
  }
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename Wrt, typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_val_1(
    OutVptr valptr, const Wrt &wrt, const Args &...args) const {
  static_assert(details::eval_traits::has_eval_val<mode>(),
                "mode should have eval_val part!");
  static_assert(!std::is_same_v<OutVptr, std::nullptr_t>,
                "OutVptr should not be a nullptr");
  static_assert(fdim == 1, "fdim should be a compile time variable!");
  valptr->fill(0, this->derived().template _mapsto<real_t>(wrt, args...));
}

template <typename Derived, int Xdim, int Fdim, index_t Xorder>
template <int mode, typename OutVptr, typename Wrt, typename... Args>
inline void autodiff_function_base<Derived, Xdim, Fdim, Xorder>::_eval_val_x(
    OutVptr valptr, const Wrt &wrt, const Args &...args) const {
  static_assert(details::eval_traits::has_eval_val<mode>(),
                "mode should have eval_val part!");
  static_assert(!std::is_same_v<OutVptr, std::nullptr_t>,
                "OutVptr should not be a nullptr");
  valptr->template batch_fill(
      this->derived().template _mapsto<real_t>(wrt, args...));
}

}  // namespace chaos::mapping