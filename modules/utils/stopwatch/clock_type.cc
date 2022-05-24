/** -*- mode: c++ -*-
 * @file clock_type.cc
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:42:13 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#include "clock_type.h"

#include <memory>

namespace chaos::utils {
struct wall_clock_t : public clock_type {
  using clock_impl = std::chrono::steady_clock;
  using time_point_t = clock_impl::time_point;

  void start() override;
  rep_t elapsed(const time_unit_t::time_unit_enum &unit) override;
  std::string type() const override { return "wall_clock"; };

 private:
  time_point_t tp_last{clock_impl::now()};
};

struct cpu_clock_t : public clock_type {
  using time_point_t = std::clock_t;

  void start() override;
  rep_t elapsed(const time_unit_t::time_unit_enum &unit) override;
  std::string type() const override { return "cpu_clock"; };

 private:
  time_point_t tp_last{std::clock()};
};

void wall_clock_t::start() { tp_last = clock_impl::now(); }

rep_t wall_clock_t::elapsed(const time_unit_t::time_unit_enum &unit) {
  auto duration = clock_impl::now() - tp_last;
  switch (unit) {
    case time_unit_t::ADAPTIVE:
    case time_unit_t::NANOSECONDS:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::nano>>(duration)
          .count();
    case time_unit_t::MICROSECONDS:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::micro>>(duration)
          .count();
    case time_unit_t::MILLISECONDS:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::milli>>(duration)
          .count();
    case time_unit_t::SECONDS:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::ratio<1>>>(duration)
          .count();
    case time_unit_t::MINUTES:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::ratio<60>>>(duration)
          .count();
    case time_unit_t::HOURS:
      return std::chrono::duration_cast<
                 std::chrono::duration<rep_t, std::ratio<3600>>>(duration)
          .count();
    default:
      return 0;
  };
}

void cpu_clock_t::start() { tp_last = std::clock(); }

rep_t cpu_clock_t::elapsed(const time_unit_t::time_unit_enum &unit) {
  constexpr double _[]{1e9, 1e6, 1e3, 1, 1.0 / 60, 1.0 / 3600, 1e9};
  auto duration = std::clock() - tp_last;
  if (unit < 0 || unit > 6) {
    return 0;
  } else {
    return _[static_cast<int>(unit)] * duration / CLOCKS_PER_SEC;
  }
}

std::unique_ptr<clock_type> clock_type::create(clock_impl_enum c) {
  switch (c) {
    case WALL_CLOCK:
      return std::make_unique<wall_clock_t>();
    case CPU_CLOCK:
      return std::make_unique<cpu_clock_t>();
    default:
      return nullptr;
  }
}

}  // namespace chaos::utils
