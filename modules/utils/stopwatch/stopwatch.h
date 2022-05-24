/** -*- mode: c++ -*-
 * @file stopwatch.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Sunday, June 20, 2021 PM11:48:10 CST
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#include <utils/logger/logger.h>
#include <utils/stopwatch/clock_type.h>
#include <utils/stopwatch/stw_metric.h>

#include <list>
#include <set>
#include <string>
#include <unordered_map>

#include "utils/stopwatch/type.h"

namespace chaos::utils {
class stopwatch_t {
 public:
  using metric_t = std::unique_ptr<stw_metric_t>;
  using clock_ptr_t = std::unique_ptr<clock_type>;
  using metric_list_t = std::list<metric_t>;

  explicit stopwatch_t(
      const std::string &event,
      clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
      time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE,
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
          {stw_metric_t::AVG})
      : clock(clock_type::create(clock_impl)),
        event(event),
        unit(unit),
        isstop(true),
        isreset(true) {
    for (const auto &m : metric_list) {
      debug_msg("create stw.metric: {}", stw_metric_t::type_list[m]);
      this->metric_list.emplace_back(stw_metric_t::create(m));
    }
  }

  explicit stopwatch_t(
      clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
      time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE,
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
          {stw_metric_t::AVG})
      : stopwatch_t("", clock_impl, unit, metric_list) {}

  void set_time_unit(const time_unit_t::time_unit_enum &unit) {
    this->unit = unit;
  }
  time_unit_t::time_unit_enum time_unit() const { return unit; }

  void set_clock_impl(clock_type::clock_impl_enum clock_impl);
  std::string clock_impl() const { return clock->type(); }

  void start(const std::string &event,
             clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
             time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE);
  void start();
  void stop();
  void end();
  void reset(const std::string &event = "",
             clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
             time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE);

  rep_t elapsed();
  rep_t const_elapsed() const;
  void record(spdlog::logger &logger = logger::default_logger());
  void const_record(spdlog::logger &logger = logger::default_logger()) const;

  void set_metric(
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list);
  void add_metric(stw_metric_t::stw_metric_impl_enum m);
  void add_metric(
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list);
  void elapsed_metric(stw_metric_t::stw_metric_impl_enum m);
  const std::string &get_event() const { return event; }

 private:
  rep_t adaptive_cost(const rep_t cost);

  clock_ptr_t clock;
  metric_list_t metric_list;
  std::string event;
  time_unit_t::time_unit_enum unit;
  bool isstop{true}, isreset{true};
};

///////////////////////////////////////////////////////////////////////////////
//                              stopwatch helper                             //
///////////////////////////////////////////////////////////////////////////////

class stopwatch_guard_t {
 public:
  explicit stopwatch_guard_t(
      const std::string &event,
      clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
      time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE,
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
          {stw_metric_t::AVG})
      : stw(event, clock_impl, unit, metric_list) {
    this->stw.start();
  }

  ~stopwatch_guard_t() { stw.end(); }

  void stop() { stw.stop(); }
  void start() { stw.start(); }

 private:
  stopwatch_t stw;
};

class stopwatch_stop_proxy_t {
 public:
  explicit stopwatch_stop_proxy_t(stopwatch_t &stw) : stw(stw) { stw.start(); }
  ~stopwatch_stop_proxy_t() { stw.stop(); }

 private:
  stopwatch_t &stw;
};

class stopwatch_manager_t {
 public:
  static stopwatch_manager_t &default_stw_manager() {
    static stopwatch_manager_t instance;
    return instance;
  }

  //-> register logger.
  stopwatch_manager_t();
  stopwatch_manager_t(const stopwatch_manager_t &) = delete;
  stopwatch_manager_t &operator=(const stopwatch_manager_t &) = delete;
  stopwatch_manager_t(const stopwatch_manager_t &&) = delete;
  stopwatch_manager_t &operator=(const stopwatch_manager_t &&) = delete;
  // auto show the remain stopwatch.
  ~stopwatch_manager_t();

 public:
  // create, remove, get.
  /**
   * @brief create a stopwatch and return its corresponding id.
   *
   * @param scale : customize the scale of the stopwatch.
   * @return stopwatch_id_t : the id of the stopwatch.
   */
  stopwatch_id_t create(
      clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
      time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE,
      const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list = {
          stw_metric_t::AVG});

  /**
   * @brief remove the stopwatch from the manager.
   *
   * @param id : the corresponding id of the stopwatch.
   */
  void remove(stopwatch_id_t id);

  /**
   * @brief get the corresponding stopwatch using the id.
   * [note1:] if there is no stopwatch with such id, this function
   * will create a stopwatch with it, which means this function will
   * also create a new stopwatch if not such stopwatch
   *
   * @param id : the stopwatch id.
   * @return std::shared_ptr<stopwatch_t> : return the corresponding stw.
   */
  [[nodiscard]] std::shared_ptr<stopwatch_t> get(stopwatch_id_t id) const;

  void add(stopwatch_id_t id, const std::shared_ptr<stopwatch_t> &stw);

  void set_default_stw_metric_list(
      const std::set<stw_metric_t::stw_metric_impl_enum> &stw_metric_list) {
    this->default_stw_metric_list = stw_metric_list;
  }
  const std::set<stw_metric_t::stw_metric_impl_enum>
      &get_default_stw_metric_list() const {
    return default_stw_metric_list;
  }

 private:
  std::unordered_map<stopwatch_id_t, std::shared_ptr<stopwatch_t>> stwmaps;
  std::set<stw_metric_t::stw_metric_impl_enum> default_stw_metric_list{
      stw_metric_t::AVG, stw_metric_t::SUM, stw_metric_t::MIN,
      stw_metric_t::MAX};
};

///////////////////////////////////////////////////////////////////////////////
//                         stopwatch helper functions                        //
///////////////////////////////////////////////////////////////////////////////
void STW_START(const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
                   stopwatch_manager_t::default_stw_manager()
                       .get_default_stw_metric_list(),
               clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
               time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE);

void STW_START(const stopwatch_id_t &id, const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
                   stopwatch_manager_t::default_stw_manager()
                       .get_default_stw_metric_list(),
               clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
               time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE);

void STW_START(const std::string &id, const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list =
                   stopwatch_manager_t::default_stw_manager()
                       .get_default_stw_metric_list(),
               clock_type::clock_impl_enum clock_impl = clock_type::WALL_CLOCK,
               time_unit_t::time_unit_enum unit = time_unit_t::ADAPTIVE);

void STW_STOP(const stopwatch_id_t &id);
void STW_STOP(const std::string &event);
void STW_END(const stopwatch_id_t &id);
void STW_END(const std::string &event);
}  // namespace chaos::utils

#define CHAOS_BENCHMARK(event, program) \
  chaos::utils::STW_START(event);       \
  program;                              \
  chaos::utils::STW_END(event);

#define CHAOS_REPEAT_BENCHMARK(event, program) \
  chaos::utils::STW_START(event);              \
  program;                                     \
  chaos::utils::STW_STOP(event);
