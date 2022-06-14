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

    SECTION("independent.call") {
      f.Val(one_dim_filler_t(val), x);
      f.Jac(gra_filler_t(jac), x);
      f.Hes(mat_filler_t(hes), x);
      CHECK(numerical::near(val, x.squaredNorm()));
      CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
      CHECK(std::equal_to<matxr_t>()(hes, 2 * mat33r_t::Identity()));
    }

    SECTION("together.call") {
      f.ValJacHes(one_dim_filler_t(val), gra_filler_t(jac), mat_filler_t(hes),
                  x);
      CHECK(numerical::near(val, x.squaredNorm()));
      CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
      CHECK(std::equal_to<matxr_t>()(hes, 2 * mat33r_t::Identity()));
    }

    SECTION("valjac") {
      f.ValJac(one_dim_filler_t(val), gra_filler_t(jac), x);
      CHECK(numerical::near(val, x.squaredNorm()));
      CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
    }

    SECTION("jaches") {
      f.JacHes(gra_filler_t(jac), mat_filler_t(hes), x);
      CHECK(std::equal_to<vecxr_t>()(jac, 2 * x));
      CHECK(std::equal_to<matxr_t>()(hes, 2 * mat33r_t::Identity()));
    }
  }
  SECTION("vector valued function") {
    auto_vec_f<3> f;
    CHECK(f.Nx() == 3);
    CHECK(f.Nf() == 2);

    vec3r_t x;
    x.setRandom();
    vec2r_t y;
    y.setRandom();
    matxr_t jac;
    matxr_t hes;
    jac.resize(2, 3);
    hes.resize(6, 3);
    vec2r_t expected_y;
    matxr_t expected_J, expected_H;
    expected_y[0] = x.squaredNorm();
    expected_y[1] = x.sum();
    expected_J.resize(2, 3);
    expected_J.row(0) = 2 * x;
    expected_J.row(1).setOnes();
    expected_H.resize(6, 3);
    expected_H.setZero();
    expected_H.col(0).reshaped(2, 3)(0, 0) = 2;
    expected_H.col(1).reshaped(2, 3)(0, 1) = 2;
    expected_H.col(2).reshaped(2, 3)(0, 2) = 2;

    SECTION("independent.call") {
      f.Val(one_dim_filler_t(y), x);
      f.Jac(mat_filler_t(jac), x);
      f.Hes(mat_filler_t(hes), x);
      CHECK(std::equal_to<vecxr_t>()(y, expected_y));
      CHECK(std::equal_to<matxr_t>()(jac, expected_J));
      CHECK(std::equal_to<matxr_t>()(hes, expected_H));
    }
    SECTION("together.call") {
      f.ValJacHes(one_dim_filler_t(y), mat_filler_t(jac), mat_filler_t(hes), x);
      CHECK(std::equal_to<vecxr_t>()(y, expected_y));
      CHECK(std::equal_to<matxr_t>()(jac, expected_J));
      CHECK(std::equal_to<matxr_t>()(hes, expected_H));
    }
    SECTION("valjac") {
      f.ValJac(one_dim_filler_t(y), mat_filler_t(jac), x);
      CHECK(std::equal_to<vecxr_t>()(y, expected_y));
      CHECK(std::equal_to<matxr_t>()(jac, expected_J));
    }
    SECTION("jaches") {
      f.JacHes(mat_filler_t(jac), mat_filler_t(hes), x);
      CHECK(std::equal_to<matxr_t>()(jac, expected_J));
      CHECK(std::equal_to<matxr_t>()(hes, expected_H));
    }
  }
}
