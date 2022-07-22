#pragma once

#include "common/type.h"
#include "mapping/function.h"

namespace chaos::mapping {
template <typename Functor>
struct function_with_context {
  //-> maintain the lifetime outside.
  function_with_context(Functor &func) : m_func(func){};
  //-> maintain the lifetime by shared_ptr.
  function_with_context(const std::shared_ptr<Functor> &func)
      : m_ptr(func), m_func(*m_ptr) {}
  using CTI = typename Functor::CTI;

  dim_t Nx() const { return m_func.Nx(); }
  dim_t Nf() const { return m_func.Nf(); }
  order_t Xorder() const { return m_func.Xorder(); }

  //-> TODO. type of x.
  template <typename Wrt>
  void set_x(const Wrt &x) {
    m_x = x;
  }

  //-> TODO. check timestamp.
  //-> TODO. lazy evaluation.
  auto Val() const {
    if constexpr (CTI::Nf() == 1) {
      real_t res{0};
      Val(scalar_filler_t(res));
      return res;
    } else if constexpr (CTI::Nf() != -1) {
      vec_t<real_t, CTI::Nf()> res;
      res.setZero();
      Val(one_dim_filler_t(res));
      return res;
    } else {
      vecxr_t res;
      res.setZero(m_func.Nf());
      Val(one_dim_filler_t(res));
      return res;
    }
  }
  auto Jac() const {
    if constexpr (CTI::HasNf() && CTI::HasNx()) {
      Eigen::Matrix<real_t, CTI::Nf(), CTI::Nx()> res;
      res.setZero();
      Jac(mat_filler_t(res));
      return res;
    } else {
      matxr_t res;
      res.setZero(m_func.Nf(), m_func.Nx());
      Jac(mat_filler_t(res));
      return res;
    }
  }
  auto Hes() const {
    if constexpr (CTI::HasNx() && CTI::HasNf()) {
      Eigen::Matrix<real_t, CTI::Nf() * CTI::Nx(), CTI::Nx()> res;
      res.setZero();
      Hes(mat_filler_t(res));
      return res;
    } else {
      matxr_t res;
      res.setZero(Nf() * Nx(), Nx());
      Hes(mat_filler_t(res));
      return res;
    }
  }
  template <typename OutV>
  void Val(OutV &&val) const {
    m_func.Val(val, m_x);
  }

  template <typename OutJ>
  void Jac(OutJ &&jac) const {
    m_func.Jac(jac, m_x);
  }

  template <typename OutH>
  void Hes(OutH &&hes) const {
    m_func.Hes(hes, m_x);
  }

 private:
  std::shared_ptr<Functor> m_ptr;
  vecxr_t m_x;
  Functor &m_func;
};
}  // namespace chaos::mapping
