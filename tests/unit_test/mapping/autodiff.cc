#include "mapping/autodiff.h"

#include <catch2/catch.hpp>

#include "common/numerical.h"
#include "common/type.h"
#include "common/type_helper.h"
#include "mapping/data_filler.h"
#include "utils/logger/logger.h"

using namespace chaos;
using namespace chaos::mapping;

template <int Xdim>
struct auto_poly_f : public autodiff_function_base<auto_poly_f<Xdim>, Xdim, 1> {
  template <typename T>
  T _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
    return x.squaredNorm();
  }
};

template <int Xdim>
struct auto_vec_f : public autodiff_function_base<auto_vec_f<Xdim>, Xdim, 2> {
  template <typename T>
  vec_t<T, 2> _mapsto(const Eigen::Ref<const vec_t<T>> &x) const {
    return vec_t<T, 2>(x.squaredNorm(), x.sum());
  }
};

TEST_CASE("test autodiff for compile time xdim and fdim", "[mapping]") {
  SECTION("real valued function") {
    auto_poly_f<3> f;
    vec3r_t x;
    x.setRandom();
    CHECK(f.Nx() == 3);
    CHECK(f.Nf() == 1);
    real_t val;
    vec3r_t jac;
    mat33r_t hes;
    f.Val(one_dim_filler_t(val), x);
    f.Jac(gra_filler_t(jac), x);
    f.Hes(mat_filler_t(hes), x);
    CHECK(numerical::near(val, x.squaredNorm()));
    CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
    CHECK(std::equal_to<matxr_t>()(hes, 2 * mat33r_t::Identity()));

    val = 0;
    jac.setZero();
    hes.setZero();
    f.ValJacHes(one_dim_filler_t(val), gra_filler_t(jac), mat_filler_t(hes), x);
    CHECK(numerical::near(val, x.squaredNorm()));
    CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
    CHECK(std::equal_to<matxr_t>()(hes, 2 * mat33r_t::Identity()));

    val = 0;
    jac.setZero();
    f.ValJac(one_dim_filler_t(val), gra_filler_t(jac), x);
    CHECK(numerical::near(val, x.squaredNorm()));
    CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
  }
  SECTION("vector valued function") {
    auto_vec_f<3> f;
    CHECK(f.Nx() == 3);
    CHECK(f.Nf() == 2);
  }
}
