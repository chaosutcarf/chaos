#include "mapping/filler_wrapper.hh"

#include <catch2/catch.hpp>

#include "common/numerical.h"
#include "common/type.h"
#include "common/type_helper.h"
#include "mapping/filler.hh"
#include "utils/logger/logger.h"

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
    ScalarFiller<double, false> f(res);
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

TEST_CASE("Test Vector Filler", "[filler_wrapper]") {
  vec3r_t res;
  res.setZero();
  SECTION("Override") {
    VectorFiller f(res);
    using type = decltype(f);
    CHECK(OneDimFillerConcept<type>);
    using Traits = type::Traits;
    CHECK(Traits::Override());
    CHECK(Traits::CanGetData());
    CHECK(Traits::CanParallel());
    CHECK(f.size() == res.size());
    default_1d_batch_fill(f, vec3r_t::Ones());
    CHECK(std::equal_to<vecxr_t>()(res, vec3r_t::Ones()));
    default_1d_batch_fill(f, vec3r_t::Ones());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
    CHECK(f.data() == res.data());
    f.setZero();
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Zero()));
    f.fill(0, 1);
    f.fill(1, 1);
    f.fill(2, 1);
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
    CHECK_THROWS(f.fill(3, 1));
  }

  SECTION("Accumulate") {
    VectorFiller<decltype(res), false> f(res);
    using type = decltype(f);
    CHECK(OneDimFillerConcept<type>);
    using Traits = type::Traits;
    CHECK(!Traits::Override());
    CHECK(!Traits::CanGetData());
    CHECK(Traits::CanParallel());
    CHECK(f.size() == res.size());
    default_1d_batch_fill(f, vec3r_t::Ones());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
    default_1d_batch_fill(f, vec3r_t::Ones());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Constant(2)));
    CHECK_THROWS(f.fill(3, 1));
  }
}

TEST_CASE("test Matrix filler", "[filler_wrapper]") {
  SECTION("DenseMatrix") {
    Eigen::Matrix<real_t, 3, 4> res;
    res.setZero();
    SECTION("Override") {
      MatrixFiller f(res);
      using type = decltype(f);
      CHECK(TwoDimFillerConcept<type>);
      using Traits = type::Traits;
      CHECK(Traits::Override());
      CHECK(Traits::CanParallel());
      CHECK(Traits::CanGetData());
      CHECK(f.rows() == 3);
      CHECK(f.cols() == 4);
      CHECK_THROWS(default_2d_batch_fill(f, mat33r_t::Zero()));
      decltype(res) dat;
      dat.setConstant(1);
      default_2d_batch_fill(f, dat);
      CHECK(std::equal_to<matxr_t>()(res, dat));
      default_2d_batch_fill(f, dat);
      CHECK(std::equal_to<matxr_t>()(res, dat));
      CHECK(f.data() == res.data());
    }
    SECTION("Accumulate") {
      MatrixFiller<decltype(res), MATRIX_FILL_MODE::FULL, false> f(res);
      using type = decltype(f);
      CHECK(TwoDimFillerConcept<type>);
      using Traits = type::Traits;
      CHECK(!Traits::Override());
      CHECK(f.rows() == 3);
      CHECK(f.cols() == 4);
      decltype(res) dat;
      dat.setConstant(1);
      default_2d_batch_fill(f, dat);
      CHECK(std::equal_to<matxr_t>()(res, dat));
      default_2d_batch_fill(f, dat);
      CHECK(std::equal_to<matxr_t>()(res, 2 * dat));
    }
  }
  SECTION("SparseMatrix") {
    csr_matr_t res(3, 4);
    res.reserve(12);
    SECTION("Override") {
      MatrixFiller<decltype(res), MATRIX_FILL_MODE::FULL, true, false> f(res);
      using type = decltype(f);
      CHECK(TwoDimFillerConcept<type>);
      using Traits = type::Traits;
      CHECK(Traits::Override());
      CHECK(f.rows() == 3);
      CHECK(f.cols() == 4);
      mat_t<real_t, 3, 4> dat;
      dat.setConstant(1);
      default_2d_batch_fill(f, dat);
      res.makeCompressed();
      CHECK(std::equal_to<matxr_t>()(res.toDense(), dat));
      default_2d_batch_fill(MatrixFiller(res), dat);
      CHECK(std::equal_to<matxr_t>()(res.toDense(), dat));
    }
    SECTION("Accumulate") {
      MatrixFiller<decltype(res), MATRIX_FILL_MODE::FULL, false, false> f(res);
      using type = decltype(f);
      CHECK(TwoDimFillerConcept<type>);
      using Traits = type::Traits;
      CHECK(!Traits::Override());
      CHECK(f.rows() == 3);
      CHECK(f.cols() == 4);
      mat_t<real_t, 3, 4> dat;
      dat.setConstant(1);
      default_2d_batch_fill(f, dat);
      res.makeCompressed();
      CHECK(std::equal_to<matxr_t>()(res.toDense(), dat));
      default_2d_batch_fill(
          MatrixFiller<decltype(res), MATRIX_FILL_MODE::FULL, false>(res), dat);
      CHECK(std::equal_to<matxr_t>()(res.toDense(), 2 * dat));
    }
  }
}

