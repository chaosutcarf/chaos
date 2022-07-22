#pragma once

#include <type_traits>

#include "common/type.h"
#include "mapping/function.h"

namespace chaos::mapping {
template <typename Functor>
struct function_with_context {
  using CTI = typename Functor::CTI;
  using wrt_t =
      std::conditional_t<CTI::HasNx(), vec_t<real_t, CTI::Nx()>, vecxr_t>;

  //-> maintain the lifetime outside.
  function_with_context(Functor &func) : m_func(func){};
  //-> maintain the lifetime by shared_ptr.
  function_with_context(const std::shared_ptr<Functor> &func)
      : m_ptr(func), m_func(*m_ptr) {}

  dim_t Nx() const { return m_func.Nx(); }
  dim_t Nf() const { return m_func.Nf(); }
  order_t Xorder() const { return m_func.Xorder(); }

  Functor &core() { return m_func; }
  const Functor &core() const { return m_func; }

  //-> TODO. type of x.
  template <typename Wrt>
  void set_x(const Wrt &x) {
    m_x = x;
  }

  //-> TODO. check timestamp.
  //-> TODO. lazy evaluation.
  auto Val() const {
    std::conditional_t<CTI::Nf() == 1, real_t, vec_t<real_t, CTI::Nf()>> res;
    if constexpr (CTI::Nf() == 1) {
      res = 0;
      Val(scalar_filler_t(res));
    } else {
      res.setZero(Nf());
      Val(one_dim_filler_t(res));
    }
    return res;
  }
  auto Jac() const {
    Eigen::Matrix<real_t, CTI::Nf(), CTI::Nx()> res;
    if constexpr (CTI::HasNf() && CTI::HasNx()) {
      res.setZero();
    } else {
      res.setZero(Nf(), Nx());
    }
    Jac(mat_filler_t(res));
    return res;
  }
  auto Hes() const {
    std::conditional_t<
        CTI::HasNx() && CTI::HasNf(),
        Eigen::Matrix<real_t, CTI::Nf() * CTI::Nx(), CTI::Nx()>,
        std::conditional_t<CTI::HasNx(), Eigen::Matrix<real_t, -1, CTI::Nx()>,
                           Eigen::Matrix<real_t, -1, -1>>>
        res;
    if constexpr (CTI::HasNf() && CTI::HasNx()) {
      res.setZero();
    } else {
      res.setZero(Nx() * Nf(), Nx());
    }
    Hes(mat_filler_t(res));
    return res;
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
  std::conditional_t<CTI::HasNx(), vec_t<real_t, CTI::Nx()>, vecxr_t> m_x;
  Functor &m_func;
};
}  // namespace chaos::mapping
