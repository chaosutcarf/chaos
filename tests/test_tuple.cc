#include "common/type.h"
#include "mapping/function.h"
#include "mapping/variable.h"

using namespace chaos::mapping;

struct A {
  template <typename Wrt, typename... Args>
  double eval(const Wrt &wrt, const variable::At<Args...> &at) {
    static_assert(sizeof...(Args) == 3, "Args shoule be 3.");
    const auto &[ls, ks, lens] = at.args;
    return impl(wrt, ls, ks, lens);
  }

  template <typename Wrt>
  double impl(const Wrt &wrt, const Eigen::Ref<const chaos::vecxr_t> &ls,
              const double *ks, int lens) {
    info_msg("wrt: {}", wrt);
    info_msg("ls: {}", ls);
    info_msg("lens: {}", lens);
    info_msg("ks: {}", Eigen::Map<const chaos::vecxr_t>(ks, lens));
    return wrt.sum();
  }
};

int main(int argc, char *argv[]) {
  A a;
  chaos::vec3r_t x, ls;
  x.setRandom();
  ls.setOnes();
  double ks[] = {2, 34, 2};

  info_msg("a.eval: {}", a.eval(x, variable::at(ls, ks, 3)));
  return 0;
}
