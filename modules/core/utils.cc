#include "utils.h"

#include "common/numerical.h"
namespace chaos::math {

inline static real_t clamp(const real_t theta,
                           const real_t left = -numerical::PI,
                           const real_t right = numerical::PI) {
  const double T = right - left;
  return theta - T * std::floor(theta / T + 0.5);
}

int exp(const Eigen::Ref<const vec3r_t> &w, mat33r_t &R) {
  /**
   * equivalent version.
     auto theta = w.norm();
     if (numerical::is_zero(theta)) {
       R = mat33r_t::Identity();
     } else {
       auto skew_w = skew33(w) / theta;
       R = mat33r_t::Identity() + std::sin(theta) * skew_w +
           (1 - std::cos(theta)) * skew_w * skew_w;
     }
     return 0;
   */
  qtnr_t q;
  int ret = exp(w, q);
  if (ret == 0) {
    R = q.matrix();
  }
  return ret;
}

mat33r_t exp(const Eigen::Ref<const vec3r_t> &w) {
  mat33r_t R;
  exp(w, R);
  return R;
}

// exp map: exp^{(0, w)} --> qtn
// w contains two info:
//  1. --> |w|/2 represents the rotation theta.
//  2. --> w/|w| represents the rotation axis.
// q[0] = cos(theta) = cos(|w|/2)
// q[1] = sin(theta) * w / |w| = sin(|w|/2) * w / |w|
int exp(const Eigen::Ref<const vec3r_t> &w, qtnr_t &q) {
  real_t theta = w.norm();
  auto q0 = std::cos(theta / 2);
  // since we need to calculate (sin(theta) / theta)
  if (numerical::is_zero(theta, 1e-2)) {
    auto hat = q0 * w / 2;
    q = qtnr_t(q0, hat[0], hat[1], hat[2]);
  } else {
    auto hat = std::sin(theta / 2) * w / theta;
    q = qtnr_t(q0, hat[0], hat[1], hat[2]);
  }
  return 0;
}

// int cayley(const vec3r_t &w, mat33r_t &R) {
//   qtnr_t q;
//   int ret = cayley(w, q);
//   if (ret == 0) {
//     R = q.matrix();
//   }
//   return ret;
// }

// cayley map: exp^{(0, w)} --> qtn
// w contains two info:
//  1. --> |w|/2 represents the rotation theta.
//  2. --> w/|w| represents the rotation axis.
// cayley map use a approximation: tan(\theta) \approx \theta
// and using tangent formula:
//  - sin(2*\theta) = \frac{2*tan(\theta)}{1 + tan^2(\theta)}
//  - cos(2*\theta) = \frac{1 - tan^2(\theta)}{1 + tan^2(\theta)}
// thus, the corresponding qtn expression is given:
//  q[0] = cos(theta) = cos(|w|/2)
//       = (1 - tan^2(|w|/4)) / (1 + tan^2(|w|/4))
//       \approx (1 - |w|^2 / 16) ( 1 + |w|^2 / 16)
//  q[1] = sin(theta) * w / |w|
//       = sin(|w|/2) * w / |w|
//       = (2 * tan(|w|/4)) /  (1 + tan^2(|w|/4)) * w / |w|
//       \approx (|w|) / (1 + |w|^2 / 16) * w / |w|
// ---------------------------------------------------------------
// notice: |w| should be very small, otherwise, the \approx will
//         will bring a lot of errors.
// int cayley(const vec3r_t &w, qtnr_t &q) {
//   real_t w_norm = w.norm();
//   auto theta = clamp(w_norm);
//   auto den = 16 + theta * theta;
//   if (numerical::is_zero(w_norm)) {
//     q = qtnr_t(0, 1, 0, 0);
//   } else {
//     auto hat = 8 * theta / den * w / w_norm;
//     q = qtnr_t(32 / den - 1, hat[0], hat[1], hat[2]);
//   }
//   return 0;
// }

int log(const Eigen::Ref<const mat33r_t> &R, vec3r_t &w) {
  //-> the same with:
  // Eigen::AngleAxis<real_t> angleAxis(R);
  // w = angleAxis.axis() * angleAxis.angle();
  qtnr_t Q(R);
  return log(Q, w);
}

/**
 * @brief from SO(3) to so(3)
 *
 * should be noticed that, this log function is different to qtn.
 * qtn version log: exp^(0, theta / 2 * w) = (cos(theta/2), sin(theta/2)*w)
 * using qtn to do rotation(axis is w, and the rotation angle is theta), we
 * will: exp^(0, theta / 2*w) * (0, v) * exp^(0, theta / 2*w).conjugate == (0,
 * u) and u is the result of v rotate with w by theta. this is why theta / 2.
 *
 *
 * @param q
 * @param w
 * @return int
 */
int log(const qtnr_t &q, vec3r_t &w) {
  auto theta = std::acos(q.w());
  w << q.x(), q.y(), q.z();
  if (numerical::is_zero(sin(theta))) {
    //-> when sin(theta) is near zero, q.w() may near 1/-1.
    w *= 2 / q.w();
  } else {
    w *= 2 * theta / sin(theta);
  }
  return 0;
}

vec3r_t log(const Eigen::Ref<const mat33r_t> &R) {
  vec3r_t w;
  log(R, w);
  return w;
}

vec3r_t log(const qtnr_t &q) {
  vec3r_t w;
  log(q, w);
  return w;
}
}  // namespace chaos::math
