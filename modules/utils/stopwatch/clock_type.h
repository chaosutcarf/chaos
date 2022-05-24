/** -*- mode: c++ -*-
 * @file clock_type.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:41:44 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <utils/stopwatch/type.h>

#include <chrono>
#include <ctime>
#include <memory>
#include <string>

namespace chaos::utils {
struct clock_type {
  enum clock_impl_enum {
    WALL_CLOCK = 0,
    CPU_CLOCK,
  };
  static constexpr const char *type_list[]{"wall_clock", "cpu_clock"};

  virtual ~clock_type() {}
  virtual void start() = 0;
  virtual rep_t elapsed(const time_unit_t::time_unit_enum &unit) = 0;
  virtual std::string type() const = 0;
  static std::unique_ptr<clock_type> create(clock_impl_enum c);
};
}  // namespace chaos::utils
