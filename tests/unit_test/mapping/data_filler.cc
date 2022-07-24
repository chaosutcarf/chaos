// #include "mapping/data_filler.h"

// #include <catch2/catch.hpp>

// #include "common/numerical.h"
// #include "common/type.h"
// #include "common/type_helper.h"
// #include "mapping/basic_data_filler.h"
// #include "mapping/filler/one_dim_filler.h"
// #include "mapping/filler/two_dim_filler.h"

// using namespace chaos;
// using namespace chaos::mapping;
// using namespace chaos::mapping::data_filler_concepts;

// TEST_CASE("test Traits::CanGetData", "[data_filler]") {
//   //------------Override, AllowGetData, Parallel-------
//   CHECK(OneDimTraits<true, true, true>::CanGetData);
//   CHECK(!OneDimTraits<true, false, true>::CanGetData);
//   CHECK(!OneDimTraits<false, true, true>::CanGetData);
//   CHECK(!OneDimTraits<false, false, true>::CanGetData);
//   CHECK(OneDimTraits<true, true, false>::CanGetData);
//   CHECK(!OneDimTraits<true, false, false>::CanGetData);
//   CHECK(!OneDimTraits<false, true, false>::CanGetData);
//   CHECK(!OneDimTraits<false, false, false>::CanGetData);
//   //---MatFillMode, Override, AllowGetData, Parallel---
//   CHECK(TwoDimTraits<MATRIX_FILL_MODE::FULL, true, true, true>::CanGetData);
//   CHECK(TwoDimTraits<MATRIX_FILL_MODE::FULL, true, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, true, false, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, true, false, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, false, true, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, false, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, false, false, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::FULL, false, false, false>::CanGetData);

//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, true, true, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, true, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, true, false, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, true, false, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, false, true, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, false, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::LOWER, false, false, true>::CanGetData);
//   CHECK(
//       !TwoDimTraits<MATRIX_FILL_MODE::LOWER, false, false, false>::CanGetData);

//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, true, true, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, true, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, true, false, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, true, false, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, false, true, true>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, false, true, false>::CanGetData);
//   CHECK(!TwoDimTraits<MATRIX_FILL_MODE::UPPER, false, false, true>::CanGetData);
//   CHECK(
//       !TwoDimTraits<MATRIX_FILL_MODE::UPPER, false, false, false>::CanGetData);
// }

// TEST_CASE("test scalar filler", "[data_filler]") {
//   double res{0};
//   SECTION("Override") {
//     scalar_filler_t f(res);
//     using type = decltype(f);
//     CHECK(OneDimFillerConcept<type>);
//     CHECK(OneDimTraitsConcept<type::Traits>);
//     CHECK(type::Traits::Override);
//     CHECK(type::Traits::CanGetData);

//     CHECK(f.size() == 1);
//     f.fill(10);
//     CHECK(numerical::near<double>(res, 10));
//     //-> check fill.
//     f.fill<false>(0, 1);
//     CHECK(numerical::near<double>(res, 11));
//     f.fill<true>(0, 1);
//     CHECK(numerical::near<double>(res, 1));
//     f.setZero();
//     CHECK(numerical::near<double>(res, 0));
//     CHECK(f.data() == &res);
//   }
//   SECTION("Accumulate") {
//     scalar_filler_t<double, false> f(res);
//     using type = decltype(f);
//     CHECK(!type::Traits::Override);
//     CHECK(!type::Traits::CanGetData);
//     CHECK(numerical::near<double>(res, 0));
//     f.fill(10);
//     CHECK(numerical::near<double>(res, 10));
//     f.fill(10);
//     CHECK(numerical::near<double>(res, 20));
//     f.setZero();
//     CHECK(numerical::near<double>(res, 0));
//   }
// }

// TEST_CASE("test vector filler", "[data_filler]") {
//   vecxr_t res;
//   res.setZero(3);
//   SECTION("Override") {
//     one_dim_filler_t filler(res);
//     using type = decltype(filler);
//     CHECK(OneDimFillerConcept<type>);
//     CHECK(OneDimTraitsConcept<type::Traits>);
//     CHECK(type::Traits::Override);
//     CHECK(type::Traits::CanGetData);
//     CHECK(filler.size() == res.size());
//     CHECK(filler.data() == res.data());
//     filler.fill(vec3r_t::Ones());
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Ones()));
//     filler.fill(vec3r_t::Ones());
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Ones()));
//     filler.fill<false>(vec3r_t::Ones());
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Constant(2)));
//     filler.setZero();
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Zero()));
//   }
//   SECTION("Accumulate") {
//     one_dim_filler_t<decltype(res), false> filler(res);
//     using type = decltype(filler);
//     CHECK(OneDimFillerConcept<type>);
//     CHECK(OneDimTraitsConcept<type::Traits>);
//     CHECK(!type::Traits::Override);
//     CHECK(!type::Traits::CanGetData);
//     CHECK(filler.size() == res.size());
//     filler.fill(vec3r_t::Ones());
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Ones()));
//     filler.fill(vec3r_t::Ones());
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Constant(2)));
//     filler.setZero();
//     CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Zero()));
//   }
// }

// TEST_CASE("test two dim filler", "[data_filler]") {
//   matxr_t res(2, 3);
//   res.setZero();
//   SECTION("Override") {
//     mat_filler_t filler(res);
//     using type = decltype(filler);
//     CHECK(TwoDimFillerConcept<type>);
//     CHECK(TwoDimTraitsConcept<type::Traits>);
//     CHECK(type::Traits::Override);
//     CHECK(type::Traits::CanGetData);
//     CHECK(filler.rows() == res.rows());
//     CHECK(filler.cols() == res.cols());
//     mat_t<double, 2, 3> val;
//     val.setRandom();
//     filler.fill(val);
//     CHECK(std::equal_to<matxr_t>()(res, val));
//     filler.fill(val);
//     CHECK(std::equal_to<matxr_t>()(res, val));
//     filler.setZero();
//     CHECK(std::equal_to<matxr_t>()(res, mat_t<double, 2, 3>::Zero()));
//     CHECK(filler.data() == res.data());
//   }
//   SECTION("Accumulate") {
//     mat_filler_t<decltype(res), MATRIX_FILL_MODE::FULL, false> filler(res);
//     using type = decltype(filler);
//     CHECK(TwoDimFillerConcept<type>);
//     CHECK(TwoDimTraitsConcept<type::Traits>);
//     CHECK(!type::Traits::Override);
//     CHECK(!type::Traits::CanGetData);
//     CHECK(filler.rows() == res.rows());
//     CHECK(filler.cols() == res.cols());
//     mat_t<double, 2, 3> val;
//     val.setRandom();
//     filler.fill(val);
//     CHECK(std::equal_to<matxr_t>()(res, val));
//     filler.fill(val);
//     CHECK(std::equal_to<matxr_t>()(res, 2 * val));
//     filler.setZero();
//     CHECK(std::equal_to<matxr_t>()(res, mat_t<double, 2, 3>::Zero()));
//   }
// }
