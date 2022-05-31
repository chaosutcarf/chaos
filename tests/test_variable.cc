#include <type_traits>

#include "common/type.h"
#include "mapping/variable.h"
#include "utils/logger/logger.h"
#include "utils/stopwatch/stopwatch.h"
using namespace chaos;
using namespace chaos::mapping;
extern "C" {
#include "maxima/spring_energy.h"
}

void h(real_t *out) { info_msg("here"); }
void h(real_t *out, const Eigen::Ref<const vec4r_t> &x, const real_t *k,
       const real_t *l) {
  mass_spring_2d_val_(out, x.data(), l, k);
}

template <typename... Args>
void f(const variable::At<Args...> &in, real_t *out) {
  // static_assert(std::tuple_size_v<decltype(in.args)> == 2, "ensure at (x,
  // p)"); const auto &[x, prm] = in.args;
  // static_assert(std::is_base_of_v<Eigen::MatrixBase<std::decay_t<decltype(x)>>,
  //                                 std::decay_t<decltype(x)>> == true,
  //               "x is eigenBase");
  // x[0] = 10;
  // CHAOS_ASSERT(x.size() == 4);
  // info_msg("addr: {:p}, {:p}", (void *)&x, (void *)&prm);
  // mass_spring_2d_val_(out, x.data(), prm.data(), prm.data() + 1);
  const auto &[x, k, l] = in.args;
  h(out, x, k, l);
}

template <typename... Args>
void g(real_t *out, Args &&...args) {
  h(out, args...);
}

template <int a>
constexpr void H() {
  if constexpr ((a & 1) != 0) {
    printf("1");
  }
  if constexpr ((a & 2) != 0) {
    printf("2");
  }
  if constexpr ((a & 4) != 0) {
    printf("3");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  real_t out;
  real_t prm[2];
  prm[0] = prm[1] = 2;
  mat2xr_t pos;
  pos.resize(2, 10);
  pos.setZero();
  pos.row(1).setZero();
  for (size_t i = 0; i < 10; ++i) {
    pos(0, i) = i;
  }
  vecxr_t prms(5);

  Eigen::Map<vec4r_t> x(pos.data());

  // info_msg("addr: {:p}, {:p}", (void *)&x, (void *)&prm);
  real_t res = 0;
  utils::STW_START("start");
  for (size_t i = 0; i < 100000; ++i) {
    // g(&out, x, &prm[0], &prm[1]);
    // f(variable::at(x, &prm[0], &prm[1]), &out);
    g(&out);
    res += out;
  }
  utils::STW_STOP("start");

  info_msg("{}", res);

  H<1>();
  H<1 | 2>();
  H<1 | 4>();
  H<1 | 2 | 4>();
  return 0;
}
