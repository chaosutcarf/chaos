#ifndef _WIN32
#define private public
#endif
#include "utils/stopwatch/stopwatch.h"
#ifndef _WIN32
#undef private
#endif
#include <catch2/catch.hpp>
#include <numeric>
#include <random>
#include <thread>

using namespace chaos::utils;

void do_something(size_t maxits) {
  double _ = 0;
  for (size_t i = 0; i < maxits; ++i) {
    _ += i * 1.0 / maxits;
  }
}

bool near(double a, double b, double eps = 1) {
  if (a < eps) {
    return (a - b) < eps;
  } else {
    return (std::abs(a - b) / a) < eps;
  }
}

TEST_CASE("stopwatch time unit enum check", "[stopwatch]") {
  CHECK(static_cast<int>(time_unit_t::NANOSECONDS) == 0);
  CHECK(static_cast<int>(time_unit_t::MICROSECONDS) == 1);
  CHECK(static_cast<int>(time_unit_t::MILLISECONDS) == 2);
  CHECK(static_cast<int>(time_unit_t::SECONDS) == 3);
  CHECK(static_cast<int>(time_unit_t::MINUTES) == 4);
  CHECK(static_cast<int>(time_unit_t::HOURS) == 5);
  CHECK(static_cast<int>(time_unit_t::ADAPTIVE) == 6);
}

TEST_CASE("stopwatch time metric enum check", "[stopwatch]") {
  CHECK(static_cast<int>(stw_metric_t::AVG) == 0);
  CHECK(static_cast<int>(stw_metric_t::MIN) == 1);
  CHECK(static_cast<int>(stw_metric_t::MAX) == 2);
  CHECK(static_cast<int>(stw_metric_t::SUM) == 3);
  CHECK(static_cast<int>(stw_metric_t::LAST) == 4);
}

TEST_CASE("stopwatch clock type impl enum check", "[stopwatch]") {
  CHECK(static_cast<int>(clock_type::WALL_CLOCK) == 0);
  CHECK(static_cast<int>(clock_type::CPU_CLOCK) == 1);
}

TEST_CASE("stopwatch clock type usage check", "[stopwatch]") {
  auto c = {clock_type::create(clock_type::CPU_CLOCK),
            clock_type::create(clock_type::WALL_CLOCK)};
  double _[7];
  for (const auto& c1 : c) {
    for (size_t i = 0; i < 7; ++i) {
      c1->start();
      do_something(1e7);
      _[i] = c1->elapsed((time_unit_t::time_unit_enum)i);
    }
#define MY_NEAR_CHECK(a, b)                            \
  if (!near(a, b)) printf("failed: %lf, %lf\n", a, b); \
  CHECK(near(a, b));

    MY_NEAR_CHECK(_[0], _[6]);
    MY_NEAR_CHECK(_[0], _[1] * 1e3);
    MY_NEAR_CHECK(_[0], _[2] * 1e6);
    MY_NEAR_CHECK(_[0], _[3] * 1e9);
    MY_NEAR_CHECK(_[0], _[4] * 1e9 * 60);
    MY_NEAR_CHECK(_[0], _[5] * 1e9 * 3600);
    MY_NEAR_CHECK(c1->elapsed(static_cast<time_unit_t::time_unit_enum>(-1)),
                  0.0);
  }
}

TEST_CASE("stopwatch clock type difference", "[stopwatch]") {
  double _[2];
  constexpr long dur = 500;
  {
    auto c = clock_type::create(clock_type::CPU_CLOCK);
    do_something(1e7);
    std::this_thread::sleep_for(std::chrono::duration<long, std::milli>(dur));
    _[0] = c->elapsed(time_unit_t::MILLISECONDS);
  }
  {
    auto c = clock_type::create(clock_type::WALL_CLOCK);

    do_something(1e7);
    std::this_thread::sleep_for(std::chrono::duration<long, std::milli>(dur));
    _[1] = c->elapsed(time_unit_t::MILLISECONDS);
  }
#ifdef _WIN32
  MY_NEAR_CHECK(_[0], _[1]);
#else
  CHECK(_[0] < _[1]);
#endif
}

