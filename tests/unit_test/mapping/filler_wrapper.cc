#include "mapping/filler_wrapper.hh"

#include <catch2/catch.hpp>

#include "common/numerical.h"
#include "common/type.h"
#include "common/type_helper.h"
#include "mapping/filler.hh"

using namespace chaos;
using namespace chaos::mapping;

template <bool _Override = false, bool _CanParallel = false,
          MATRIX_FILL_MODE _MatFillMode = MATRIX_FILL_MODE::FULL,
          bool _AllowGetData = false>
struct TraitsTemplate {
  CONSTEXPR_VAR(Override);
  CONSTEXPR_VAR(CanParallel);
  CONSTEXPR_VAR(MatFillMode);
  CONSTEXPR_VAR(AllowGetData);
};

TEST_CASE("Test FillerTraits", "[filler_traits]") {
  SECTION("Default traits value") {
    //-> check default traits value.
    using Traits = FillerTraits<int>;
    CHECK(Traits::CanGetData() == false);
    CHECK(Traits::CanParallel() == false);
    CHECK(Traits::Override() == false);
    CHECK(Traits::MatFillMode() == MATRIX_FILL_MODE::FULL);
  }

  SECTION("Customize") {
    CHECK(FillerTraits<TraitsTemplate<true>>::Override() == true);
    CHECK(FillerTraits<TraitsTemplate<false>>::Override() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true>>::CanParallel() == true);
    CHECK(FillerTraits<TraitsTemplate<true, false>>::CanParallel() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::FULL>>::
              MatFillMode() == MATRIX_FILL_MODE::FULL);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::LOWER>>::
              MatFillMode() == MATRIX_FILL_MODE::LOWER);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::UPPER>>::
              MatFillMode() == MATRIX_FILL_MODE::UPPER);
    //-> check can get data.
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::FULL,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::FULL,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::FULL,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::FULL,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::UPPER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::UPPER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::UPPER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::UPPER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::LOWER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::LOWER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::LOWER,
                                      false>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::LOWER,
                                      false>>::CanGetData() == false);
    //-> can get data is set to true:
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::FULL,
                                      true>>::CanGetData() == true);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::FULL,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::FULL,
                                      true>>::CanGetData() == true);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::FULL,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::UPPER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::UPPER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::UPPER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::UPPER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, true, MATRIX_FILL_MODE::LOWER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, true, MATRIX_FILL_MODE::LOWER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<true, false, MATRIX_FILL_MODE::LOWER,
                                      true>>::CanGetData() == false);
    CHECK(FillerTraits<TraitsTemplate<false, false, MATRIX_FILL_MODE::LOWER,
                                      true>>::CanGetData() == false);
  }
}

TEST_CASE("Test Scalar Filler", "[filler_wrapper]") {
  double res{0};
  SECTION("Override") {
    ScalarFiller f(res);
    using type = decltype(f);
    CHECK(OneDimFillerConcept<type>);
    CHECK(TwoDimFillerConcept<type>);
    //-> check traits.
    using Traits = FillerTraits<type>;
    CHECK(Traits::Override());
    CHECK(Traits::CanGetData());
    //-> check fill behavior.
    CHECK(f.size() == 1);
    CHECK(f.rows() == 1);
    CHECK(f.cols() == 1);
    f.fill(10);
    CHECK(numerical::near<double>(res, 10));
    //-> check onedim fill.
    f.fill<false>(0, 1);
    CHECK(numerical::near<double>(res, 11));
    //-> check twodim fill.
    f.fill<true>(0, 0, 1);
    CHECK(numerical::near<double>(res, 1));
    default_1d_batch_fill(f, 2);
    CHECK(res == 2);
    CHECK(numerical::near<double>(res, 2));
    default_2d_batch_fill(f, 3);
    CHECK(numerical::near<double>(res, 3));
    default_1d_batch_fill<false>(f, 2);
    CHECK(numerical::near<double>(res, 5));
    default_2d_batch_fill<false>(f, 3);
    CHECK(numerical::near<double>(res, 8));
    f.setZero();
    CHECK(numerical::near<double>(res, 0));
    //-> check data.
    if constexpr (Traits::CanGetData()) {
      CHECK(f.data() == &res);
    }
    //-> check throws
    CHECK_THROWS(f.fill(1, 1));
    CHECK_THROWS(f.fill(1, 1, 1));
  }
  SECTION("Accumulate") {
    ScalarFiller<false> f(res);
    using type = decltype(f);
    CHECK(OneDimFillerConcept<type>);
    CHECK(TwoDimFillerConcept<type>);
    using Traits = FillerTraits<type>;
    CHECK(!Traits::Override());
    CHECK(!Traits::CanGetData());
    CHECK(!HasFunctionData<type>);
    f.setZero();
    CHECK(numerical::near<double>(res, 0));
    f.fill(10);
    CHECK(numerical::near<double>(res, 10));
    f.fill<false>(0, 1);
    CHECK(numerical::near<double>(res, 11));
    default_1d_batch_fill(f, 1);
    CHECK(numerical::near<double>(res, 12));
    default_2d_batch_fill(f, 2);
    CHECK(numerical::near<double>(res, 14));
    f.fill<false>(0, 0, 1);
    CHECK(numerical::near<double>(res, 15));
    //-> check throws
    CHECK_THROWS(f.fill<false>(0, 1, 1));
    CHECK_THROWS(f.fill<false>(1, 1));
  }
}
