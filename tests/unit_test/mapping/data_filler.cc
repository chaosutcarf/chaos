#include <catch2/catch.hpp>

#include "common/numerical.h"
#include "mapping/basic_data_filler.h"

using namespace chaos;
using namespace chaos::mapping;
using namespace chaos::mapping::data_filler_concepts;

TEST_CASE("test scalar filler", "[data_filler]") {
  double res{0};
  SECTION("Override") {
    scalar_filler_t f(res);
    using type = decltype(f);
    CHECK(IsOverride<type>);
    CHECK(CanGetData<type>);
    CHECK(!CanGetData<scalar_filler_t<double, true, true>>);
    CHECK(!CanGetData<scalar_filler_t<double, true, false>>);
    CHECK(!CanGetData<scalar_filler_t<double, false, true>>);
    CHECK(!CanGetData<scalar_filler_t<double, false, false>>);
    CHECK(f.size() == 1);
    f.batch_fill(10);
    CHECK(numerical::near<double>(res, 10));
    //-> check fill.
    f.fill<false>(0, 1);
    CHECK(numerical::near<double>(res, 11));
    f.fill<true>(0, 1);
    CHECK(numerical::near<double>(res, 1));
    f.setZero();
    CHECK(numerical::near<double>(res, 0));
    CHECK(f.data() != nullptr);
  }
  SECTION("Accumulate") {
    scalar_filler_t<double, false> f(res);
    CHECK(numerical::near<double>(res, 0));
    f.batch_fill(10);
  }
}
// #include "mapping/data_filler.h"

// #include <catch2/catch.hpp>
// #include <functional>

// #include "common/type.h"
// #include "common/type_helper.h"

// using namespace chaos::mapping;

// TEST_CASE("test one dim filler", "[mapping]") {
//   SECTION("scalar") {
//     SECTION("override") {
//       double res{0};
//       one_dim_filler_t filler(res);
//       CHECK(filler.size() == 1);
//       CHECK(filler.data() == &res);
//       CHECK(filler.can_get_data == true);
//       CHECK(filler.override_mode == true);
//       //-> override.
//       filler.fill(0, 10);
//       CHECK(res == 10);
//       filler.fill(0, 5);
//       CHECK(res == 5);
//     }
//     SECTION("accumulate") {
//       double res{0};
//       one_dim_filler_t<double, false> filler(res);
//       CHECK(filler.size() == 1);
//       CHECK(filler.can_get_data == false);
//       CHECK(filler.override_mode == false);
//       //-> override.
//       filler.fill(0, 10);
//       CHECK(res == 10);
//       filler.fill(0, 5);
//       CHECK(res == 15);
//     }
//   }

//   SECTION("vector") {
//     SECTION("override") {
//       std::vector<double> res(10);
//       one_dim_filler_t filler(res);
//       CHECK(filler.size() == 10);
//       CHECK(filler.data() == res.data());
//       CHECK(filler.can_get_data == true);
//       CHECK(filler.override_mode == true);
//       CHECK(filler.can_parallel == true);
//       //-> override.
//       std::vector<double> ones(10, 1);
//       filler.batch_fill(ones);
//       CHECK_THAT(res, Catch::Matchers::Equals(ones));
//       std::vector<double> twos(10, 2);
//       filler.batch_fill(twos);
//       CHECK_THAT(res, Catch::Matchers::Equals(twos));
//     }
//     SECTION("accumulate") {
//       std::vector<double> res(10);
//       res.assign(10, 0);
//       one_dim_filler_t<decltype(res), false> filler(res);
//       CHECK(filler.size() == 10);
//       CHECK(filler.can_get_data == false);
//       CHECK(filler.override_mode == false);
//       CHECK(filler.can_parallel == true);
//       //-> override.
//       std::vector<double> ones(10, 1);
//       filler.batch_fill(ones);
//       CHECK_THAT(res, Catch::Matchers::Equals(ones));
//       std::vector<double> twos(10, 2);
//       std::vector<double> threes(10, 3);
//       filler.batch_fill(twos);
//       CHECK_THAT(res, Catch::Matchers::Equals(threes));
//     }
//   }