TEST_CASE("stopwatch unit type validator", "[stopwatch]") {
  CHECK(std::string("h") == time_unit_t::units_str[time_unit_t::HOURS]);
  CHECK(std::string("min") == time_unit_t::units_str[time_unit_t::MINUTES]);
  CHECK(std::string("s") == time_unit_t::units_str[time_unit_t::SECONDS]);
  CHECK(std::string("ms") == time_unit_t::units_str[time_unit_t::MILLISECONDS]);
  CHECK(std::string("us") == time_unit_t::units_str[time_unit_t::MICROSECONDS]);
  CHECK(std::string("ns") == time_unit_t::units_str[time_unit_t::NANOSECONDS]);
  CHECK(std::string("?") == time_unit_t::units_str[time_unit_t::ADAPTIVE]);
}

TEST_CASE("stw metric create type validator", "[stopwatch]") {
  CHECK(stw_metric_t::create(stw_metric_t::AVG)->type() == "avg");
  CHECK(stw_metric_t::create(stw_metric_t::MIN)->type() == "min");
  CHECK(stw_metric_t::create(stw_metric_t::MAX)->type() == "max");
  CHECK(stw_metric_t::create(stw_metric_t::SUM)->type() == "sum");
  CHECK(stw_metric_t::create(stw_metric_t::LAST)->type() == "last");
  CHECK(stw_metric_t::create(
            static_cast<stw_metric_t::stw_metric_impl_enum>(-1)) == nullptr);

  CHECK(stw_metric_t::create(stw_metric_t::AVG)->name() == "avg(0)");
  CHECK(stw_metric_t::create(stw_metric_t::MIN)->name() == "min");
  CHECK(stw_metric_t::create(stw_metric_t::MAX)->name() == "max");
  CHECK(stw_metric_t::create(stw_metric_t::SUM)->name() == "sum");
  CHECK(stw_metric_t::create(stw_metric_t::LAST)->name() == "last");

  CHECK(std::string("avg") == stw_metric_t::type_list[stw_metric_t::AVG]);
  CHECK(std::string("min") == stw_metric_t::type_list[stw_metric_t::MIN]);
  CHECK(std::string("max") == stw_metric_t::type_list[stw_metric_t::MAX]);
  CHECK(std::string("sum") == stw_metric_t::type_list[stw_metric_t::SUM]);
  CHECK(std::string("last") == stw_metric_t::type_list[stw_metric_t::LAST]);

  for (size_t i = 0; i < 5; ++i) {
    CHECK(stw_metric_t::type_list[i] ==
          stw_metric_t::create((stw_metric_t::stw_metric_impl_enum)i)->type());
  }
}

TEST_CASE("clock impl type validator", "[stopwatch]") {
  CHECK(clock_type::create(clock_type::CPU_CLOCK)->type() == "cpu_clock");
  CHECK(clock_type::create(clock_type::WALL_CLOCK)->type() == "wall_clock");
  CHECK(clock_type::create(static_cast<clock_type::clock_impl_enum>(-1)) ==
        nullptr);

  CHECK(std::string("cpu_clock") ==
        clock_type::type_list[clock_type::CPU_CLOCK]);
  CHECK(std::string("wall_clock") ==
        clock_type::type_list[clock_type::WALL_CLOCK]);

  for (size_t i = 0; i < 2; ++i) {
    CHECK(clock_type::type_list[i] ==
          clock_type::create((clock_type::clock_impl_enum)i)->type());
  }
}

