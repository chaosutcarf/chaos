#pragma once

#include <cstddef>
#include <exception>
#include <type_traits>

#include "tridiagonal_matrix.h"

namespace chaos {

namespace internal {

template <typename T, typename = void>
struct default_inverse_op;

template <typename T>
struct default_inverse_op<T, std::enable_if_t<std::is_floating_point_v<T>>> {
  constexpr static int value = 1;
  static T inverse(const T& M) {
    CHAOS_ASSERT(abs(M) > 1e-7, M);
    return 1.0 / M;
  }
};

template <typename T>
struct default_inverse_op<
    T, std::enable_if_t<std::is_base_of_v<Eigen::MatrixBase<T>, T>>> {
  constexpr static int value = 2;
  static T inverse(const T& M) {
    CHAOS_ASSERT(abs(M.determinant()) > 1e-7, M, M.determinant());
    return M.inverse();
  }
};

}  // namespace internal

template <typename T>
struct tridiagonal_linear_solver_t {
  using scalar_type = typename T::scalar_type;
  using element_type = typename T::element_type;
  using vector_type = typename T::vector_type;

  tridiagonal_linear_solver_t() = default;
  tridiagonal_linear_solver_t(T& data) { compute(data); }

  template <typename InverseOp = internal::default_inverse_op<element_type>>
  void compute(T& data);
  Eigen::ComputationInfo info() const { return m_info; }
  //-> thomas_algorithm
  void solve(const Eigen::Ref<const vecxr_t>& b, Eigen::Ref<vecxr_t> x) const;
  vecxr_t solve(const Eigen::Ref<const vecxr_t>& b) const {
    vecxr_t x(b.size());
    solve(b, x);
    return x;
  }

 private:
  const T* data;
  size_t N;
  vector_type Up, invD;
  Eigen::ComputationInfo m_info;
  bool m_factorizeIsOk{false};
};

////////////////////////////////////////////////////////////////////////
//                       template implementation                      //
////////////////////////////////////////////////////////////////////////

template <typename T>
template <typename InverseOp>
void tridiagonal_linear_solver_t<T>::compute(T& data) {
  try {
    m_factorizeIsOk = false;
    this->data = &data;
    N = data.nBlocks();
    Up.resize(N - 1);
    invD.resize(N);
    const auto& D = data.get_diag();
    const auto& L = data.get_lower();
    const auto& U = data.get_upper();

    //-> generalize to: U'_0 = D_0.inv() * U_0
    invD[0] = InverseOp::inverse(D[0]);
    Up[0] = invD[0] * U[0];

    for (size_t i = 1; i < N - 1; ++i) {
      //-> m = (D_i - L_{i-1} * U'_{i-1}).inv()
      invD[i] = InverseOp::inverse(D[i] - L[i - 1] * Up[i - 1]);
      Up[i] = invD[i] * U[i];
    }
    invD[N - 1] = InverseOp::inverse(D[N - 1] - L[N - 2] * Up[N - 2]);
    m_factorizeIsOk = true;
    m_info = Eigen::Success;
  } catch (std::exception& e) {
    error_msg("{}", e.what());
    m_info = Eigen::NumericalIssue;
  }
}

template <typename T>
void tridiagonal_linear_solver_t<T>::solve(const Eigen::Ref<const vecxr_t>& b,
                                           Eigen::Ref<vecxr_t> x) const {
  //-> http://www.industrial-maths.com/ms6021_thomas.pdf
  //-> Condition: ||Di|| > ||Li|| + ||Ui||
  CHAOS_ASSERT(data != nullptr);
  CHAOS_ASSERT(data->rows() == (size_t)b.size());
  CHAOS_ASSERT(b.size() == x.size());
  CHAOS_ASSERT(m_factorizeIsOk);

  //-> pick data.
  size_t N = data->nBlocks();
  const auto& L = data->get_lower();

  //-> use the same storage.
  auto& bp = x;
  data->part(bp, 0) = invD[0] * data->part(b, 0);
  for (size_t i = 1; i < N; ++i) {
    data->part(bp, i) =
        invD[i] * (data->part(b, i) - L[i - 1] * data->part(bp, i - 1));
  }
  //-> reverse sweep.
  for (size_t i = N - 1; i-- > 0;) {
    data->part(x, i) -= Up[i] * data->part(x, i + 1);
  }
}

}  // namespace chaos
