#include "pardiso_solver.h"

#include <stdexcept>

#include "common/type.h"
#include "utils/logger/logger.h"
#include "utils/stopwatch/stopwatch.h"
using namespace Eigen;
namespace chaos::solver {

static int get_omp_num_threads() {
  char *var = getenv("OMP_NUM_THREADS");
  return var == nullptr ? 1 : std::stoi(var);
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::pardiso_sp_matr_t::set(const vecxi_t &ia,
                                                    const vecxi_t &ja,
                                                    const vecxr_t &val,
                                                    bool zero_base) {
  auto nnz = ja.size();
  auto n = ia.size() - 1;
  CHAOS_ASSERT(nnz == val.size());
  CHAOS_ASSERT(n != 0);
  this->val = val;
  if (zero_base) {
    this->ia = ia + vecxi_t::Ones(n + 1);
    this->ja = ja + vecxi_t::Ones(nnz);
  } else {
    this->ja = ja;
    this->ia = ia;
  }
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::pardiso_sp_matr_t::update_with_same_pattern(
    const vecxr_t &val) {
  CHAOS_ASSERT(this->val.size() == val.size());
  this->val = val;
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::pardiso_sp_matr_t::update_with_same_pattern(
    const csr_matr_t &A, bool is_symmetric) {
  csr_matr_t pardiso_mat;
  if (is_symmetric) {
    //-> pardiso only store the upper triangle part of a symmetric matrix.
    pardiso_mat.template selfadjointView<Upper>() =
        A.template selfadjointView < int(Mode) & Upper ? Upper : Lower > ();
  } else {
    pardiso_mat = A;
  }
  pardiso_mat.makeCompressed();
  auto nnz = pardiso_mat.nonZeros();
  CHAOS_ASSERT(nnz == val.size());
  std::copy(pardiso_mat.valuePtr(), pardiso_mat.valuePtr() + nnz, val.data());
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::pardiso_sp_matr_t::set(const csr_matr_t &A,
                                                    bool is_symmetric) {
  csr_matr_t pardiso_mat;
  if (is_symmetric) {
    //-> pardiso only store the upper triangle part of a symmetric matrix.
    pardiso_mat.template selfadjointView<Upper>() =
        A.template selfadjointView < int(Mode) & Upper ? Upper : Lower > ();
  } else {
    pardiso_mat = A;
  }
  pardiso_mat.makeCompressed();
  auto n = pardiso_mat.rows();
  auto nnz = pardiso_mat.nonZeros();
  ia.resize(n + 1);
  ja.resize(nnz);
  val.resize(nnz);
  std::copy(pardiso_mat.outerIndexPtr(), pardiso_mat.outerIndexPtr() + n + 1,
            ia.data());
  std::copy(pardiso_mat.innerIndexPtr(), pardiso_mat.innerIndexPtr() + nnz,
            ja.data());
  std::copy(pardiso_mat.valuePtr(), pardiso_mat.valuePtr() + nnz, val.data());
  ia += vecxi_t::Ones(n + 1);
  ja += vecxi_t::Ones(nnz);
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::init(PARDISO_MATRIX_TYPE type) {
  mtype = (int)type;
  is_symmetric = !(type == PARDISO_MATRIX_TYPE::REAL_NONSYMMETRIC ||
                   type == PARDISO_MATRIX_TYPE::COMPLEX_NONSYMMETRIC);
  error = 0;
  solver = 0;    /* use sparse direct solver */
  iparm[0] = 0;  // fill iparm with default value, except iparm[2].

  //-> init pardiso solver.
  pardisoinit(pt, &mtype, &solver, iparm, dparm, &error);
  /* Numbers of processors, value of OMP_NUM_THREADS */
  iparm[2] = get_omp_num_threads();
  if (!check_error()) {
    info_msg("[PARDISO]: License check was successful!");
  } else {
    throw std::runtime_error("[PARDISO]: License Error");
  }
  // //-> pivot perturbation
  // iparm[9] = 13;
  // //-> scalings
  // iparm[10] = 1;
  // //-> matchings
  // iparm[12] = 1;
  // //-> pivoting
  // iparm[20] = 3;
  // //-> reordering
  // iparm[27] = 1;

  maxfct = 1; /* Maximum number of numerical factorizations.  */
  mnum = 1;   /* Which factorization to use. */
  msglvl = 0; /* Print statistical information  */
  error = 0;  /* Initialize error flag */
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::release() {
  if (is_initialized) {
    /* -------------------------------------------------------------------- */
    /* ..  Termination and release of memory.                               */
    /* -------------------------------------------------------------------- */
    /* Release internal memory. */
    run(RELEASE_ALL);
    // pardiso(pt, &maxfct, &mnum, &mtype, &phase, &mat_size, &ddum, &idum,
    // &idum,
    //         &idum, &idum, iparm, &msglvl, &ddum, &ddum, &error, dparm);
    is_initialized = false;
  }
}

template <MATRIX_FILL_MODE Mode>
bool pardiso_solver_t<Mode>::check_error() const {
  switch (error) {
    case 0:
      break;
    case -1:
      error_msg("[PARDISO]: Input inconsistent.");
      break;
    case -2:
      error_msg("[PARDISO]: Not enough memory.");
      break;
    case -3:
      error_msg("[PARDISO]: Reordering problem.");
      break;
    case -4:
      error_msg(
          "[PARDISO]: Zero pivot, numerical fact. or iterative refinement "
          "problem.");
      break;
    case -5:
      error_msg("[PARDISO]: Unclassified (internal) error.");
      break;
    case -6:
      error_msg("[PARDISO]: Preordering failed (matrix types 11, 13 only).");
      break;
    case -7:
      error_msg("[PARDISO]: Diagonal matrix problem.");
      break;
    case -8:
      error_msg("[PARDISO]: 32-bit integer overflow problem.");
      break;
    case -10:
      error_msg("[PARDISO]: No license file pardiso.lic found.");
      break;
    case -11:
      error_msg("[PARDISO]: License is expired.");
      break;
    case -12:
      error_msg("[PARDISO]: Wrong username or hostname.");
      break;
    case -100:
      error_msg(
          "[PARDISO]: Reached maximum number of Krylov-subspace iteration in "
          "iterative solver.");
      break;
    case -101:
      error_msg(
          "[PARDISO]: No sufficient convergence in Krylov-subspace iteration "
          "within 25 iterations.");
      break;
    case -102:
      error_msg("[PARDISO]: Error in Krylov-subspace iteration.");
      break;
    case -103:
      error_msg("[PARDISO]: Break-Down in Krylov-subspace iteration.");
      break;
    default:
      error_msg("[PARDISO]: Unknown pardiso error.");
  }
  return error != 0;
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::analyzePattern(const csr_matr_t &A) {
  //-> TODO: support rectangle matrix.
  CHAOS_ASSERT(A.rows() == A.cols(), A.rows(), A.cols());
  release();

  mat_size = A.rows();

  load_mat(A);
  run(ANALYSIS);

  is_analyzed = true;
  is_factorized = false;
  is_initialized = true;
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::factorize(const csr_matr_t &A) {
  CHAOS_ASSERT_EXT(is_analyzed, "Call before analyzePattern()");
  CHAOS_ASSERT(A.rows() == A.cols() && A.rows() == mat_size);

  csr_mat.update_with_same_pattern(A, is_symmetric);
  run(FACTORIZATION);
  is_factorized = true;
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::compute(const csr_matr_t &A) {
  //-> TODO: support rectangle matrix.
  CHAOS_ASSERT(A.rows() == A.cols(), A.rows(), A.cols());
  //-> Release internal memory.
  release();

  mat_size = A.rows();
  load_mat(A);
  run(ANALYSIS_FACTORIZATION);
  is_initialized = true;
  is_factorized = true;
  is_analyzed = true;
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::solve(const Eigen::Ref<const matxr_t> &b,
                                   const Eigen::Ref<matxr_t> &x) const {
  CHAOS_ASSERT(is_factorized);
  CHAOS_ASSERT(b.rows() == mat_size);
  CHAOS_DEBUG_ASSERT(x.rows() == b.rows());
  CHAOS_DEBUG_ASSERT(x.cols() == b.cols());

  int nrhs = b.cols();
  pardiso_chkvec(&mat_size, &nrhs, b.data(), &error);
  run(SOLVE, b.data(), x.const_cast_derived().data(), nrhs);
  debug_msg("[PARDISO] Number of performed iterative refinement steps {}",
            iparm[6]);
  debug_msg("[PARDISO] Number of perturbed pivots {}", iparm[13]);
}

template <MATRIX_FILL_MODE Mode>
Eigen::ComputationInfo pardiso_solver_t<Mode>::info() const {
  if (!is_initialized) {
    warn_msg("[PARDISO]: Solver is not initialized.");
    return Eigen::Success;
  } else {
    if (error == 0) {
      return Eigen::Success;
    } else if (error == -5 || error <= -10 && error >= -100) {
      return Eigen::InvalidInput;
    } else if (error > -10) {
      return Eigen::NumericalIssue;
    } else {
      return Eigen::NoConvergence;
    }
  }
}

template <MATRIX_FILL_MODE Mode>
void pardiso_solver_t<Mode>::load_mat(const csr_matr_t &A) {
  csr_mat.set(A, is_symmetric);
  //-> debug
  pardiso_chkmatrix(&mtype, &mat_size, csr_mat.val.data(), csr_mat.ia.data(),
                    csr_mat.ja.data(), &error);
  if (check_error()) {
    critical_msg("[PARDISO]: ERROR in consistency of matrix, error code: {}",
                 error);
    return;
  }
}

template class pardiso_solver_t<MATRIX_FILL_MODE::FULL>;
template class pardiso_solver_t<MATRIX_FILL_MODE::LOWER>;
template class pardiso_solver_t<MATRIX_FILL_MODE::UPPER>;
}  // namespace chaos::solver
