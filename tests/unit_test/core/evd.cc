#include "core/evd/evd.h"

#include <algorithm>
#include <catch2/catch.hpp>

#include "common/type_helper.h"

using namespace chaos;
using namespace std;

TEST_CASE("eigen value decomposition", "[evd]") {
  matxr_t U, A, I;
  vecxr_t Lambda;

  for (int i = 100; i <= 300; i += 100) {
    //-> generate orthogonal matrix.
    U.setRandom(i, i);
    I.setIdentity(i, i);
    Lambda.setRandom(i);
    std::sort(&Lambda[0], &Lambda[0] + i,
              [](real_t a, real_t b) { return std::abs(a) < std::abs(b); });
    U = U.fullPivHouseholderQr().matrixQ();
    CHECK(std::equal_to<matxr_t>()(U.transpose() * U, I));
    A = U.transpose() * Lambda.asDiagonal() * U;

    SECTION("Dense MatType") {
      matxr_t basis;
      vecxr_t lambda;
      //-> full eigen decomposition.
      int ncov = math::symmetric_evd<Eigen::Lower>(
          (matxr_t)A.triangularView<Eigen::Lower>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd<Eigen::Lower>(
          (matxr_t)A.triangularView<Eigen::Lower>(), i, &basis, &lambda,
          Spectra::SortRule::LargestMagn);
      std::reverse(lambda.begin(), lambda.end());
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, matxr_t>(
          (matxr_t)A.triangularView<Eigen::Lower>(), I, i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, matxr_t>(
          (matxr_t)A.triangularView<Eigen::Lower>(), I, i, &basis, &lambda,
          Spectra::SortRule::LargestMagn);
      std::reverse(lambda.begin(), lambda.end());
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd<Eigen::Upper>(
          (matxr_t)A.triangularView<Eigen::Upper>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, matxr_t>(
          (matxr_t)A.triangularView<Eigen::Upper>(), I, i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd(A, i, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd(A, I, i, &basis, &lambda,
                                  Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));

      //-> partial eigen decomposition.
      ncov = math::symmetric_evd<Eigen::Lower>(
          (matxr_t)A.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Lower>(
          (matxr_t)A.triangularView<Eigen::Lower>(), I, 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_evd<Eigen::Upper>(
          (matxr_t)A.triangularView<Eigen::Upper>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      ncov = math::symmetric_gevd<Eigen::Upper>(
          (matxr_t)A.triangularView<Eigen::Upper>(), I, 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      //-> check failed layout.
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_evd<Eigen::Upper>(
          (matxr_t)A.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Upper>(
          (matxr_t)A.triangularView<Eigen::Lower>(), I, 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_evd(A, 20, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd(A, I, 20, &basis, &lambda,
                                  Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
    }

    SECTION("CSC") {
      csc_matr_t sA = A.sparseView();
      matxr_t basis;
      vecxr_t lambda;
      //-> full eigen decomposition.
      int ncov = math::symmetric_evd<Eigen::Lower>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), I.sparseView(), i,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd<Eigen::Upper>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), I.sparseView(), i,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd(sA, i, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd(sA, csc_matr_t(I.sparseView()), i, &basis,
                                  &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_evd<Eigen::Lower, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), I.sparseView(), 20,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_evd<Eigen::Upper, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      //-> check failed layout.
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csc_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), I.sparseView(), 20,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      //-> check failed layout.
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_evd<Eigen::Upper, csc_matr_t>(
          sA.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csc_matr_t>(
          sA.triangularView<Eigen::Lower>(), I.sparseView(), 20, &basis,
          &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_evd(sA, 20, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd(sA, (csc_matr_t)I.sparseView(), 20, &basis,
                                  &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
    }
    SECTION("CSR") {
      csr_matr_t sA = A.sparseView();
      matxr_t basis;
      vecxr_t lambda;
      //-> full eigen decomposition.
      int ncov = math::symmetric_evd<Eigen::Lower, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), I.sparseView(), i,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd<Eigen::Upper, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), i, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), I.sparseView(), i,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);
      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_evd(sA, i, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);

      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      ncov = math::symmetric_gevd(sA, (csr_matr_t)I.sparseView(), i, &basis,
                                  &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == i);

      CHECK(std::equal_to<vecxr_t>()(Lambda, lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_evd<Eigen::Lower, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Lower, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Lower>(), I.sparseView(), 20,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_evd<Eigen::Upper, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csr_matr_t>(
          (csc_matr_t)sA.triangularView<Eigen::Upper>(), I.sparseView(), 20,
          &basis, &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      //-> check failed layout.
      ncov = math::symmetric_evd<Eigen::Upper, csr_matr_t>(
          sA.triangularView<Eigen::Lower>(), 20, &basis, &lambda,
          Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      ncov = math::symmetric_gevd<Eigen::Upper, csr_matr_t>(
          sA.triangularView<Eigen::Lower>(), I.sparseView(), 20, &basis,
          &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(!std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_evd(sA, 20, &basis, &lambda,
                                 Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
      //-> partial eigen decomposition.
      ncov = math::symmetric_gevd(sA, (csr_matr_t)I.sparseView(), 20, &basis,
                                  &lambda, Spectra::SortRule::SmallestMagn);
      CHECK(ncov == 20);
      CHECK(std::equal_to<vecxr_t>()(Lambda.topRows(20), lambda));
    }
  }
}
