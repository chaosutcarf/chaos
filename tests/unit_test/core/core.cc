#include <catch2/catch.hpp>

#include "common/type_helper.h"
#include "core/utils.h"

using namespace chaos;

TEST_CASE("test core utils", "[core]") {
  vec3r_t w;
  w << 1, 2, 3;
  mat33r_t Skew = math::skew33<real_t>(w);
  mat33r_t ref;
  ref << 0, -3, 2, 3, 0, -1, -2, 1, 0;
  CHECK(std::equal_to<matxr_t>()(Skew, ref));
}

TEST_CASE("test core utils exp", "[core]") {
  //-> exp.
  CHECK(std::equal_to<matxr_t>()(math::exp(vec3r_t::Zero()),
                                 mat33r_t::Identity()));
  //-> [0, 0, 1]
  vec3r_t axis(0, 0, 1);
  mat33r_t R;
  R.setZero();
  R(0, 0) = R(1, 1) = cos(1);
  R(0, 1) = -sin(1);
  R(1, 0) = sin(1);
  R(2, 2) = 1;
  CHECK(std::equal_to<matxr_t>()(math::exp(axis), R));

  axis.setZero();
  axis[1] = 1;
  R.setZero();
  R(0, 0) = R(2, 2) = cos(1);
  R(2, 0) = -sin(1);
  R(0, 2) = sin(1);
  R(1, 1) = 1;
  CHECK(std::equal_to<matxr_t>()(math::exp(axis), R));

  axis.setZero();
  axis[0] = 1;
  R.setZero();
  R(1, 1) = R(2, 2) = cos(1);
  R(1, 2) = -sin(1);
  R(2, 1) = sin(1);
  R(0, 0) = 1;
  CHECK(std::equal_to<matxr_t>()(math::exp(axis), R));
}

TEST_CASE("test core utils log", "[core]") {
  //-> log.
  CHECK(std::equal_to<vecxr_t>()(math::log(mat33r_t::Identity()),
                                 vec3r_t::Zero()));
  //-> [0, 0, 1]
  vec3r_t axis(0, 0, 1);
  mat33r_t R;
  qtnr_t Q;
  R.setZero();
  R(0, 0) = R(1, 1) = cos(1);
  R(0, 1) = -sin(1);
  R(1, 0) = sin(1);
  R(2, 2) = 1;
  Q = R;
  CHECK(std::equal_to<vecxr_t>()(math::log(R), axis));
  CHECK(std::equal_to<vecxr_t>()(math::log(Q), axis));

  axis.setZero();
  axis[1] = 1;
  R.setZero();
  R(0, 0) = R(2, 2) = cos(1);
  R(2, 0) = -sin(1);
  R(0, 2) = sin(1);
  R(1, 1) = 1;
  Q = R;
  CHECK(std::equal_to<vecxr_t>()(math::log(R), axis));
  CHECK(std::equal_to<vecxr_t>()(math::log(Q), axis));

  axis.setZero();
  axis[0] = 1;
  R.setZero();
  R(1, 1) = R(2, 2) = cos(1);
  R(1, 2) = -sin(1);
  R(2, 1) = sin(1);
  R(0, 0) = 1;
  Q = R;
  CHECK(std::equal_to<vecxr_t>()(math::log(R), axis));
  CHECK(std::equal_to<vecxr_t>()(math::log(Q), axis));
}
