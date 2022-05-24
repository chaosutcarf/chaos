#pragma once

#include "common/type.h"
#include "linearsolver/linearsolver.h"

/**
 * ref: https://pardiso-project.org/manual/refsheet.pdf
 * details: https://pardiso-project.org/manual/manual.pdf
 * example: https://www.pardiso-project.org/manual/pardiso_sym.cpp
 *          https://www.pardiso-project.org/manual/pardiso_unsym.cpp
 */

namespace chaos::solver {
extern "C" {
/* PARDISO prototype. */
/* Check license of the solver and initialize the solver */
void pardisoinit(void *pt, int *mtype, int *solver, int *iparm, double *dparm,
                 int *error);
/* Solve matrix sytem */
void pardiso(void *pt, const int *maxfct, const int *mnum, const int *mtype,
             const int *phase, const int *n, const double *a, const int *ia,
             const int *ja, const int *perm, const int *nrhs, int *iparm,
             const int *msglvl, const double *b, double *x, int *error,
             double *dparm);
void pardiso_residual(const int *mtype, const int *n, const double *a,
                      const int *ia, const int *ja, double *b, double *x,
                      double *y, double *norm_b, double *norm_res);

void pardiso_chkmatrix(const int *mtype, const int *n, const double *a,
                       const int *ia, const int *ja, int *error);
void pardiso_chkvec(const int *n, const int *nrhs, const double *b, int *error);
void pardiso_printstats(int *mtype, int *n, double *a, int *ia, int *ja,
                        int *nrhs, double *b, int *error);
}

enum class PARDISO_MATRIX_TYPE {
  COMPLEX_HERMITIAN_INDEFINITE = -4,
  REAL_SYMMETRIC_INDEFINITE = -2,
  REAL_SYMMETRIC_STRUCTURE = 1,
  REAL_SYMMETRIC_POSITIVE_DEFINITE = 2,
  COMPLEX_SYMMETRIC_STRUCTURE = 3,
  COMPLEX_HERMITIAN_POSITIVE_DEFINITE = 4,
  COMPLEX_SYMMETRIC = 6,
  REAL_NONSYMMETRIC = 11,
  COMPLEX_NONSYMMETRIC = 13
};

template <MATRIX_FILL_MODE Mode = MATRIX_FILL_MODE::UPPER>
class pardiso_solver_t : public linear_solver_t<Mode> {
 public:
  struct pardiso_sp_matr_t {
    /*
      IA(N+1) — INTEGER Input
      On entry: IA is an integer array of size N+1. IA(i) points to the first
      column index of row i in the array JA in compressed sparse row format.
      Refer to Figure 2 for more details. Note: The array is accessed in all
      phases of the solution process. Note that the row and column numbers start
      from 1. JA(∗) — INTEGER Input On entry: The integer array JA contains the
      column indices of the sparse matrix A stored in compress sparse row
      format. The indices in each row must be sorted in increasing order. Note:
      The array is accessed in all phases of the solution process. For symmetric
      and structurally symmetric matrices it is assumed that zero diagonal
      elements are also stored in the list of nonzeros in A and JA. For
      symmetric matrices the solver needs only the upper triangular part of the
      system as shown in Figure 2.
    */
    vecxi_t ia;   // outer index array.
    vecxi_t ja;   // inner index array.
    vecxr_t val;  // value array.

