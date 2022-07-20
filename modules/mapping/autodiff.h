#pragma once

#include "mapping/function.h"
// clang-format off
#include <autodiff/forward/dual.hpp>
#include <autodiff/forward/dual/eigen.hpp>
#include <cstddef>
// clang-format on

namespace chaos::mapping {

template <typename Derived>
struct autodiff_function_base : public function_base<Derived> {
  //-> if fdim is 1.
  //-> Derived Class should implement this function:
  // template <typename T, typename... Args>
  // T _mapsto(const Eigen::Ref<const vec_t<T>> &x, const Args &...args) const
  // {}
  //-> else
  // template <typename T, typename... Args>
  // vec_t<T> _mapsto(const Eigen::Ref<const vec_t<T>> &x, const Args &...args)
  // const {}

  template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
            typename... Args>
  void _eval(Vptr vptr, Jptr jptr, Hptr hptr, const Wrt &wrt,
             const Args &...args) const;

 private:
  template <typename Vptr, typename Wrt, typename... Args>
  void _eval_val(Vptr vptr, const Wrt &wrt, const Args &...args) const;
  template <typename Vptr, typename Jptr, typename Wrt, typename... Args>
  void _eval_jac_x(Vptr vptr, Jptr jptr, const Wrt &wrt,
                   const Args &...args) const;
  template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
            typename... Args>
  void _eval_hes_x(Vptr vptr, Jptr jptr, Hptr hptr, const Wrt &wrt,
                   const Args &...args) const;
  template <typename Vptr, typename Jptr, typename Wrt, typename... Args>
  void _eval_jac(Vptr vptr, Jptr jptr, const Wrt &wrt,
                 const Args &...args) const;
  template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
            typename... Args>
  void _eval_hes(Vptr vptr, Jptr jptr, Hptr hptr, const Wrt &wrt,
                 const Args &...args) const;
  template <int order>
  using dual_t = autodiff::HigherOrderDual<order, real_t>;
  using Base = function_base<Derived>;
};

template <typename Derived>
template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
          typename... Args>
void autodiff_function_base<Derived>::_eval(Vptr vptr, Jptr jptr, Hptr hptr,
                                            const Wrt &wrt,
                                            const Args &...args) const {
  if constexpr (!std::is_same_v<Hptr, std::nullptr_t>) {
    _eval_hes(vptr, jptr, hptr, wrt, args...);
  } else if constexpr (!std::is_same_v<Hptr, std::nullptr_t>) {
    _eval_jac(vptr, jptr, wrt, args...);
  } else if constexpr (!std::is_same_v<Vptr, std::nullptr_t>) {
    _eval_val(vptr, wrt, args...);
  }
}

template <typename Derived>
template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
          typename... Args>
void autodiff_function_base<Derived>::_eval_hes(Vptr vptr, Jptr jptr, Hptr hptr,
                                                const Wrt &wrt,
                                                const Args &...args) const {
  if constexpr (Base::CTI::Nf() != 1) {
    _eval_hes_x(vptr, jptr, hptr, wrt, args...);
  } else {
    auto X = wrt.template cast<dual_t<2>>().eval();
    dual_t<2> _2;
    Eigen::Matrix<real_t, 1, Base::CTI::Nx()> G;
    Eigen::Matrix<real_t, Base::CTI::Nx(), Base::CTI::Nx()> H;
    if constexpr (Base::CTI::Nx() == -1) {
      auto Nx = this->Nx();
      G.resize(1, Nx);
      H.resize(Nx, Nx);
    }
    autodiff::hessian(
        [this](const auto &x, const Args &...args) {
          return this->derived().template _mapsto<dual_t<2>>(x, args...);
        },
        autodiff::wrt(X), autodiff::at(X, args...), _2, G, H);
    hptr->fill(H);
    if constexpr (!std::is_same_v<Jptr, std::nullptr_t>) {
      jptr->fill(G);
    }
    if constexpr (!std::is_same_v<Vptr, std::nullptr_t>) {
      vptr->fill(_2.val.val);
    }
  }
}

template <typename Derived>
template <typename Vptr, typename Jptr, typename Hptr, typename Wrt,
          typename... Args>
void autodiff_function_base<Derived>::_eval_hes_x(Vptr vptr, Jptr jptr,
                                                  Hptr hptr, const Wrt &wrt,
                                                  const Args &...args) const {
#define RUN(J, H)                                                            \
  dual_t<2> _2;                                                              \
  auto X = wrt.template cast<dual_t<2>>().eval();                            \
  auto rH = H.reshaped(this->Nf(), this->Nx() * this->Nx());                 \
  for (int i = 0; i < this->Nf(); ++i) {                                     \
    auto &&Ji = J.row(i);                                                    \
    auto &&Hi = rH.row(i).reshaped(this->Nx(), this->Nx());                  \
    autodiff::hessian(                                                       \
        [&i, this](const auto &x, const Args &...args) {                     \
          return this->derived().template _mapsto<dual_t<2>>(x, args...)[i]; \
        },                                                                   \
        autodiff::wrt(X), autodiff::at(X, args...), _2, Ji, Hi);             \
    if constexpr (!std::is_same_v<Vptr, std::nullptr_t>) {                   \
      vptr->fill(i, _2.val.val);                                             \
    }                                                                        \
  }                                                                          \
  hptr->fill(H);                                                             \
  if constexpr (!std::is_same_v<Jptr, std::nullptr_t>) {                     \
    jptr->fill(J);                                                           \
  }

  Eigen::Matrix<real_t, Base::CTI::Nf(), Base::CTI::Nx()> J;
  if constexpr (Base::CTI::Nf() == -1 || Base::CTI::Nx() == -1) {
    Eigen::Matrix<real_t, -1, Base::CTI::Nx()> H;
    H.resize(this->Nf() * this->Nx(), this->Nx());
    J.resize(this->Nf(), this->Nx());
    RUN(J, H);
  } else {
    Eigen::Matrix<real_t, Base::CTI::Nf() * Base::CTI::Nx(), Base::CTI::Nx()> H;
    RUN(J, H);
  }
#undef RUN
}

template <typename Derived>
template <typename Vptr, typename Jptr, typename Wrt, typename... Args>
void autodiff_function_base<Derived>::_eval_jac(Vptr vptr, Jptr jptr,
                                                const Wrt &wrt,
                                                const Args &...args) const {
  if constexpr (Base::CTI::Nf() != 1) {
    _eval_jac_x(vptr, jptr, wrt, args...);
  } else {
    auto X = wrt.template cast<dual_t<1>>().eval();
    dual_t<1> _1;
    Eigen::Matrix<real_t, 1, Base::CTI::Nx()> J;
    if constexpr (Base::CTI::Nx() == -1) {
      J.resize(1, this->Nx());
    }
    autodiff::gradient(
        [&](const auto &x, const Args &...args) {
          return this->derived().template _mapsto<dual_t<1>>(x, args...);
        },
        autodiff::wrt(X), autodiff::at(X, args...), _1, J);
    jptr->fill(J);
    if constexpr (!std::is_same_v<Vptr, std::nullptr_t>) {
      vptr->fill(_1.val);
    }
  }
}

template <typename Derived>
template <typename Vptr, typename Jptr, typename Wrt, typename... Args>
void autodiff_function_base<Derived>::_eval_jac_x(Vptr vptr, Jptr jptr,
                                                  const Wrt &wrt,
                                                  const Args &...args) const {
  auto X = wrt.template cast<dual_t<1>>().eval();
  Eigen::Vector<dual_t<1>, Base::CTI::Nf()> _1;
  Eigen::Matrix<real_t, Base::CTI::Nf(), Base::CTI::Nx()> J;
  if constexpr (Base::CTI::Nf() == -1) {
    _1.resize(this->Nf());
  }
  if constexpr (Base::CTI::Nx() == -1 || Base::CTI::Nf() == -1) {
    J.resize(this->Nf(), this->Nx());
  }
  autodiff::jacobian(
      [this](const auto &x, const Args &...args) {
        return this->derived().template _mapsto<dual_t<1>>(x, args...);
      },
      autodiff::wrt(X), autodiff::at(X, args...), _1, J);
  jptr->fill(J);
  if constexpr (!std::is_same_v<Vptr, std::nullptr_t>) {
    vptr->fill(_1.template cast<real_t>());
  }
}

template <typename Derived>
template <typename Vptr, typename Wrt, typename... Args>
void autodiff_function_base<Derived>::_eval_val(Vptr vptr, const Wrt &wrt,
                                                const Args &...args) const {
  vptr->fill(this->derived().template _mapsto<real_t>(wrt, args...));
}

}  // namespace chaos::mapping
