#pragma once

#include "common/type.h"

namespace chaos::math {
/**
 * @brief skew33, is also called cross operator of w.
 *
 * @param w is a 3 dim vector
 * @return mat33r_t the result skew matrix.
 *
 * skew33 = \begin{matrix}
 *  0   & -w_3 &  w_2 \\
 *  w_3 &  0   & -w_1 \\
 * -w_2 &  w_1 &  0   \\
 * \end{matrix}
 */
template <typename Scalar>
mat_t<Scalar, 3, 3> skew33(const Eigen::Ref<const vec_t<Scalar, 3>> &w) {
  mat_t<Scalar, 3, 3> wx;
  // clang-format off
  wx << 0, -w[2], w[1],
      w[2], 0, -w[0],
      -w[1], w[0], 0;
  // clang-format on
  return wx;
}

int exp(const Eigen::Ref<const vec3r_t> &w, mat33r_t &R);
int exp(const Eigen::Ref<const vec3r_t> &w, qtnr_t &q);
mat33r_t exp(const Eigen::Ref<const vec3r_t> &w);

// int cayley(const vec3r_t &w, mat33r_t &R);
// int cayley(const vec3r_t &w, qtnr_t &q);

int log(const Eigen::Ref<const mat33r_t> &R, vec3r_t &w);
int log(const qtnr_t &q, vec3r_t &W);
vec3r_t log(const Eigen::Ref<const mat33r_t> &R);
vec3r_t log(const qtnr_t &q);
}  // namespace chaos::math
