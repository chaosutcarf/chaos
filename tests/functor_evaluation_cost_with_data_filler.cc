#include <algorithm>
#include <cstddef>

#include "common/type.h"
#include "core/evd/evd.h"
#include "geometry/line.h"
#include "mapping/data_filler.h"
#include "mapping/function.h"
#include "spring_chain.h"
#include "utils/logger/logger.h"
#include "utils/params/params.h"
#include "utils/stopwatch/stopwatch.h"
extern "C" {
#include "maxima/spring_energy.h"
}
using namespace chaos;
using namespace std;

#define MS_EVAL(order, ...)              \
  if constexpr (space_dim == 1) {        \
    mass_spring_1d##order(__VA_ARGS__);  \
  } else if constexpr (space_dim == 2) { \
    mass_spring_2d##order(__VA_ARGS__);  \
  } else {                               \
    mass_spring_3d##order(__VA_ARGS__);  \
  }

template <int space_dim>
struct spring_chain_energy
    : public mapping::function_base<spring_chain_energy<space_dim>> {
  //-> data.
  spring_chain_energy(const spring_chain_t *spring_chain)
      : spring_chain(spring_chain) {}

  static constexpr index_t fdim = 1;
  index_t _nx_impl() const { return (spring_chain->N + 1) * space_dim; }

  FUNCTION_SPLIT_IMPL();

#define CHAIN_PRM                                         \
  x.data() + space_dim *i, &spring_chain->rest_length[i], \
      &spring_chain->stiffness[i]

  template <typename OutPtr>
  void _val_impl(OutPtr valptr, const Eigen::Ref<const vecxr_t> &x) const {
    //-> assume x is an ordered chain structure.
    const auto &N = spring_chain->N;
    vecxr_t batch_eval(N);
    batch_eval.setZero();
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
      MS_EVAL(_val_, &batch_eval[i], CHAIN_PRM);
    }
    valptr->fill(0, batch_eval.sum());
  }

  template <typename OutPtr>
  void _jac_impl(OutPtr jacptr, const Eigen::Ref<const vecxr_t> &x) const {
    const auto &N = spring_chain->N;

    vecxr_t g;
    real_t *g_data = nullptr;

    if constexpr (jacptr->can_get_data) {
      g_data = jacptr->data();
    } else {
      utils::STW_START("g.allocate");
      g.resize((N + 1) * space_dim);
      g_data = g.data();
      utils::STW_STOP("g.allocate");
    }

    //-> for even.
    utils::STW_START("g.eval");
#pragma omp parallel for
    for (size_t i = 0; i < N; i += 2) {
      MS_EVAL(_jac_, g_data + space_dim * i, CHAIN_PRM);
    }
    //-> for odd.
#pragma omp parallel for
    for (size_t i = 1; i < N; i += 2) {
      MS_EVAL(_jac_, g_data + space_dim * i, CHAIN_PRM);
    }
    utils::STW_STOP("g.eval");

    if constexpr (!jacptr->can_get_data) {
      utils::STW_START("g.fill");
      jacptr->template batch_fill(g.transpose());
      utils::STW_STOP("g.fill");
    }
  }

  template <typename OutPtr>
  void _hes_impl(OutPtr hesptr, const Eigen::Ref<const vecxr_t> &x) const {
    const auto &N = spring_chain->N;
    //-> TODO.
    std::vector<Eigen::Matrix<real_t, space_dim * 2, space_dim * 2>> batch_eval(
        N);
#pragma omp parallel for
    for (size_t i = 0; i < N; ++i) {
      MS_EVAL(_hes_, batch_eval[i].data(), CHAIN_PRM);
    }
    //-> assemble.
    for (size_t i = 0; i < N; ++i) {
      for (size_t p = 0; p < space_dim * 2; ++p) {
        for (size_t q = p; q < space_dim * 2; ++q) {
          hesptr->fill(p, q, batch_eval[i](p, q));
        }
      }
    }
  }
  const spring_chain_t *spring_chain;
#undef CHAIN_PRM
};

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
  info_msg("spaceDof: {}, totalDof: {}", space_dim, energy.Nx());

  real_t val = 0;
  utils::STW_START("eval.val");
  energy.Val(mapping::one_dim_filler_t(val), x);
  utils::STW_STOP("eval.val");

  vecxr_t gra(x.size());
  gra.setZero();
  utils::STW_START("eval.jac");
  energy.Jac(mapping::gra_filler_t(gra), x);
  utils::STW_STOP("eval.jac");

  coo_list_t<real_t> coo;
  coo.reserve(coo.size() + N * space_dim * (space_dim * 2 + 1));
  csr_matr_t csr(x.size(), x.size());
  utils::STW_START("eval.hes");
  energy.Hes(mapping::coo_filler_t(coo, x.size(), x.size()), x);
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
