#include "linearsolver.h"

#include <Eigen/IterativeLinearSolvers>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseLU>
#include <Eigen/SparseQR>
#include <Eigen/UmfPackSupport>
#include <memory>

#include "utils/logger/logger.h"

#ifdef USE_SUITESPARSE
#include <Eigen/CholmodSupport>
#endif

#ifdef USE_PARDISO
#include "pardiso_solver.h"
#endif

using namespace std;
using namespace Eigen;
namespace chaos::solver {

template <MATRIX_FILL_MODE Mode>
std::unique_ptr<linear_solver_t<Mode>> linear_solver_t<Mode>::create(
    linear_solver_impl_t type, real_t tol, size_t maxits) {
  params_t prm;
  prm.type.set_val(type);
  prm.tol.set_val(tol);
  prm.maxits.set_val(maxits);
  return create(prm);
}

template <MATRIX_FILL_MODE Mode>
std::unique_ptr<linear_solver_t<Mode>> linear_solver_t<Mode>::create(
    const params_t &prm) {
  const auto setup_iterative = [&prm](iterative_linear_solver_t<Mode> *slv) {
    if (slv != nullptr) {
      if (prm.maxits > 0) {
        slv->setMaxIterations(prm.maxits);
      }
      if (prm.tol > 0) {
        slv->setTolerance(prm.tol);
      }
    }
  };

  //-> TODO::figure out why cholmod should revert the lower/upper part of
  // triangle matrix???
  //-> eigen 3.3.91 has fix this bug, use eigen 3.4 instead.
#if EIGEN_VERSION_AT_LEAST(3, 3, 91)
  constexpr int CHOLMOD_MODE = (int)Mode & Upper ? Upper : Lower;
#else
  constexpr int CHOLMOD_MODE = int(Mode) & Upper ? Lower : Upper;
#endif
  constexpr int EIGEN_MODE = (int)Mode & Upper ? Upper : Lower;
  switch (prm.type.val) {
    //-> Eigen bultin llt and ldlt only works for ColMajor.
    case EIGEN_BUILTIN_LLT:
      return make_unique<eigen_ls_wrapper_t<
          SimplicialLLT<sp_mat_t<real_t, Eigen::ColMajor>, EIGEN_MODE>,
          Mode>>();
    case EIGEN_BUILTIN_LDLT:
      return make_unique<eigen_ls_wrapper_t<
          SimplicialLDLT<sp_mat_t<real_t, Eigen::ColMajor>, EIGEN_MODE>,
          Mode>>();
    case EIGEN_BUILTIN_D_PCG: {
      auto ptr = make_unique<eigen_iterative_ls_wrapper_t<
          ConjugateGradient<csr_matr_t, (int)Mode,
                            DiagonalPreconditioner<real_t>>,
          Mode>>();
      setup_iterative(ptr.get());
      return ptr;
    }
    case EIGEN_BUILTIN_IC_PCG: {
      auto ptr = make_unique<eigen_iterative_ls_wrapper_t<
          ConjugateGradient<csr_matr_t, (int)Mode,
                            IncompleteCholesky<real_t, EIGEN_MODE>>,
          Mode>>();
      setup_iterative(ptr.get());
      return ptr;
    }

    case EIGEN_BUILTIN_D_BIPCG: {
      auto ptr = make_unique<eigen_iterative_ls_wrapper_t<
          BiCGSTAB<csr_matr_t, DiagonalPreconditioner<real_t>>, Mode>>();
      setup_iterative(ptr.get());
      return ptr;
    }

    case EIGEN_BUILTIN_ILU_BIPCG: {
      auto ptr = make_unique<eigen_iterative_ls_wrapper_t<
          BiCGSTAB<csr_matr_t, IncompleteLUT<real_t>>, Mode>>();
      setup_iterative(ptr.get());
      return ptr;
    }
#ifdef USE_SUITESPARSE
    case CHOLMOD_SIMPLICIAL_LDLT:
      return make_unique<eigen_ls_wrapper_t<
          CholmodSimplicialLDLT<csr_matr_t, CHOLMOD_MODE>, Mode>>();
    case CHOLMOD_SIMPLICIAL_LLT:
      return make_unique<eigen_ls_wrapper_t<
          CholmodSimplicialLLT<csr_matr_t, CHOLMOD_MODE>, Mode>>();
    case CHOLMOD_SUPERNODAL_LLT:
      return make_unique<eigen_ls_wrapper_t<
          CholmodSupernodalLLT<csr_matr_t, CHOLMOD_MODE>, Mode>>();
    case UmfPackLU:
      return make_unique<
          eigen_ls_wrapper_t<Eigen::UmfPackLU<csr_matr_t>, Mode>>();
#endif
#ifdef USE_PARDISO
    case PARDISO_LDLT:
      return make_unique<pardiso_solver_t<Mode>>(
          PARDISO_MATRIX_TYPE::REAL_SYMMETRIC_INDEFINITE);
    case PARDISO_LLT:
      return make_unique<pardiso_solver_t<Mode>>(
          PARDISO_MATRIX_TYPE::REAL_SYMMETRIC_POSITIVE_DEFINITE);
#endif
    default:
      warn_msg("linear_solver_type[{}] not yet supported.", prm.type.val);
      return nullptr;
  }
}

#define INSTANTIATION_LINEAR_SOLVER(mode)                                    \
  template std::unique_ptr<linear_solver_t<MATRIX_FILL_MODE::mode>>          \
  linear_solver_t<MATRIX_FILL_MODE::mode>::create(const params_t &prm);      \
  template std::unique_ptr<linear_solver_t<MATRIX_FILL_MODE::mode>>          \
  linear_solver_t<MATRIX_FILL_MODE::mode>::create(linear_solver_impl_t type, \
                                                  real_t tol, size_t maxits);

INSTANTIATION_LINEAR_SOLVER(FULL);
INSTANTIATION_LINEAR_SOLVER(LOWER);
INSTANTIATION_LINEAR_SOLVER(UPPER);
}  // namespace chaos::solver
