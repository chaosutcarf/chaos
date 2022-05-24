/** -*- mode: c++ -*-
 * @file stw_metric.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Wednesday, November 04, 2020 AM10:32:37 CST
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <utils/stopwatch/type.h>

#include <limits>
#include <memory>
#include <string>

namespace chaos::utils {
class stw_metric_t {
 public:
  enum stw_metric_impl_enum {
    AVG = 0,
    MIN,
    MAX,
    SUM,
    LAST,
  };
  static constexpr const char *type_list[]{"avg", "min", "max", "sum", "last"};

  virtual ~stw_metric_t() = default;
  [[nodiscard]] virtual rep_t elapsed() const = 0;
  virtual void eval(rep_t cost) = 0;
  virtual void reset() = 0;
  [[nodiscard]] virtual std::string name() const { return type(); }
  [[nodiscard]] virtual std::string type() const = 0;
  static std::unique_ptr<stw_metric_t> create(stw_metric_impl_enum e);
};

}  // namespace chaos::utils
