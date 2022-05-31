#include <catch2/catch.hpp>

#include "mapping/patt_helper.h"

using namespace chaos::mapping;

TEST_CASE("test function patt", "[mapping]") {
  SECTION("diagonal") {
    const int xdim = 3;
    auto patt = patt_helper::diag_patt(xdim);
    REQUIRE(patt != nullptr);
    CHECK(patt->size() == xdim);
    for (const auto &oo : *patt) {
      CHECK(oo.first == oo.second);
    }
  }
  SECTION("extract") {
    //-> squared A.
    SECTION("squared A") {
      Eigen::Matrix3d A;
      // clang-format off
      A <<
          1, 2, 3,
          0, 0, 4,
          7, 6, 5;
      // clang-format on
      SECTION("upper") {
        auto patt = patt_helper::extract_A_patt<true>(A);
        REQUIRE(patt != nullptr);
        CHECK(patt->size() == 5);
        CHECK(patt->count({0, 0}) == 1);
        CHECK(patt->count({0, 1}) == 1);
        CHECK(patt->count({0, 2}) == 1);
        CHECK(patt->count({1, 2}) == 1);
        CHECK(patt->count({2, 2}) == 1);
        CHECK(patt->count({1, 1}) == 0);
      }
      SECTION("full") {
        auto patt = patt_helper::extract_A_patt<false>(A);
        REQUIRE(patt != nullptr);
        CHECK(patt->size() == 7);
        CHECK(patt->count({0, 0}) == 1);
        CHECK(patt->count({0, 1}) == 1);
        CHECK(patt->count({0, 2}) == 1);
        CHECK(patt->count({1, 2}) == 1);
        CHECK(patt->count({2, 2}) == 1);
        CHECK(patt->count({2, 1}) == 1);
        CHECK(patt->count({2, 0}) == 1);
        CHECK(patt->count({1, 1}) == 0);
      }
    }
    //-> rectangle A.
    SECTION("rectangle A") {
      Eigen::Matrix<double, 2, 4> A;
      // clang-format off
      A <<
          1, 2, 3, 0,
          0, 0, 5, 4;
      // clang-format on
      auto patt = patt_helper::extract_A_patt<false>(A);
      REQUIRE(patt != nullptr);
      CHECK(patt->size() == 5);
      CHECK(patt->count({0, 0}) == 1);
      CHECK(patt->count({0, 1}) == 1);
      CHECK(patt->count({0, 2}) == 1);
      CHECK(patt->count({1, 2}) == 1);
      CHECK(patt->count({1, 3}) == 1);
    }
  }
  SECTION("self_adjoint") {
    Eigen::Matrix3d A;
    // clang-format off
    A <<
        1, 0, 2,
        3, 0, 0,
        0, 4, 0;
    // clang-format on
    auto patt = patt_helper::extract_A_patt<false>(A);
    REQUIRE(patt != nullptr);
    auto symPatt = patt_helper::self_adjoint_patt(patt.get());
    REQUIRE(symPatt != nullptr);
    CHECK(symPatt->size() == 7);
  }
}
