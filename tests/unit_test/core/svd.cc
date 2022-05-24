#include <catch2/catch.hpp>

#include "common/type.h"
#include "core/svd/closedFormSVD.h"
#include "core/svd/signedSVD.h"

using namespace chaos;
using namespace chaos::math;

TEST_CASE("test closed form svd", "[svd]") {
  //-> TODO.
  mat22r_t A;
  A.setRandom();
  A.setRandom();
  ClosedFormSVD2d<mat22r_t> svd;
  svd.compute(A);
  svd.compute(A, Eigen::ComputeFullU);
  svd.compute(A, Eigen::ComputeFullV);
  svd.compute(A, Eigen::ComputeFullV | Eigen::ComputeFullU);
  svd.singularValues();
  svd.matrixU();
  svd.matrixV();
  ClosedFormSVD2d<mat22r_t> svd2(A);
}

TEST_CASE("test signed svd", "[svd]") {
  //-> TODO. check this.
  SECTION("2d") {
    mat22r_t A22;
    A22.setRandom();
    SignedSVD<mat22r_t> svd22;
    svd22.compute(A22, Eigen::ComputeFullU);
    svd22.compute(A22, Eigen::ComputeFullV);
    svd22.compute(A22, Eigen::ComputeFullV | Eigen::ComputeFullU);
    svd22.matrixU();
    svd22.matrixV();
    svd22.singularValues();
    SignedSVD<mat22r_t> svd(A22);
  }
  SECTION("3d") {
    mat33r_t A33;
    A33.setRandom();
    SignedSVD<mat33r_t> svd33;
    svd33.compute(A33, Eigen::ComputeFullU);
    svd33.compute(A33, Eigen::ComputeFullV);
    svd33.compute(A33, Eigen::ComputeFullV | Eigen::ComputeFullU);
    svd33.matrixU();
    svd33.matrixV();
    svd33.singularValues();
    SignedSVD<mat33r_t> svd(A33);
  }
}
