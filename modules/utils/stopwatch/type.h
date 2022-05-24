/** -*- mode: c++ -*-
 * @file type.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:42:02 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <cstddef>

namespace chaos::utils {
using rep_t = double;
using stopwatch_id_t = size_t;

struct time_unit_t {
  enum time_unit_enum {
    NANOSECONDS = 0,
    MICROSECONDS,
    MILLISECONDS,
    SECONDS,
    MINUTES,
    HOURS,
    ADAPTIVE,
  };
  static constexpr const char *units_str[]{"ns",  "us", "ms", "s",
                                           "min", "h",  "?"};
};
}  // namespace chaos::utils