    pardiso_sp_matr_t() = default;
    pardiso_sp_matr_t(const csr_matr_t &A, bool is_symmetric = true) {
      set(A, is_symmetric);
    };
    void set(const csr_matr_t &A, bool is_symmetric = true);
    void update_with_same_pattern(const csr_matr_t &A,
                                  bool is_symmetric = true);
    void set(const vecxi_t &ia, const vecxi_t &ja, const vecxr_t &val,
             bool zero_base = true);
    void update_with_same_pattern(const vecxr_t &val);
  };
  /* Matrix type
   *   1: real and structurally symmetric, supernode pivoting
   *   2: real and symmetric positive definite
   *  -2: real and symmetric indefinite, diagonal or Bunch-Kaufman pivoting
   *  11: real and nonsymmetric, complete supernode pivoting
   *   3: complex and structurally symmetric, supernode pivoting
   *   4: complex and hermitian positive definite
   *  -4: complex and hermitian indefinite, diagonal or Bunch-Kaufman pivoting
   *   6: complex and symmetric
   *  13: complex and nonsymmetric, supernode pivoting
   */

  pardiso_solver_t(
      PARDISO_MATRIX_TYPE type = PARDISO_MATRIX_TYPE::REAL_SYMMETRIC_INDEFINITE)
      : is_initialized(false) {
    init(type);
  }
  ~pardiso_solver_t() { release(); }
  void init(PARDISO_MATRIX_TYPE type =
                PARDISO_MATRIX_TYPE::REAL_SYMMETRIC_INDEFINITE);
  void release();

  void analyzePattern(const csr_matr_t &A) override;
  void factorize(const csr_matr_t &A) override;
  void compute(const csr_matr_t &A) override;
  void solve(const Eigen::Ref<const matxr_t> &b,
             const Eigen::Ref<matxr_t> &x) const override;
  Eigen::ComputationInfo info() const override;
  bool check_error() const;

 private:
  void load_mat(const csr_matr_t &A);
  void run(int phase) { run(phase, &ddum, &ddum); }
  void run(int phase, const double *b, double *x, int nrhs = 1) const {
    pardiso(pt, &maxfct, &mnum, &mtype, &phase, &mat_size, csr_mat.val.data(),
            csr_mat.ia.data(), csr_mat.ja.data(), &idum, &nrhs, iparm, &msglvl,
            b, x, &error, dparm);
    check_error();
  }

