/** -*- mode: c++ -*-
 * @file stopwatch.cc
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Monday, June 28, 2021 PM06:43:33 HKT
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2021
 */
#include "stopwatch.h"

#include <chrono>
#include <ctime>
#include <ratio>

#include "utils/logger/logger.h"
#include "utils/stopwatch/clock_type.h"
#include "utils/stopwatch/stw_metric.h"
#include "utils/stopwatch/type.h"

namespace chaos::utils {

void stopwatch_t::set_clock_impl(clock_type::clock_impl_enum clock_impl) {
  if (clock->type() != clock_type::type_list[(int)clock_impl]) {
    clock = clock_type::create(clock_impl);
  }
}

void stopwatch_t::record(spdlog::logger &logger) {
  warn_msg_handler_if(return, isreset, "the stopwatch({}) is never started.",
                            event);
  if (!isstop) {
    stop();
  }
  const_record(logger);
}

void stopwatch_t::const_record(spdlog::logger &logger) const {
  warn_msg_handler_if(return, isreset, "the stopwatch is never started.");
  warn_msg_handler_if(return, !isstop, "the stopwatch is still running.");
  for (const auto &metric : metric_list) {
    logger.info("{} [{}] costs {} {}.", event, metric->name(),
                metric->elapsed(), time_unit_t::units_str[(int)unit]);
  }
}

rep_t stopwatch_t::elapsed() {
  CHAOS_ASSERT(!metric_list.empty());
  if (!isstop) {
    stop();
  }
  return const_elapsed();
}

rep_t stopwatch_t::const_elapsed() const {
  CHAOS_ASSERT(!metric_list.empty());
  warn_msg_if(!isstop,
              "the stopwatch is still running! const elapsed is not correct!");

  //-> return the first important one.
  return (*metric_list.begin())->elapsed();
}

void stopwatch_t::start() {
  warn_msg_if(!isstop, "the stopwatch({}) has started. Now it will reset it.",
              event);
  isreset = false;
  isstop = false;
  clock->start();
}

void stopwatch_t::stop() {
  warn_msg_handler_if(return, isreset, "the stopwatch is never started.");
  warn_msg_handler_if(
      return, isstop, "the stopwatch({}) has stopped. This stop will not work.",
            event);
  auto cost = adaptive_cost(clock->elapsed(unit));
  isstop = true;
  for (const auto &metric : metric_list) {
    metric->eval(cost);
  }
}

void stopwatch_t::end() { record(); }

void stopwatch_t::reset(const std::string &event,
                        clock_type::clock_impl_enum clock_impl,
                        time_unit_t::time_unit_enum unit) {
  this->event = event;
  this->unit = unit;
  set_clock_impl(clock_impl);
  this->isstop = this->isreset = true;
  for (auto &metric : metric_list) {
    metric->reset();
  }
}

rep_t stopwatch_t::adaptive_cost(const rep_t cost) {
  if (unit != time_unit_t::ADAPTIVE) {
    return cost;
  } else {
    constexpr double _[]{1, 1e-3, 1e-6, 1e-9, 1e-9 / 60, 1e-9 / 3600};
    //-> else, the input cost will be nanoseconds.
    constexpr auto converter =
        [](const rep_t cost) -> time_unit_t::time_unit_enum {
      constexpr double level[]{4, 7, 10, 12, 13};
      auto _ = std::log10(cost);
      for (size_t i = 0; i < 5; ++i) {
        if (_ < level[i]) {
          return (time_unit_t::time_unit_enum)i;
        }
      }
      return time_unit_t::HOURS;
    };
    unit = converter(cost);
    return cost * _[(int)unit];
  }
}

void stopwatch_t::set_metric(
    const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list) {
  this->metric_list.clear();
  add_metric(metric_list);
}

void stopwatch_t::add_metric(stw_metric_t::stw_metric_impl_enum m) {
  this->metric_list.emplace_back(stw_metric_t::create(m));
}

void stopwatch_t::add_metric(
    const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list) {
  for (const auto &m : metric_list) {
    add_metric(m);
  }
}

void stopwatch_t::elapsed_metric(stw_metric_t::stw_metric_impl_enum m) {
  metric_list.remove_if([&m](const metric_t &_) {
    return _->type() == stw_metric_t::type_list[static_cast<int>(m)];
  });
  metric_list.emplace_front(stw_metric_t::create(m));
}

///////////////////////////////////////////////////////////////////////////
//                    stopwatch manager implementation                   //
///////////////////////////////////////////////////////////////////////////
stopwatch_manager_t::stopwatch_manager_t() {
  // register default logger.
  logger::default_logger();
}

stopwatch_manager_t::~stopwatch_manager_t() {
  //-> sort.
  std::map<std::string, std::shared_ptr<stopwatch_t>> sort_stw;
  for (const auto &stw : stwmaps) {
    sort_stw.insert({stw.second->get_event(), stw.second});
  }
  for (const auto &stw : sort_stw) {
    stw.second->end();
  }
}

stopwatch_id_t stopwatch_manager_t::create(
    clock_type::clock_impl_enum clock_impl, time_unit_t::time_unit_enum unit,
    const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list) {
  auto stw = std::make_shared<stopwatch_t>(clock_impl, unit, metric_list);
  stopwatch_id_t id = std::hash<decltype(stw)>{}(stw);
  stwmaps.insert({id, stw});
  return id;
}

void stopwatch_manager_t::remove(stopwatch_id_t id) { stwmaps.erase(id); }

std::shared_ptr<stopwatch_t> stopwatch_manager_t::get(stopwatch_id_t id) const {
  const auto iter = stwmaps.find(id);
  if (iter != stwmaps.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}
void stopwatch_manager_t::add(stopwatch_id_t id,
                              const std::shared_ptr<stopwatch_t> &stw) {
  stwmaps[id] = stw;
}

///////////////////////////////////////////////////////////////////////////////
//                         stopwatch helper functions                        //
///////////////////////////////////////////////////////////////////////////////
void STW_START(const stopwatch_id_t &id, const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list,
               clock_type::clock_impl_enum clock_impl,
               time_unit_t::time_unit_enum unit) {
  auto stw = stopwatch_manager_t::default_stw_manager().get(id);
  if (stw == nullptr) {
    stw = std::make_shared<stopwatch_t>(event, clock_impl, unit, metric_list);
    stopwatch_manager_t::default_stw_manager().add(id, stw);
  }
  stw->start();
}

void STW_START(const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list,
               clock_type::clock_impl_enum clock_impl,
               time_unit_t::time_unit_enum unit) {
  STW_START(event, event, metric_list, clock_impl, unit);
}

void STW_START(const std::string &id, const std::string &event,
               const std::set<stw_metric_t::stw_metric_impl_enum> &metric_list,
               clock_type::clock_impl_enum clock_impl,
               time_unit_t::time_unit_enum unit) {
  STW_START(std::hash<std::string>{}(id), event, metric_list, clock_impl, unit);
}

void STW_STOP(const stopwatch_id_t &id) {
  const auto &stw = stopwatch_manager_t::default_stw_manager().get(id);
  if (stw != nullptr) {
    stw->stop();
  }
}

void STW_STOP(const std::string &event) {
  STW_STOP(std::hash<std::string>{}(event));
}

void STW_END(const stopwatch_id_t &id) {
  const auto &stw = stopwatch_manager_t::default_stw_manager().get(id);
  if (stw != nullptr) {
    stw->end();
    // TODO::make a stw pool to manage stws.
    stopwatch_manager_t::default_stw_manager().remove(id);
  }
}

void STW_END(const std::string &event) {
  STW_END(std::hash<std::string>{}(event));
}

}  // namespace chaos::utils
