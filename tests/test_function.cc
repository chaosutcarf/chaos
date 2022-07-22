#include <type_traits>

#include "common/type.h"
#include "mapping/function.h"

using namespace chaos::mapping;
using namespace chaos;

struct poly_f : public function_base<poly_f> {
  static constexpr int xdim = 3;
  static constexpr int fdim = 1;

  template <typename Vptr, typename Jptr, typename Hptr>
  void _eval(Vptr vptr, Jptr jptr, Hptr hptr,
             const Eigen::Ref<const vec3r_t> &x) const {
    if constexpr (chaos::mapping::need_eval<Vptr>()) {
      vptr->fill(x.squaredNorm());
    }
    if constexpr (!std::is_same_v<Jptr, std::nullptr_t>) {
      jptr->fill(2 * x.transpose());
    }
    if constexpr (!std::is_same_v<Hptr, std::nullptr_t>) {
      hptr->fill(mat33r_t::Identity() * 2);
    }
  }
};

int main(int argc, char *argv[]) {
  poly_f f;
  vec3r_t x;
  x.setRandom();
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
