#include "common/macro.h"
#include "common/type.h"
#include "utils/params/params.h"
#include "utils/params/valid.h"
#include "utils/stopwatch/stopwatch.h"
using namespace chaos;

struct params_t : utils::params_group_t {
  enum bench_compute_t { MATRIX_VECTOR_PROD, MATRIX_MATRIX_PROD };
  enum storage_layout_t {
    DYNAMIC_STORAGE_NO_MAP,
    DYNAMIC_STORAGE_WITH_MAP,
    STATIC_STORAGE,
    STATIC_STORAGE_WITH_MAP_X,
    STATIC_STORAGE_WITH_MAP_S
  };
  inline static const std::map<std::string, storage_layout_t>
      storage_layout_map{STRING_ENUM_MAP(DYNAMIC_STORAGE_NO_MAP),
                         STRING_ENUM_MAP(DYNAMIC_STORAGE_WITH_MAP),
                         STRING_ENUM_MAP(STATIC_STORAGE),
                         STRING_ENUM_MAP(STATIC_STORAGE_WITH_MAP_S),
                         STRING_ENUM_MAP(STATIC_STORAGE_WITH_MAP_X)};
  inline static const std::map<storage_layout_t, std::string>
      storage_layout_inverse_map{ENUM_STRING_MAP(DYNAMIC_STORAGE_NO_MAP),
                                 ENUM_STRING_MAP(DYNAMIC_STORAGE_WITH_MAP),
                                 ENUM_STRING_MAP(STATIC_STORAGE),
                                 ENUM_STRING_MAP(STATIC_STORAGE_WITH_MAP_X),
                                 ENUM_STRING_MAP(STATIC_STORAGE_WITH_MAP_S)};
  inline static const std::map<std::string, bench_compute_t> bench_compute_map{
      STRING_ENUM_MAP(MATRIX_MATRIX_PROD), STRING_ENUM_MAP(MATRIX_VECTOR_PROD)};
  inline static const std::map<bench_compute_t, std::string>
      bench_compute_inverse_map{ENUM_STRING_MAP(MATRIX_MATRIX_PROD),
                                ENUM_STRING_MAP(MATRIX_VECTOR_PROD)};

  params_t() {
    emplace_back({&storage, &repeated_N, &vector_N, &matrix_size, &compute});
    matrix_size.add_valid(utils::range_valid_t<unsigned>::create(2, 4));
    compute.add_valid(utils::enum_transform_valid_t<bench_compute_t>::create(
        bench_compute_map));
    storage.add_valid(utils::enum_transform_valid_t<storage_layout_t>::create(
        storage_layout_map));
  }

  void group_setup_complete_callback() override {
    benchmark_type = storage_layout_inverse_map.at(storage) + "." +
                     bench_compute_inverse_map.at(compute);
  };

  DEFINE_PARAM_DEFAULT(unsigned, repeated_N, "repeated times", 10);
  DEFINE_PARAM_DEFAULT(unsigned, vector_N, "num of matrix on a vector", 1000);
  DEFINE_PARAM_DEFAULT(unsigned, matrix_size,
                       "(squared) matrix dim{only support [2, 4]}", 2);
  DEFINE_PARAM_DEFAULT(bench_compute_t, compute, "benchmark computation case",
                       MATRIX_VECTOR_PROD);
  DEFINE_PARAM_DEFAULT(storage_layout_t, storage, "storage layout type",
                       DYNAMIC_STORAGE_NO_MAP);
  std::string benchmark_type;
};

void benchmark(const params_t &prm);

template <params_t::storage_layout_t storage_type>
void benchmark(const params_t &prm);

int main(int argc, char *argv[]) {
  DEFINE_APP_AND_PRM(app, "", params_t);

  benchmark(prm);
  return 0;
}

template <typename LHS, typename RHS, typename RES, typename FuncOnLhs,
          typename FuncOnRhs, typename FuncOnRes>
void run(const LHS &lhs, const RHS &rhs, RES &res, const params_t &prm,
         FuncOnLhs &&func_lhs, FuncOnRhs &&func_rhs, FuncOnRes &&func_res) {
  for (size_t i = 0; i < prm.repeated_N; ++i) {
    utils::STW_START(prm.benchmark_type);
    for (size_t j = 0; j < prm.vector_N; ++j) {
      func_res(res[j]) = func_lhs(lhs[j]) * func_rhs(rhs[j]);
    }
    utils::STW_STOP(prm.benchmark_type);
  }
}

