#pragma once
#include <cstddef>
#include <type_traits>
#include <vector>

#include "common/type.h"
#include "utils/logger/logger.h"
namespace chaos {

namespace internal {

template <int BlockSize, typename Scalar = real_t>
struct block_element_traits {
 private:
 public:
  using scalar_type = Scalar;
  using element_type = std::conditional_t<
      BlockSize == 1, Scalar,
      std::conditional_t<(BlockSize > 0),
                         Eigen::Matrix<Scalar, BlockSize, BlockSize>,
                         Eigen::Matrix<Scalar, -1, -1>>>;
#if CPP_STANDARD >= CPP17
  using vector_type = std::vector<element_type>;
#else
  using vector_type = std::conditional_t<
      (BlockSize > 1),
      std::vector<element_type, Eigen::aligned_allocator<element_type>>,
      std::vector<element_type>>;
#endif
};

}  // namespace internal

template <MATRIX_FILL_MODE Mode, int BlockSize, typename Scalar = real_t>
struct tridiagonal_matrix_t {
  static constexpr MATRIX_FILL_MODE fill_mode = Mode;
  static constexpr int block_size = BlockSize;
  using scalar_type =
      typename internal::block_element_traits<block_size, Scalar>::scalar_type;
  using element_type =
      typename internal::block_element_traits<block_size, Scalar>::element_type;
  using vector_type =
      typename internal::block_element_traits<block_size, Scalar>::vector_type;

  tridiagonal_matrix_t(size_t nBlocks);

  template <MATRIX_FILL_MODE _ = Mode,
            std::enable_if_t<_ == MATRIX_FILL_MODE::FULL, bool> = true>
  tridiagonal_matrix_t(const vector_type &diag, const vector_type &lower,
                       const vector_type &upper);

  template <MATRIX_FILL_MODE _ = Mode,
            std::enable_if_t<_ != MATRIX_FILL_MODE::FULL, bool> = true>
  tridiagonal_matrix_t(const vector_type &diag, const vector_type &off_diag);

  size_t rows() const { return m_nScalars; }
  size_t cols() const { return m_nScalars; }

  size_t nScalars() const { return m_nScalars; }
  size_t nBlocks() const { return m_nBlocks; }

  vector_type &set_diag() { return diag; }
  const vector_type &get_diag() const { return diag; }

  element_type &set_blk(size_t blk_r, size_t blk_c);
  element_type &set_diag(size_t blk_id);
  element_type &set_lower(size_t blk_id);
  element_type &set_upper(size_t blk_id);

  vecxr_t operator*(const Eigen::Ref<const vecxr_t> &rhs) const;

  vector_type &set_lower();
  vector_type &set_upper();
  const vector_type &get_lower() const;
  const vector_type &get_upper() const;

  mat_t<scalar_type> to_dense_matrix() const;
  csr_mat_t<scalar_type> to_csr_matrix() const;

  template <typename Derived, int _ = BlockSize,
            std::enable_if_t<(_ > 0), bool> = true>
  auto part(Derived &vec, size_t p) const {
    return vec.template segment<BlockSize>(p * BlockSize);
  }

 protected:
  template <bool full>
  void fill(size_t r, size_t c, const element_type &elem,
            coo_list_t<scalar_type> &coo) const;
  void fill(size_t r, size_t c, const element_type &elem,
            mat_t<scalar_type> &mat) const;

  vector_type diag, upper, lower;
  size_t m_nBlocks, m_nScalars;
};

template <MATRIX_FILL_MODE mode, typename Scalar>
using scalar_tridiagonal_matrix_t = tridiagonal_matrix_t<mode, 1, Scalar>;
}  // namespace chaos

#include "tridiagonal_matrix.imp"
