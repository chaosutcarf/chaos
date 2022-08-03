#include <algorithm>
#include <cstddef>

#include "common/type.h"
#include "core/evd/evd.h"
#include "geometry/line.h"
#include "spring_chain.h"
#include "utils/logger/logger.h"
#include "utils/params/params.h"
#include "utils/stopwatch/stopwatch.h"
extern "C" {
#include "maxima/spring_energy.h"
}
using namespace chaos;
using namespace std;

#define MS_EVAL(order, ...)             \
  if constexpr (space_dim == 2) {       \
    mass_spring_2d##order(__VA_ARGS__); \
  } else {                              \
    mass_spring_3d##order(__VA_ARGS__); \
  }

template <int space_dim>
struct spring_chain_energy {
  spring_chain_energy(const spring_chain_t *spring_chain)
      : spring_chain(spring_chain) {}

#define CHAIN_PRM                                         \
  x.data() + space_dim *i, &spring_chain->rest_length[i], \
      &spring_chain->stiffness[i]
  void Val(const Eigen::Ref<const vecxr_t> &x, real_t &val) const {
    //-> assume x is an ordered chain structure.
    const auto &N = spring_chain->N;
    CHAOS_ASSERT((size_t)x.size() == space_dim * (N + 1));
    vecxr_t batch_eval(N);
    batch_eval.setZero();
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
      MS_EVAL(_val_, &batch_eval[i], CHAIN_PRM);
    }
    val = batch_eval.sum();
  }
  void Gra(const Eigen::Ref<const vecxr_t> &x, Eigen::Ref<vecxr_t> g) const {
    const auto &N = spring_chain->N;
    CHAOS_ASSERT((size_t)x.size() == space_dim * (N + 1));
    CHAOS_ASSERT(g.size() == x.size());
    //-> for even.
#pragma omp parallel for
    for (size_t i = 0; i < N; i += 2) {
      MS_EVAL(_jac_, g.data() + space_dim * i, CHAIN_PRM);
    }
    //-> for odd.
#pragma omp parallel for
    for (size_t i = 1; i < N; i += 2) {
      MS_EVAL(_jac_, g.data() + space_dim * i, CHAIN_PRM);
    }
  }
  void Hes(const Eigen::Ref<const vecxr_t> &x, coo_list_t<real_t> &coo) const {
    const auto &N = spring_chain->N;
    CHAOS_ASSERT((size_t)x.size() == space_dim * (N + 1));
    coo.reserve(coo.size() + N * space_dim * (space_dim * 2 + 1));
    std::vector<Eigen::Matrix<real_t, space_dim * 2, space_dim * 2>> batch_eval(
        N);
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
      MS_EVAL(_hes_, batch_eval[i].data(), CHAIN_PRM);
    }
    //-> assemble.
    for (size_t i = 0; i < N; ++i) {
      //-> each block, fill upper symmetry part.
      for (size_t p = 0; p < space_dim * 2; ++p) {
        for (size_t q = p; q < space_dim * 2; ++q) {
          coo.emplace_back(p, q, batch_eval[i](p, q));
        }
      }
    }
  }
  const spring_chain_t *spring_chain;
#undef CHAIN_PRM
};

// template <int space_dim>
// struct spring_net_energy {
//   void Val(const Eigen::Ref<const vecxr_t> &x, real_t &val) const;
//   void Gra(const Eigen::Ref<const vecxr_t> &x, Eigen::Ref<vecxr_t> g) const;
//   void Hes(const Eigen::Ref<const vecxr_t> &x, coo_list_t<real_t> &coo)
//   const; const spring_net *spring_net;
// };

struct params_t : public utils::params_group_t {
  params_t() {
    emplace_back({&num_of_segs, &space_dim, &Ym, &rest_length, &right_end});
  }
  DEFINE_PARAM_DEFAULT(unsigned, num_of_segs, "number of segments", 100);
  DEFINE_PARAM_DEFAULT(int, space_dim, "space dim", 2);
  DEFINE_PARAM_DEFAULT(real_t, Ym, "homo Ym", 1);
  DEFINE_PARAM_DEFAULT(real_t, rest_length, "rest length", 1);
  DEFINE_PARAM_DEFAULT(real_t, right_end, "right end", 1);
};

template <int space_dim>
int run(const params_t &prm);

int run(const params_t &prm);

int main(int argc, char *argv[]) {
  DEFINE_APP_AND_PRM(app, "", params_t);
  run(prm);

  return 0;
}

template <int space_dim>
int run(const params_t &prm) {
  const auto &N = prm.num_of_segs.val;
  spring_chain_t spring_chain(N);
  //-> setup rest length and stiffness.
  std::fill_n(spring_chain.stiffness.begin(), N, prm.Ym / prm.rest_length);
  std::fill_n(spring_chain.rest_length.begin(), N, prm.rest_length);
  //-> generate line.
  auto line = geometry::line_t<space_dim>(0, prm.right_end, N);
  spring_chain_energy<space_dim> energy(&spring_chain);

  //-> extract DoF.
  Eigen::Map<const vecxr_t> x(line.pos().data(), line.pos().size());
  info_msg("spaceDof: {}, totalDof: {}", space_dim, x.size());

  real_t val = 0;
  utils::STW_START("eval.val");
  energy.Val(x, val);
  utils::STW_STOP("eval.val");

  vecxr_t gra(x.size());
  gra.setZero();
  utils::STW_START("eval.jac");
  energy.Gra(x, gra);
  utils::STW_STOP("eval.jac");

  coo_list_t<real_t> coo;
  csr_matr_t csr(x.size(), x.size());
  utils::STW_START("eval.hes");
  energy.Hes(x, coo);
  csr.setFromTriplets(coo.begin(), coo.end());
  utils::STW_STOP("eval.hes");

  vecxr_t lam_lo, lam_hi;
  math::symmetric_evd(csr, 8, nullptr, &lam_lo);
  math::symmetric_evd(csr, 8, nullptr, &lam_hi, Spectra::SortRule::LargestMagn);
  info_msg("Val: {}\nGra: {}\nHes:\n{}\n{}", val, gra.norm(), lam_lo, lam_hi);

  return 0;
}

int run(const params_t &prm) {
#define CASE(d) \
  case d:       \
    return run<d>(prm);

  switch (prm.space_dim) {
    CASE(1);
    CASE(2);
    CASE(3);
    default:
      return -1;
  }
}
