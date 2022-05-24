#include "tridiagonal_solver.h"

namespace chaos {
#define INSTANTIATE_TRIDIAG(mode)                       \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 1>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 2>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 3>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 4>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 5>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 6>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 7>>; \
  template struct tridiagonal_linear_solver_t<          \
      tridiagonal_matrix_t<MATRIX_FILL_MODE::mode, 8>>;

INSTANTIATE_TRIDIAG(FULL);
INSTANTIATE_TRIDIAG(UPPER);
INSTANTIATE_TRIDIAG(LOWER);
}  // namespace chaos
