/** -*- mode: c++ -*-
 * @file numerical.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:39:58 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <cmath>
#include <cstdio>
#include <limits>

namespace chaos::numerical {
constexpr double PI{3.1415926535897932384626433832795028841971693993};
constexpr double HALF_PI{PI / 2};
constexpr double TWO_PI{PI * 2};
constexpr double PI_OVER_180{PI / 180};
constexpr size_t GOLDEN_RATIO_32{0x9e3779b9ull};
constexpr size_t GOLDEN_RATIO_PRIME_32{0x9e3779b1ull};
constexpr size_t GOLDEN_RATIO_64{0x9e3779b97f4a7c55ull};
constexpr size_t GOLDEN_RATIO_PRIME_64{0x9e3779b97f4a7c15ull};

template <typename Scalar>
struct constant {
  static constexpr Scalar eps{0};
  static constexpr int precision{0};
  static constexpr Scalar inf{std::numeric_limits<Scalar>::max()};
};

template <>
struct constant<double> {
  //-> double has precision about 15~16
  //-> #exponential is 52.
  static constexpr double eps{1e-10};
  static constexpr double pi{PI};
  static constexpr double half_pi{HALF_PI};
  static constexpr double inf{std::numeric_limits<double>::max()};
  static constexpr int precision{15};
  //-> this contant number usually used in hash combine function.
  static constexpr size_t golden_ratio{GOLDEN_RATIO_64};
  static constexpr size_t golden_ratio_prime{GOLDEN_RATIO_PRIME_64};
};

template <>
struct constant<float> {
  //-> double has precision about 6~7
  //-> #exponential is 23
  static constexpr float eps{1e-4};
  static constexpr float pi{PI};
  static constexpr float half_pi{HALF_PI};
  static constexpr float inf{std::numeric_limits<float>::max()};
  static constexpr int precision{6};
  //-> this contant number usually used in hash combine function.
  static constexpr size_t golden_ratio{GOLDEN_RATIO_32};
  static constexpr size_t golden_ratio_prime{GOLDEN_RATIO_PRIME_32};
};

/**
 * @brief convert degrees to radians
 *
 * @param d the degrees
 * @return corresponding radians
 */
constexpr double degree2rad(const double d) { return d * PI_OVER_180; }

/**
 * @brief convert radians to degrees
 *
 * @param d the radians
 * @return corresponding degrees
 */
constexpr double rad2degree(const double r) { return r / PI_OVER_180; }

/**
 * @brief check whether some value near the reference.
 *
 * @tparam Scalar maybe int, float, double...
 * @param val the input value, marked as a.
 * @param ref the reference value, marked as r.
 * @param eps the eps w.r.t. the Scalar type
 * @return true \f$|a-r| \le \epsilon.\f$
 * @return false \f$ |a-r| > \epsilon. \f$
 */
template <typename Scalar>
constexpr bool near(const Scalar val, const Scalar ref,
                    const Scalar eps = constant<Scalar>::eps) {
  const auto &_ = std::abs(ref);
  if (_ <= 1) {
    return std::abs(val - ref) <= eps;
  } else {
    return std::abs(val - ref) <= eps * _;
  }
}

/**
 * @brief check whether the input value is zero.
 *
 * @tparam Scalar maybe int, float, double...
 * @param val the input value, marked as a.
 * @param eps the eps w.r.t. the Scalar type.
 * @return true \f$ a \approx \epsilon \f$
 * @return false a is not zero.
 */
template <typename Scalar>
constexpr bool is_zero(const Scalar val,
                       const Scalar eps = constant<Scalar>::eps) {
  return val <= eps && val >= -eps;
}

/**
 * @brief clamp the value to a valid region.
 *
 * @tparam Scalar maybe int, float, double...
 * @param val the input value.
 * @param lower valid lower bound.
 * @param upper valid upper bound.
 * @return a valid value.
 */
template <typename Scalar>
constexpr Scalar clamp(const Scalar val, const Scalar lower,
                       const Scalar upper) {
  return val > upper ? upper : val < lower ? lower : val;
}
}  // namespace chaos::numerical
