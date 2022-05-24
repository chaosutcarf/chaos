#include "evd.h"

#include <Spectra/MatOp/SparseCholesky.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/MatOp/SparseSymShiftSolve.h>
#include <Spectra/SymEigsShiftSolver.h>
#include <Spectra/SymEigsSolver.h>
#include <Spectra/SymGEigsShiftSolver.h>
#include <Spectra/SymGEigsSolver.h>

#include <Eigen/Eigenvalues>

using namespace Spectra;
namespace chaos::math {
template <typename Solver>
int solve_impl(Solver &slv, matxr_t *basis, vecxr_t *lambda,
               Spectra::SortRule selection, Spectra::SortRule sorting,
               size_t maxits, real_t tol) {
  slv.init();
  int ncov = slv.compute(selection, maxits, tol, sorting);
  if (slv.info() == Spectra::CompInfo::Successful) {
    if (basis != nullptr) {
      *basis = slv.eigenvectors();
    }
    if (lambda != nullptr) {
      *lambda = slv.eigenvalues();
    }
  }
  return ncov;
}

template <typename Solver>
int full_solve_impl(Solver &slv, matxr_t *basis, vecxr_t *lambda,
                    const Spectra::SortRule &rule) {
  int ncov = 0;
  if (slv.info() == Eigen::Success) {
    const auto &ev = slv.eigenvalues();
    ncov = ev.size();
    if (rule != Spectra::SortRule::SmallestAlge) {
      //-> sort.
      std::vector<int> ids(ncov);
      for (int i = 0; i < ncov; ++i) {
        ids[i] = i;
      }
      std::sort(ids.begin(), ids.end(), [&ev, &rule](int a, int b) {
        switch (rule) {
          case Spectra::SortRule::SmallestMagn:
            return std::abs(ev[a]) < std::abs(ev[b]);
          case Spectra::SortRule::LargestMagn:
            return std::abs(ev[a]) > std::abs(ev[b]);
          case Spectra::SortRule::LargestAlge:
            return ev[a] > ev[b];
          default:
            critical_msg("symmetric sort error!");
        }
      });
      if (basis != nullptr) {
        const auto &vecs = slv.eigenvectors();
        basis->resize(vecs.rows(), vecs.cols());
        for (size_t i = 0; i < ids.size(); ++i) {
          basis->col(i) = vecs.col(ids[i]);
        }
      }
      if (lambda != nullptr) {
        lambda->resize(ev.size());
        for (size_t i = 0; i < ids.size(); ++i) {
          (*lambda)[i] = ev[ids[i]];
        }
      }
    } else {
      if (basis != nullptr) {
        *basis = slv.eigenvectors();
      }
      if (lambda != nullptr) {
        *lambda = slv.eigenvalues();
      }
    }
  }
  return ncov;
}

void symmetric_valid_rule(const Spectra::SortRule &rule) {
  CHAOS_ASSERT(rule == Spectra::SortRule::SmallestMagn ||
                   rule == Spectra::SortRule::SmallestAlge ||
                   rule == Spectra::SortRule::LargestMagn ||
                   rule == Spectra::SortRule::LargestAlge,
               rule);
}

std::pair<int, int> get_nev_ncv(int rows, int num, int ncv) {
  int nev = std::min<int>(rows - 1, num);
  ncv = std::min<int>(rows, ncv > 0 ? nev + ncv : (-ncv + 1) * nev);
  return {nev, ncv};
}

//-> return value is the number of convergence basis
template <int Uplo, typename MatType>
int symmetric_evd(const MatType &A, int num, matxr_t *basis, vecxr_t *lambda,
                  const Spectra::SortRule &rule, const spectra_params_t &prm) {
  CHAOS_ASSERT(A.rows() == A.cols());
  CHAOS_ASSERT(basis != nullptr || lambda != nullptr);
  symmetric_valid_rule(rule);
  if (num >= A.rows()) {
    debug_msg("evd.full");
    //-> perform full eigen decomposition.
    //-> notice: Only the lower triangular part of the matrix is
    // referenced.
    Eigen::SelfAdjointEigenSolver<MatType> slv;
    int Option =
        basis == nullptr ? Eigen::EigenvaluesOnly : Eigen::ComputeEigenvectors;
    if constexpr (Uplo == Eigen::Lower) {
      slv.compute(A, Option);
    } else {
      slv.compute(A.transpose(), Option);
    }
    return full_solve_impl(slv, basis, lambda, rule);
  } else {
    //-> perform partial eigen decomposition.
    int nev, ncv;
    std::tie(nev, ncv) = get_nev_ncv(A.rows(), num, prm.ncv);
    if (rule >= Spectra::SortRule::SmallestMagn &&
        rule <= Spectra::SortRule::SmallestAlge) {
      try {
        if constexpr (std::is_same<csr_matr_t, MatType>::value ||
                      std::is_same<csc_matr_t, MatType>::value) {
          debug_msg("evd.partial.sparse");
          //-> perform y_out = (A-\sigma I)^{-1} * x_in
          using OpType = SparseSymShiftSolve<real_t, Uplo, MatType::Options>;
          OpType op(A);
          SymEigsShiftSolver<OpType> slv(op, nev, ncv, prm.shift_eps);
          return solve_impl(slv, basis, lambda,
                            (Spectra::SortRule)((int)rule - 4), rule,
                            prm.maxits, prm.tol);
        } else {
          //-> TODO: NEED CHECK
          debug_msg("evd.partial.dense");
          //-> perform y_out = (A-\sigma I)^{-1} * x_in
          using OpType = DenseSymShiftSolve<real_t, Uplo, MatType::Options>;
          OpType op(A);
          SymEigsShiftSolver<OpType> slv(op, nev, ncv, prm.shift_eps);
          return solve_impl(slv, basis, lambda,
                            (Spectra::SortRule)((int)rule - 4), rule,
                            prm.maxits, prm.tol);
        }
      } catch (std::invalid_argument &e) {
        warn_msg("{}, use non-shift version.", e.what());
      }
    }

    if constexpr (std::is_same<csr_matr_t, MatType>::value ||
                  std::is_same<csc_matr_t, MatType>::value) {
      debug_msg("evd.partial.sparse.h");
      //-> perform y_out = A * x_in
      using OpType = SparseSymMatProd<real_t, Uplo, MatType::Options>;
      OpType op(A);
      SymEigsSolver<OpType> slv(op, nev, ncv);
      return solve_impl(slv, basis, lambda, rule, rule, prm.maxits, prm.tol);
    } else {
      //-> TODO: NEED CHECK
      debug_msg("evd.partial.dense.h");
      //-> perform y_out = A * x_in
      using OpType = DenseSymMatProd<real_t, Uplo, MatType::Options>;
      OpType op(A);
      SymEigsSolver<OpType> slv(op, nev, ncv);
      return solve_impl(slv, basis, lambda, rule, rule, prm.maxits, prm.tol);
    }
  }
}

template <int Uplo, typename MatType>
int symmetric_gevd(const MatType &A, const MatType &B, int num, matxr_t *basis,
                   vecxr_t *lambda, const Spectra::SortRule &rule,
                   const spectra_params_t &prm) {
  CHAOS_ASSERT(A.rows() == A.cols() && B.rows() == B.cols() &&
               A.cols() == B.cols());
  CHAOS_ASSERT(basis != nullptr || lambda != nullptr);
  symmetric_valid_rule(rule);
  if (num >= A.rows()) {
    debug_msg("gevd.full");
    //-> perform full general eigen decomposition.
    //-> notice: Only the lower triangular part of the matrix is
    // referenced.
    Eigen::GeneralizedSelfAdjointEigenSolver<matxr_t> slv;
    if constexpr (Uplo == Eigen::Lower) {
      slv.compute(A, B);
    } else {
      slv.compute(A.transpose(), B.transpose());
    }
    return full_solve_impl(slv, basis, lambda, rule);
  } else {
    //-> perform partial general eigen decomposition.
    int nev, ncv;
    std::tie(nev, ncv) = get_nev_ncv(A.rows(), num, prm.ncv);
    if (rule >= Spectra::SortRule::SmallestMagn &&
        rule <= Spectra::SortRule::SmallestAlge) {
      try {
        if constexpr (std::is_same<csr_matr_t, MatType>::value ||
                      std::is_same<csc_matr_t, MatType>::value) {
          debug_msg("gevd.partial.sparse");
          //-> perform y_out = (A-\sigma B)^{-1} * x_in
          using OpType =
              Spectra::SymShiftInvert<real_t, Eigen::Sparse, Eigen::Sparse,
                                      Uplo, Uplo, MatType::Options,
                                      MatType::Options>;
          //-> perform y_out = B * x_in
          using BOpType =
              Spectra::SparseSymMatProd<real_t, Uplo, MatType::Options>;
          OpType op(A, B);
          BOpType Bop(B);
          SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert>
              slv(op, Bop, nev, ncv, prm.shift_eps);
          return solve_impl(slv, basis, lambda,
                            (Spectra::SortRule)((int)rule - 4), rule,
                            prm.maxits, prm.tol);
        } else {
          //-> TODO: NEED CHECK
          debug_msg("gevd.partial.dense");
          //-> perform y_out = (A-\sigma B)^{-1} * x_in
          using OpType =
              Spectra::SymShiftInvert<real_t, Eigen::Dense, Eigen::Dense, Uplo,
                                      Uplo, MatType::Options, MatType::Options>;
          //-> perform y_out = B * x_in
          using BOpType =
              Spectra::DenseSymMatProd<real_t, Uplo, MatType::Options>;
          OpType op(A, B);
          BOpType Bop(B);
          SymGEigsShiftSolver<OpType, BOpType, Spectra::GEigsMode::ShiftInvert>
              slv(op, Bop, nev, ncv, prm.shift_eps);
          return solve_impl(slv, basis, lambda,
                            (Spectra::SortRule)((int)rule - 4), rule,
                            prm.maxits, prm.tol);
        }
      } catch (std::invalid_argument &e) {
        warn_msg("{}, use non-shift version.", e.what());
      }
    }

    if constexpr (std::is_same<csr_matr_t, MatType>::value ||
                  std::is_same<csc_matr_t, MatType>::value) {
      debug_msg("gevd.partial.sparse.h");
      //-> perform y_out = A * x_in
      using OpType = Spectra::SparseSymMatProd<real_t, Uplo, MatType::Options>;
      //-> perform y_out = B^{-1} * x_in
      using BOpType = Spectra::SparseCholesky<real_t, Uplo, MatType::Options>;
      OpType op(A);
      BOpType Bop(B);
      SymGEigsSolver<OpType, BOpType, GEigsMode::Cholesky> slv(op, Bop, nev,
                                                               ncv);
      return solve_impl(slv, basis, lambda, rule, rule, prm.maxits, prm.tol);
    } else {
      //-> TODO: NEED CHECK
      debug_msg("gevd.partial.dense.h");
      //-> perform y_out = A * x_in
      using OpType = Spectra::DenseSymMatProd<real_t, Uplo, MatType::Options>;
      //-> perform y_out = B^{-1} * x_in
      using BOpType = Spectra::DenseCholesky<real_t, Uplo, MatType::Options>;
      OpType op(A);
      BOpType Bop(B);
      SymGEigsSolver<OpType, BOpType, GEigsMode::Cholesky> slv(op, Bop, nev,
                                                               ncv);
      return solve_impl(slv, basis, lambda, rule, rule, prm.maxits, prm.tol);
    }
  }
}

template <int Uplo, typename MatType, bool dense>
int symmetric_subspace_gevd(const MatType &A, const MatType &B,
                            const matxr_t &S, int num, matxr_t *basis,
                            vecxr_t *lambda, const Spectra::SortRule &rule,
                            const spectra_params_t &prm) {
  symmetric_valid_rule(rule);
  int ncv = 0;
  if constexpr (dense || std::is_same<matxr_t, MatType>::value) {
    debug_msg("in dense subspace");
    ncv = symmetric_gevd<Eigen::Lower, matxr_t>(
        S.transpose() * A.template selfadjointView<Uplo>() * S,
        S.transpose() * B.template selfadjointView<Uplo>() * S, num, basis,
        lambda, rule, prm);
    if (basis != nullptr) {
      *basis = S * (*basis);
    }
  } else {
    csr_matr_t tildeK =
        (S.transpose() * A.template selfadjointView<Uplo>() * S).sparseView();
    csr_matr_t tildeM =
        (S.transpose() * B.template selfadjointView<Uplo>() * S).sparseView();
    ncv = symmetric_gevd<Eigen::Lower, csr_matr_t>(tildeK, tildeM, num, basis,
                                                   lambda, rule, prm);
    if (basis != nullptr) {
      *basis = S * (*basis);
    }
  }

  return ncv;
}

#define INSTANTIATION(Uplo, MatType)                                           \
  template int symmetric_evd<Uplo, MatType>(                                   \
      const MatType &A, int num, matxr_t *basis, vecxr_t *lambda,              \
      const Spectra::SortRule &rule, const spectra_params_t &prm);             \
  template int symmetric_gevd<Uplo, MatType>(                                  \
      const MatType &A, const MatType &B, int num, matxr_t *basis,             \
      vecxr_t *lambda, const Spectra::SortRule &rule,                          \
      const spectra_params_t &prm);                                            \
  template int symmetric_subspace_gevd<Uplo, MatType, true>(                   \
      const MatType &A, const MatType &B, const matxr_t &subspace_basis,       \
      int num, matxr_t *basis, vecxr_t *lambda, const Spectra::SortRule &rule, \
      const spectra_params_t &prm);                                            \
  template int symmetric_subspace_gevd<Uplo, MatType, false>(                  \
      const MatType &A, const MatType &B, const matxr_t &subspace_basis,       \
      int num, matxr_t *basis, vecxr_t *lambda, const Spectra::SortRule &rule, \
      const spectra_params_t &prm);

INSTANTIATION(Eigen::Lower, csr_matr_t)
INSTANTIATION(Eigen::Lower, csc_matr_t)
INSTANTIATION(Eigen::Lower, matxr_t)
INSTANTIATION(Eigen::Upper, csr_matr_t)
INSTANTIATION(Eigen::Upper, csc_matr_t)
INSTANTIATION(Eigen::Upper, matxr_t)

#undef INSTANTIATION
}  // namespace chaos::math
