#include <type_traits>

#include "common/type.h"
#include "mapping/autodiff.h"
#include "mapping/function.h"
#include "mapping/function_concepts.h"
#include "utils/logger/logger.h"

using namespace chaos::mapping;
using namespace chaos;

struct test_auto_f : public autodiff_function_base<test_auto_f> {
  DECLARE_COMPILETIME_XDIM(3);
  DECLARE_COMPILETIME_FDIM(1);
  DECLARE_COMPILETIME_XORDER(inf_order);

  template <typename T, typename Wrt>
  auto _mapsto(const Wrt &x) const {
    return x.squaredNorm();
  }
};

struct test_auto_f2 : public autodiff_function_base<test_auto_f2> {
  DECLARE_COMPILETIME_FDIM(2);
  DECLARE_COMPILETIME_XDIM(3);
  DECLARE_COMPILETIME_XORDER(inf_order);

  template <typename T, typename Wrt>
  auto _mapsto(const Wrt &x) const {
    return vec_t<T, 2>{x.squaredNorm(), x.sum()};
  }
};

struct poly_f : public function_base<poly_f> {
  static constexpr int xdim = 3;
  static constexpr int fdim = 1;

  template <typename Vptr, typename Jptr, typename Hptr>
  void _eval(Vptr vptr, Jptr jptr, Hptr hptr,
             const Eigen::Ref<const vec3r_t> &x) const {
    if constexpr (not_nullptr(vptr)) {
      vptr->fill(x.squaredNorm());
    }
    if constexpr (not_nullptr(jptr)) {
      jptr->fill(2 * x.transpose());
    }
    if constexpr (not_nullptr(hptr)) {
      hptr->fill(mat33r_t::Identity() * 2);
    }
  }
};

int main(int argc, char *argv[]) {
  poly_f f;
  test_auto_f g;
  test_auto_f2 g2;
  vec3r_t x;
  x.setRandom();
  info_msg("g.Nf: {}", g.Nf());
  info_msg("g.Nx: {}", g.Nx());
  info_msg("g.val: {}", g.Val(x));
  info_msg("g.jac: {}", g.Jac(x));
  info_msg("g.hes: {}", g.Hes(x));
  info_msg("g2.Nf: {}", g2.Nf());
  info_msg("g2.Nx: {}", g2.Nx());
  info_msg("g2.val: {}", g2.Val(x));
  info_msg("g2.jac: {}", g2.Jac(x));
  info_msg("g2.hes: {}", g2.Hes(x));
  info_msg("x: {}", x);
  info_msg("Nf: {}", f.Nf());
  info_msg("Nx: {}", f.Nx());
  info_msg("CTI.Nf: {}", poly_f::CTI::Nf());
  info_msg("CTI.Nx: {}", poly_f::CTI::Nx());
  info_msg("Val: {}", f.Val(x));
  info_msg("Jac: {}", f.Jac(x));
  info_msg("Hes: {}", f.Hes(x));
  return 0;
}
