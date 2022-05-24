/** -*- mode: c++ -*-
 * @file stw_metric.cc
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:43:44 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#include <utils/stopwatch/stw_metric.h>

namespace chaos::utils {
namespace stw_metric {
class stw_min : public stw_metric_t {
 public:
  [[nodiscard]] rep_t elapsed() const override { return min; }
  void eval(rep_t cost) override { min = cost < min ? cost : min; }
  void reset() override { min = std::numeric_limits<rep_t>::max(); }
  [[nodiscard]] std::string type() const override { return "min"; }

 private:
  rep_t min{std::numeric_limits<rep_t>::max()};
};

class stw_max : public stw_metric_t {
 public:
  [[nodiscard]] rep_t elapsed() const override { return max; }
  void eval(rep_t cost) override { max = cost > max ? cost : max; }
  void reset() override { max = 0; }
  [[nodiscard]] std::string type() const override { return "max"; }

 private:
  rep_t max{0};
};

class stw_avg : public stw_metric_t {
 public:
  [[nodiscard]] rep_t elapsed() const override { return avg; }
  void eval(rep_t cost) override {
    cnt++;
    double w = 1.0 / cnt;
    avg = (1 - w) * avg + w * cost;
  }
  void reset() override { avg = 0, cnt = 0; }
  [[nodiscard]] std::string type() const override { return "avg"; }
  [[nodiscard]] std::string name() const override {
    return "avg(" + std::to_string(cnt) + ")";
  }

 private:
  rep_t avg{0};
  std::size_t cnt{0};
};

class stw_sum : public stw_metric_t {
 public:
  [[nodiscard]] rep_t elapsed() const override { return sum; }
  void eval(rep_t cost) override { sum += cost; }
  void reset() override { sum = 0; }
  [[nodiscard]] std::string type() const override { return "sum"; }

 private:
  rep_t sum{0};
};

class stw_last_cost : public stw_metric_t {
 public:
  [[nodiscard]] rep_t elapsed() const override { return cost; }
  void eval(rep_t cost) override { this->cost = cost; }
  void reset() override { cost = 0; }
  [[nodiscard]] std::string type() const override { return "last"; }

 private:
  rep_t cost{0};
};
}  // namespace stw_metric

std::unique_ptr<stw_metric_t> stw_metric_t::create(stw_metric_impl_enum e) {
  switch (e) {
    case AVG:
      return std::make_unique<stw_metric::stw_avg>();
    case MIN:
      return std::make_unique<stw_metric::stw_min>();
    case MAX:
      return std::make_unique<stw_metric::stw_max>();
    case SUM:
      return std::make_unique<stw_metric::stw_sum>();
    case LAST:
      return std::make_unique<stw_metric::stw_last_cost>();
    default:
      return nullptr;
  }
}
}  // namespace chaos::utils
