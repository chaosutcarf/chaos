#include "core/linearsolver/linearsolver.h"

#include <catch2/catch.hpp>
#include <iostream>
#include <memory>

#include "common/numerical.h"
using namespace std;
using namespace chaos;
using namespace chaos::solver;

void check_linear_system(const csr_matr_t &A, const vecxr_t &b,
                         const vecxr_t &sol) {
#if defined(USE_PARDISO)
  for (size_t i = 0; i <= linear_solver_base::PARDISO_LDLT; ++i) {
#elif defined(USE_SUITESPARSE)
  for (size_t i = 0; i <= linear_solver_base::CHOLMOD_SIMPLICIAL_LDLT; ++i) {
#else
  for (size_t i = 0; i <= linear_solver_base::EIGEN_BUILTIN_ILU_BIPCG; ++i) {
#endif
    linear_solver_base::params_t prm;
    prm.maxits.set_val(-1);
    prm.tol.set_val(0);
    prm.type.set_val(static_cast<linear_solver_base::linear_solver_impl_t>(i));
    auto slv = linear_solver_t<>::create(prm);
    slv->compute(A);
    CHECK(slv->info() == Eigen::Success);
    vecxr_t x = slv->solve(b);
    CHECK(slv->info() == Eigen::Success);
    CHECK(numerical::is_zero((x - sol).cwiseAbs2().maxCoeff()));
    //-> check solve size:
    x.resize(b.size() + 1);
    CHECK_THROWS(slv->solve(b, x));
    matxr_t xx(b.size(), 2);
    CHECK_THROWS(slv->solve(b, xx));
  }

#if defined(USE_PARDISO)
  for (size_t i = 0; i <= linear_solver_base::PARDISO_LDLT; ++i) {
#elif defined(USE_SUITESPARSE)
  for (size_t i = 0; i <= linear_solver_base::CHOLMOD_SIMPLICIAL_LDLT; ++i) {
#else
  for (size_t i = 0; i <= linear_solver_base::EIGEN_BUILTIN_ILU_BIPCG; ++i) {
#endif
    linear_solver_base::params_t prm;
    prm.maxits.set_val(-1);
    prm.tol.set_val(0);
    prm.type.set_val(static_cast<linear_solver_base::linear_solver_impl_t>(i));
    auto slv = linear_solver_t<>::create(prm);
    slv->analyzePattern(A);
    slv->factorize(A);
    vecxr_t x = slv->solve(b);
    CHECK(slv->info() == Eigen::Success);
    CHECK(numerical::is_zero((x - sol).cwiseAbs2().maxCoeff()));
    if (i == linear_solver_base::EIGEN_BUILTIN_D_PCG) {
      auto iter_slv = (iterative_linear_solver_t<> *)(slv.get());
      iter_slv->setTolerance(1);
      CHECK(iter_slv->tolerance() == 1);
      iter_slv->setMaxIterations(10);
      CHECK(iter_slv->maxIterations() == 10);
      iter_slv->error();
      iter_slv->iterations();
    }
  }
}

TEST_CASE("test linearsolver diagonal", "[linearsolver]") {
  for (size_t i = 2; i < 100; ++i) {
    Eigen::DiagonalMatrix<real_t, -1> D(i);
    D.diagonal() = vecxr_t::Random(i).cwiseAbs2() + vecxr_t::Ones(i);
    vecxr_t b(i);
    b.setRandom();
    vecxr_t sol = b.cwiseQuotient(D.diagonal());
    check_linear_system(D.toDenseMatrix().sparseView(), b, sol);
  }
}

TEST_CASE("test symmetric positive definite", "[linearsolver]") {
  for (size_t i = 2; i < 10; ++i) {
    matxr_t Ai(i, i);
    Ai.setRandom();
    matxr_t denseA = Ai * Ai.transpose() + matxr_t::Identity(i, i);
    vecxr_t b(i);
    b.setRandom();
    vecxr_t sol = denseA.inverse() * b;
    check_linear_system(denseA.sparseView(), b, sol);
  }
}