TEST_CASE("min stw metric method validator", "[stopwatch]") {
  auto stws = {stw_metric_t::create(stw_metric_t::MIN),
               stw_metric_t::create(stw_metric_t::MAX),
               stw_metric_t::create(stw_metric_t::LAST),
               stw_metric_t::create(stw_metric_t::AVG),
               stw_metric_t::create(stw_metric_t::SUM)};
  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  std::uniform_real_distribution<double> dist{0, 1000};
  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
  for (size_t i = 0; i < 20; ++i) {
    std::vector<double> _(i + 1);
    std::generate(begin(_), end(_), gen);
    std::vector<double> cmp = {
        *std::min_element(_.begin(), _.end()),
        *std::max_element(_.begin(), _.end()),
        _[i],
        std::accumulate(_.begin(), _.end(), 0.0) / (i + 1),
        std::accumulate(_.begin(), _.end(), 0.0),
    };
    int j = 0;
    for (const auto& stw : stws) {
      stw->reset();
      for (const auto v : _) {
        stw->eval(v);
      }
      CHECK(near(stw->elapsed(), cmp[j++]));
    }
  }
}

TEST_CASE("test stopwatch manager", "[stopwatch]") {
  auto& _ = stopwatch_manager_t::default_stw_manager();

  auto id = _.create(chaos::utils::clock_type::WALL_CLOCK,
                     chaos::utils::time_unit_t::SECONDS);
  CHECK(_.get(id)->clock_impl() ==
        clock_type::type_list[chaos::utils::clock_type::WALL_CLOCK]);
  CHECK(_.get(id) != nullptr);
  CHECK(_.get(id + 1) == nullptr);
  CHECK(_.get(id - 1) == nullptr);

  _.remove(id);
  CHECK(_.get(id) == nullptr);

  _.add(0, std::make_shared<stopwatch_t>(chaos::utils::clock_type::CPU_CLOCK));
  CHECK(_.get(0) != nullptr);
  CHECK(_.get(0)->clock_impl() ==
        clock_type::type_list[chaos::utils::clock_type::CPU_CLOCK]);
}

TEST_CASE("check stopwatch interface", "[stopwatch]") {
  stopwatch_t stw;
  stw.set_clock_impl(chaos::utils::clock_type::CPU_CLOCK);
  CHECK(stw.clock_impl() == "cpu_clock");
  stw.set_clock_impl(chaos::utils::clock_type::WALL_CLOCK);
  CHECK(stw.clock_impl() == "wall_clock");

  stw.start();
  stw.start();  //-> this will cause a warning and restart stw.
  stw.stop();
  stw.record();

  stw.start();
  stw.record();  //-> this will auto stop the stw.

  stw.elapsed();        //-> this will return the last elapsed cost.
  stw.const_elapsed();  //-> this will return the last elapsed cost.

  stw.start();
  stw.elapsed();  //-> this will auto stop the stw and return cost.

  stw.reset();
  stw.set_metric({stw_metric_t::AVG});
  stw.add_metric({stw_metric_t::MIN, stw_metric_t::MAX});
  stw.add_metric(stw_metric_t::LAST);
  stw.elapsed_metric(stw_metric_t::AVG);

#ifndef _WIN32
  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(1e20);
  CHECK(stw.time_unit() == time_unit_t::HOURS);

  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(1e3);
  CHECK(stw.time_unit() == time_unit_t::NANOSECONDS);

  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(1e6);
  CHECK(stw.time_unit() == time_unit_t::MICROSECONDS);

  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(1e9);
  CHECK(stw.time_unit() == time_unit_t::MILLISECONDS);

  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(1e11);
  CHECK(stw.time_unit() == time_unit_t::SECONDS);

  stw.set_time_unit(time_unit_t::ADAPTIVE);
  stw.adaptive_cost(5e12);
  CHECK(stw.time_unit() == time_unit_t::MINUTES);
#endif

  STW_START("test event");
  STW_STOP("test event");
  STW_END("test event");

  STW_START("test event");
  STW_END("test event");
}