  pardiso_sp_matr_t csr_mat;
  int mat_size;
  /* Internal solver memory pointer pt,                  */
  /* 32-bit: int pt[64]; 64-bit: long int pt[64]         */
  /* or void *pt[64] should be OK on both architectures  */
  mutable void *pt[64];
  /* Pardiso control parameters.
     IPARM (64) — INTEGER Input/Output
     On entry: IPARM is an integer array of size 64 that is used to pass various
     parameters to PARDISO and to return some useful information after the
     execution of the solver. If IPARM(1) is 0, then PARDISOINIT fills IPARM(2)
     and IPARM(4) through IPARM(64) with default values. See section 2.3 for a
     detailed description. On output. Some IPARM values will contain useful
     information, e.g. numbers of nonzeros in the factors, etc. . Note: There is
     no default value for IPARM(3) and this value must always be supplied by the
     user, regardless of whether IPARM(1) is 0 or 1. On distributed-memory
     architectures, the user must also supply the value for IPARM(52), which
     reflects the number of compute nodes. Mixed OpenMP-MPI parallelization is
     used for the distributed-memory solver.
  */
  mutable int iparm[64];
  /* Control parameters for iterative solver.
     On entry: DPARM is a double-precision array of size 64 that is used to pass
     various parameters to PARDISO and to return some useful information after
     the execution of the iterative solver. The array will be used in the
     multi-recursive iterative linear solver in PARDISO. This iterative solver
     is used in case of IPARM(32) = 1. In addition, DPARM returns double return
     values from the direct solver such as the determinant for symmetric
     indefinite matrices or unsymmetric matrices. See section 2.4 for a detailed
     description.
  */
  mutable double dparm[64];
  /*
    MAXFCT — INTEGER Input
    On entry: Maximal number of factors with identical nonzero sparsity
    structure that the user would like to keep at the same time in memory. It is
    possible to store several different factorizations with the same nonzero
    structure at the same time in the internal data management of the solver. In
    many applications this value is equal to 1. Note: Matrices with different
    sparsity structure can be kept in memory with different memory address
    pointers PT.
  */
  int maxfct{1};
  /*
    MNUM — INTEGER Input
    On entry: Actual matrix for the solution phase. With this scalar the user
    can define the matrix that he would like to factorize. The value must be: 1
    ≤ MNUM ≤ MAXFCT. In many applications this value is equal to 1.
  */
  int mnum{1};
  /*
    PHASE — INTEGER Input
    On entry: PHASE controls the execution of the solver. It is a two-digit
    integer ij (10i + j, 1 ≤ i ≤ 3, i ≤ j ≤ 3 for normal execution modes). The i
    digit indicates the starting phase of execution, and j indicates the ending
    phase. PARDISO has the following phases of execution:
    1. Phase 1: Fill-reduction analysis and symbolic factorization
    2. Phase 2: Numerical factorization
    3. Phase 3: Forward and Backward solve including iterative refinement
    4. Termination and Memory Release Phase (PHASE ≤ 0)
    If a previous call to the routine has computed information from previous
    phases, execution may start at any phase:
    11 Analysis
    12 Analysis, numerical factorization
    13 Analysis, numerical factorization, solve, iterative refinement
    22 Numerical factorization
    -22 Selected Inversion
    23 Numerical factorization, solve, iterative refinement
    33 Solve, iterative refinement
    0 Release internal memory for L and U matrix number MNUM
    -1 Release all internal memory for all matrices
    Note: The analysis phase needs the numerical values of the matrix A in case
    of scalings (IPARM(11)=1) and symmetric weighted matching (IPARM(13)=1
    (normal matching) or IPARM(13)=2 (advanced matchings)).
  */
  enum PARDISO_PHASES {
    SELECTED_INVERSION = -22,
    RELEASE_ALL = -1,
    RELEASE_LU = 0,
    ANALYSIS = 11,
    ANALYSIS_FACTORIZATION = 12,
    ANALYSIS_FACTORIZATION_SOLVE = 13,
    FACTORIZATION = 22,
    FACTORIZATION_SOLVE = 23,
    SOLVE = 33,
  };
  /*
    ERROR — INTEGER Output
    On output: The error indicator
    Error Information
     0 No error.
    -1 Input inconsistent.
    -2 Not enough memory.
    -3 Reordering problem.
    -4 Zero pivot, numerical fact. or iterative refinement problem.
    -5 Unclassified (internal) error.
    -6 Preordering failed (matrix types 11, 13 only).
    -7 Diagonal matrix problem.
    -8 32-bit integer overflow problem.
    -10 No license file pardiso.lic found.
    -11 License is expired.
    -12 Wrong username or hostname.
    -100 Reached maximum number of Krylov-subspace iteration in iterative
    solver. -101 No sufficient convergence in Krylov-subspace iteration within
    25 iterations. -102 Error in Krylov-subspace iteration. -103 Break-Down in
    Krylov-subspace iteration.
  */
  mutable int error{0};
  /*
    MSGLVL — INTEGER Input
    On entry: Message level information. If MSGLVL = 0 then PARDISO generates
    no output. If MSGLVL = 1 the direct solver prints statistical information to
    the screen. The multi-recursive iterative solver prints statistical
    information in the file pardiso-ml.out.
  */
  int msglvl{0};
  /*
    SOLVER — INTEGER Input
    On entry: This scalar value defines the solver method that the user would
    like to use.
    0 sparse direct solver
    1 multi-recursive iterative solver
  */
  int solver{0};

  int mtype{int(PARDISO_MATRIX_TYPE::REAL_SYMMETRIC_INDEFINITE)};
  mutable double ddum; /* Double dummy */
  mutable int idum;    /* Integer dummy. */
  bool is_initialized{false};
  bool is_analyzed{false};
  bool is_factorized{false};
  bool is_symmetric{false};
};

}  // namespace chaos::solver