const auto idmap = [](auto &&x) -> auto && { return x; };
#define map(dim)                                           \
  const auto mat##dim##map = [](auto &&x) {                \
    return Eigen::Map<mat##dim##dim##r_t>(x.data());       \
  };                                                       \
  const auto vec##dim##map = [](auto &&x) {                \
    return Eigen::Map<vec##dim##r_t>(x.data());            \
  };                                                       \
  const auto cmat##dim##map = [](auto &&x) {               \
    return Eigen::Map<const mat##dim##dim##r_t>(x.data()); \
  };                                                       \
  const auto cvec##dim##map = [](auto &&x) {               \
    return Eigen::Map<const vec##dim##r_t>(x.data());      \
  };                                                       \
  const auto xmat##dim##map = [](auto &&x) {               \
    return Eigen::Map<matxr_t>(x.data(), dim, dim);        \
  };                                                       \
  const auto xvec##dim##map = [](auto &&x) {               \
    return Eigen::Map<vecxr_t>(x.data(), dim);             \
  };                                                       \
  const auto cxmat##dim##map = [](auto &&x) {              \
    return Eigen::Map<const matxr_t>(x.data(), dim, dim);  \
  };                                                       \
  const auto cxvec##dim##map = [](auto &&x) {              \
    return Eigen::Map<const vecxr_t>(x.data(), dim);       \
  };                                                       \
  const auto xxmat##dim##map = [](auto &&x) {              \
    return mat##dim##map(xmat##dim##map(x));               \
  };                                                       \
  const auto xxvec##dim##map = [](auto &&x) {              \
    return vec##dim##map(xvec##dim##map(x));               \
  };                                                       \
  const auto cxxmat##dim##map = [](auto &&x) {             \
    return cmat##dim##map(cxmat##dim##map(x));             \
  };                                                       \
  const auto cxxvec##dim##map = [](auto &&x) {             \
    return cvec##dim##map(cxvec##dim##map(x));             \
  };

map(2);
map(3);
map(4);

#undef map

template <int dim>
std::tuple<std::vector<mat_t<real_t, dim, dim>>,
           std::vector<mat_t<real_t, dim, dim>>,
           std::vector<mat_t<real_t, dim, dim>>>
declare_mm() {
  std::vector<mat_t<real_t, dim, dim>> lhs, rhs, res;
  return {lhs, rhs, res};
}
template <int dim>
std::tuple<std::vector<mat_t<real_t, dim, dim>>,
           std::vector<vec_t<real_t, dim>>, std::vector<vec_t<real_t, dim>>>
declare_mv() {
  std::vector<mat_t<real_t, dim, dim>> lhs;
  std::vector<vec_t<real_t, dim>> rhs, res;
  return {lhs, rhs, res};
}

template <int compute, typename LHS, typename RHS, typename RES>
void generate(LHS &lhs, RHS &rhs, RES &res, unsigned N, unsigned dim) {
  lhs.resize(N);
  rhs.resize(N);
  res.resize(N);

  for (size_t i = 0; i < N; ++i) {
    lhs[i].setRandom(dim, dim);
    if constexpr (compute == params_t::MATRIX_VECTOR_PROD) {
      rhs[i].setRandom(dim);
      res[i].setRandom(dim);
    } else {
      rhs[i].setRandom(dim, dim);
      res[i].setRandom(dim, dim);
    }
  }
}

template <>
void benchmark<params_t::DYNAMIC_STORAGE_NO_MAP>(const params_t &prm) {
  std::vector<matxr_t> As;
  const auto &N = prm.vector_N.val;
  const auto &dim = prm.matrix_size.val;
  switch (prm.compute) {
    case params_t::MATRIX_VECTOR_PROD: {
      std::vector<vecxr_t> bs, xs;
      generate<params_t::MATRIX_VECTOR_PROD>(As, bs, xs, N, dim);
      run(As, bs, xs, prm, idmap, idmap, idmap);
      break;
    }
    case params_t::MATRIX_MATRIX_PROD: {
      std::vector<matxr_t> bs, xs;
      generate<params_t::MATRIX_MATRIX_PROD>(As, bs, xs, N, dim);
      run(As, bs, xs, prm, idmap, idmap, idmap);
      break;
    }
  }
}

