/** -*- mode: c++ -*-
 * @file type.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:41:06 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Sparse>
#include <functional>
#include <vector>

namespace chaos {

#ifndef USE_SINGLE_PRECISION
using real_t = double;
#else
using real_t = float;
#endif

template <typename Scalar = real_t>
using coo_t = Eigen::Triplet<Scalar>;
template <typename Scalar = real_t>
using tpl_t = coo_t<Scalar>;

template <typename Scalar = real_t>
using coo_list_t = std::vector<coo_t<Scalar>>;
template <typename Scalar = real_t>
using tpl_list_t = coo_list_t<Scalar>;

template <typename Scalar = real_t, int Options = Eigen::RowMajor>
using sp_mat_t = Eigen::SparseMatrix<Scalar, Options>;

template <typename Scalar = real_t>
using csr_mat_t = sp_mat_t<real_t, Eigen::RowMajor>;

template <typename Scalar = real_t>
using csc_mat_t = sp_mat_t<real_t, Eigen::ColMajor>;

template <typename Scalar = real_t>
using sp_vec_t = Eigen::SparseVector<Scalar>;

template <typename Scalar = real_t, int Rows = Eigen::Dynamic,
          int Cols = Eigen::Dynamic, int Options = Eigen::ColMajor>
using mat_t = Eigen::Matrix<Scalar, Rows, Cols, Options>;

template <typename Scalar = real_t, int Rows = Eigen::Dynamic>
using vec_t = Eigen::Matrix<Scalar, Rows, 1>;

template <typename Scalar = real_t>
using qtn_t = Eigen::Quaternion<Scalar>;

// some common matrix type
#define BATCH_COMMON_SIZE_DEFS_(type, suffix, row, col)             \
  template <typename Scalar>                                        \
  using mat##row##col##_t = mat_t<Scalar, row, col>;                \
  template <typename Scalar>                                        \
  using vec##row##_t = vec_t<Scalar, row>;                          \
  using mat##row##col##suffix##_t = mat_t<type, row, col>;          \
  using vec##row##suffix##_t = vec_t<type, row>;                    \
  using mat##row##x##suffix##_t = mat_t<type, row, Eigen::Dynamic>; \
  using mat##x##col##suffix##_t = mat_t<type, Eigen::Dynamic, col>;

#define BATCH_TYPES_(type, suffix)                                      \
  BATCH_COMMON_SIZE_DEFS_(type, suffix, 2, 2)                           \
  BATCH_COMMON_SIZE_DEFS_(type, suffix, 3, 3)                           \
  BATCH_COMMON_SIZE_DEFS_(type, suffix, 4, 4)                           \
  using matx##suffix##_t = mat_t<type, Eigen::Dynamic, Eigen::Dynamic>; \
  using vecx##suffix##_t = vec_t<type, Eigen::Dynamic>;                 \
  using qtn##suffix##_t = qtn_t<type>;                                  \
  using csr_mat##suffix##_t = sp_mat_t<type, Eigen::RowMajor>;          \
  using csc_mat##suffix##_t = sp_mat_t<type, Eigen::ColMajor>;          \
  using sp_vec##suffix##_t = sp_vec_t<type>;

BATCH_TYPES_(real_t, r);
BATCH_TYPES_(int, i);

#undef BATCH_TYPES_
#undef BATCH_COMMON_TYPE_DEFS_

enum class MATRIX_FILL_MODE {
  LOWER = Eigen::Lower,
  UPPER = Eigen::Upper,
  FULL = Eigen::Lower | Eigen::Upper
};
}  // namespace chaos