//   SECTION("Eigen::Vector") {
//     SECTION("override") {
//       Eigen::VectorXd res(10);
//       one_dim_filler_t filler(res);
//       CHECK(filler.size() == 10);
//       CHECK(filler.data() == res.data());
//       CHECK(filler.can_get_data == true);
//       CHECK(filler.override_mode == true);
//       CHECK(filler.can_parallel == true);
//       //-> override.
//       std::vector<double> ones(10, 1);
//       filler.batch_fill(ones);
//       Eigen::Map<chaos::vecxr_t> map_ones(ones.data(), 10);
//       CHECK(std::equal_to<chaos::vecxr_t>()(res, map_ones));
//       Eigen::VectorXd twos;
//       twos.setConstant(10, 2);
//       filler.batch_fill(twos);
//       CHECK(std::equal_to<chaos::vecxr_t>()(res, twos));
//     }
//     SECTION("accumulate") {
//       Eigen::VectorXd res(10);
//       res.setZero();
//       one_dim_filler_t<decltype(res), false> filler(res);
//       CHECK(filler.size() == 10);
//       CHECK(filler.can_get_data == false);
//       CHECK(filler.override_mode == false);
//       CHECK(filler.can_parallel == true);
//       //-> override.
//       std::vector<double> ones(10, 1);
//       filler.batch_fill(ones);
//       Eigen::Map<chaos::vecxr_t> map_ones(ones.data(), 10);
//       CHECK(std::equal_to<chaos::vecxr_t>()(res, map_ones));
//       std::vector<double> twos(10, 2);
//       std::vector<double> threes(10, 3);
//       filler.batch_fill(twos);
//       Eigen::Map<chaos::vecxr_t> map_threes(threes.data(), 10);
//       CHECK(std::equal_to<chaos::vecxr_t>()(res, map_threes));
//     }
//   }
// }

// TEST_CASE("test two dim filler", "[mapping]") {
//   SECTION("mat filler") {
//     SECTION("override") {
//       chaos::matxr_t res(2, 3);
//       mat_filler_t filler(res);
//       CHECK(filler.rows() == 2);
//       CHECK(filler.cols() == 3);
//       CHECK(filler.can_get_data == true);
//       CHECK(filler.data() == res.data());
//       CHECK(filler.override_mode == true);
//       chaos::matxr_t val(2, 3);
//       val.setRandom();
//       filler.batch_fill(val);
//       CHECK(std::equal_to<chaos::matxr_t>()(val, res));
//       filler.batch_fill(val);
//       CHECK(std::equal_to<chaos::matxr_t>()(val, res));
//     }
//     SECTION("UPPER") {
//       chaos::matxr_t res(3, 3);
//       res.setZero();
//       mat_filler_t<decltype(res), chaos::MATRIX_FILL_MODE::UPPER>
//       filler(res); CHECK(filler.rows() == 3); CHECK(filler.cols() == 3);
//       CHECK(filler.can_get_data == false);
//       CHECK(filler.override_mode == true);
//       chaos::matxr_t val(3, 3);
//       val.setRandom();
//       filler.batch_fill(val);
//       chaos::matxr_t trig = val.triangularView<Eigen::Upper>();
//       CHECK(std::equal_to<chaos::matxr_t>()(trig, res));
//       filler.batch_fill(val);
//       CHECK(std::equal_to<chaos::matxr_t>()(trig, res));
//     }
//     SECTION("LOWER") {
//       chaos::matxr_t res(3, 3);
//       res.setZero();
//       mat_filler_t<decltype(res), chaos::MATRIX_FILL_MODE::LOWER>
//       filler(res); CHECK(filler.rows() == 3); CHECK(filler.cols() == 3);
//       CHECK(filler.can_get_data == false);
//       CHECK(filler.override_mode == true);
//       chaos::matxr_t val(3, 3);
//       val.setRandom();
//       chaos::matxr_t trig = val.triangularView<Eigen::Upper>();
//       chaos::matxr_t diag = val.diagonal().asDiagonal();
//       filler.batch_fill(trig);
//       CHECK(std::equal_to<chaos::matxr_t>()(diag, res));
//       res.setZero();
//       filler.batch_fill(trig.transpose());
//       CHECK(std::equal_to<chaos::matxr_t>()(trig.transpose(), res));
//     }
//   }
// }