template <>
void benchmark<params_t::DYNAMIC_STORAGE_WITH_MAP>(const params_t &prm) {
  const auto &N = prm.vector_N.val;
  const auto &dim = prm.matrix_size.val;
#define DIM(d)                                                       \
  if (dim == d) {                                                    \
    if (prm.compute == params_t::MATRIX_MATRIX_PROD) {               \
      auto [As, bs, xs] = declare_mm<-1>();                          \
      generate<params_t::MATRIX_MATRIX_PROD>(As, bs, xs, N, dim);    \
      run(As, bs, xs, prm, cmat##d##map, cmat##d##map, mat##d##map); \
    } else {                                                         \
      auto [As, bs, xs] = declare_mv<-1>();                          \
      generate<params_t::MATRIX_VECTOR_PROD>(As, bs, xs, N, dim);    \
      run(As, bs, xs, prm, cmat##d##map, cvec##d##map, vec##d##map); \
    }                                                                \
  }
  DIM(2);
  DIM(3);
  DIM(4);
#undef DIM
}

template <>
void benchmark<params_t::STATIC_STORAGE>(const params_t &prm) {
  const auto &N = prm.vector_N.val;
  const auto &dim = prm.matrix_size.val;
#define DIM(d)                                                    \
  if (dim == d) {                                                 \
    if (prm.compute == params_t::MATRIX_MATRIX_PROD) {            \
      auto [As, bs, xs] = declare_mm<d>();                        \
      generate<params_t::MATRIX_MATRIX_PROD>(As, bs, xs, N, dim); \
      run(As, bs, xs, prm, idmap, idmap, idmap);                  \
    } else {                                                      \
      auto [As, bs, xs] = declare_mv<d>();                        \
      generate<params_t::MATRIX_VECTOR_PROD>(As, bs, xs, N, dim); \
      run(As, bs, xs, prm, idmap, idmap, idmap);                  \
    }                                                             \
  }
  DIM(2);
  DIM(3);
  DIM(4);
#undef DIM
}

template <>
void benchmark<params_t::STATIC_STORAGE_WITH_MAP_S>(const params_t &prm) {
  const auto &N = prm.vector_N.val;
  const auto &dim = prm.matrix_size.val;
#define DIM(d)                                                             \
  if (dim == d) {                                                          \
    if (prm.compute == params_t::MATRIX_MATRIX_PROD) {                     \
      auto [As, bs, xs] = declare_mm<d>();                                 \
      generate<params_t::MATRIX_MATRIX_PROD>(As, bs, xs, N, dim);          \
      run(As, bs, xs, prm, cxxmat##d##map, cxxmat##d##map, xxmat##d##map); \
    } else {                                                               \
      auto [As, bs, xs] = declare_mv<d>();                                 \
      generate<params_t::MATRIX_VECTOR_PROD>(As, bs, xs, N, dim);          \
      run(As, bs, xs, prm, cxxmat##d##map, cxxvec##d##map, xxvec##d##map); \
    }                                                                      \
  }
  DIM(2);
  DIM(3);
  DIM(4);
#undef DIM
}

template <>
void benchmark<params_t::STATIC_STORAGE_WITH_MAP_X>(const params_t &prm) {
  const auto &N = prm.vector_N.val;
  const auto &dim = prm.matrix_size.val;
#define DIM(d)                                                          \
  if (dim == d) {                                                       \
    if (prm.compute == params_t::MATRIX_MATRIX_PROD) {                  \
      auto [As, bs, xs] = declare_mm<d>();                              \
      generate<params_t::MATRIX_MATRIX_PROD>(As, bs, xs, N, dim);       \
      run(As, bs, xs, prm, cxmat##d##map, cxmat##d##map, xmat##d##map); \
    } else {                                                            \
      auto [As, bs, xs] = declare_mv<d>();                              \
      generate<params_t::MATRIX_VECTOR_PROD>(As, bs, xs, N, dim);       \
      run(As, bs, xs, prm, cxmat##d##map, cxvec##d##map, xvec##d##map); \
    }                                                                   \
  }
  DIM(2);
  DIM(3);
  DIM(4);
#undef DIM
}

void benchmark(const params_t &prm) {
#define CASE(t) \
  case t:       \
    return benchmark<t>(prm)
  switch (prm.storage) {
    CASE(params_t::DYNAMIC_STORAGE_NO_MAP);
    CASE(params_t::DYNAMIC_STORAGE_WITH_MAP);
    CASE(params_t::STATIC_STORAGE);
    CASE(params_t::STATIC_STORAGE_WITH_MAP_X);
    CASE(params_t::STATIC_STORAGE_WITH_MAP_S);
  }
#undef CASE
}