TEST_CASE("Test Gra Filler", "[filler_wrapper]") {
  vec3r_t res;
  res.setZero();
  SECTION("Override") {
    GraFiller f(res);
    using type = decltype(f);
    using Traits = FillerTraits<type>;
    CHECK(TwoDimFillerConcept<type>);
    CHECK(Traits::Override());
    CHECK(Traits::CanParallel());
    CHECK(Traits::CanGetData());
    CHECK(Traits::MatFillMode() == MATRIX_FILL_MODE::FULL);
    CHECK(f.rows() == 1);
    CHECK(f.cols() == res.size());
    CHECK_THROWS(f.fill(1, 1, 1));
    default_2d_batch_fill(f, vec3r_t::Ones().transpose());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
    default_2d_batch_fill(f, vec3r_t::Ones().transpose());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
  }
  SECTION("Accumulate") {
    GraFiller<decltype(res), false> f(res);
    using type = decltype(f);
    using Traits = FillerTraits<type>;
    CHECK(TwoDimFillerConcept<type>);
    CHECK(Traits::Override() == false);
    CHECK(Traits::CanParallel());
    CHECK(!Traits::CanGetData());
    CHECK(Traits::MatFillMode() == MATRIX_FILL_MODE::FULL);
    CHECK(f.rows() == 1);
    CHECK(f.cols() == res.size());
    default_2d_batch_fill(f, vec3r_t::Ones().transpose());
    CHECK(std::equal_to<vec3r_t>()(res, vec3r_t::Ones()));
    default_2d_batch_fill(f, vec3r_t::Ones().transpose());
    CHECK(std::equal_to<vec3r_t>()(res, 2 * vec3r_t::Ones()));
  }
}

TEST_CASE("test coo filler", "[filler_wrapper]") {
  coo_list_t<real_t> res;
  COOFiller f(res, 3, 3);
  using type = decltype(f);
  CHAOS_DEBUG_ASSERT(TwoDimFillerConcept<type>);
  using Traits = type::Traits;
  CHAOS_DEBUG_ASSERT(!Traits::Override());
  CHAOS_DEBUG_ASSERT(!Traits::CanParallel());
  CHAOS_DEBUG_ASSERT(!Traits::CanGetData());
  mat33r_t dat;
  dat.setConstant(1);
  default_2d_batch_fill(f, dat);
  csr_matr_t mat(3, 3);
  mat.setFromTriplets(res.begin(), res.end());
  CHECK(std::equal_to<matxr_t>()(mat.toDense(), dat));
}
