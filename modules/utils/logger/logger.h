/** -*- mode: c++ -*-
 * @file logger.h
 * @author LamKamhang (Cool_Lam@outlook.com)
 * @brief A Documented file.
 * @version 1.0
 * @date Sunday, September 27, 2020 PM10:28:37 CST
 *
 * Detailed description
 *
 *
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <memory.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
// user defined types logging by implementing operator<<
#include <spdlog/fmt/bundled/ranges.h>
#include <spdlog/fmt/ostr.h>  // must be included

#include <map>
#include <stdexcept>

#ifdef _WIN32
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

namespace chaos::utils {

class logger {
 public:
  // default logger:
  static spdlog::logger &default_logger() {
    static spdlog::logger dlog(
        "", {std::make_shared<spdlog::sinks::stdout_color_sink_mt>()});
    static bool init_flag = false;
    if (!init_flag) {
#ifndef NO_DEBUG_MSG
      dlog.set_level(spdlog::level::debug);
#else
      dlog.set_level(spdlog::level::info);
#endif
      dlog.set_pattern("[%^%l%$] %v", spdlog::pattern_time_type::local);
      init_flag = true;
    }
    return dlog;
  }

  static spdlog::logger &get_logger(const std::string &name) {
    static std::map<std::string, std::shared_ptr<spdlog::logger>> logs_pool;
    auto iter = logs_pool.find(name);
    if (iter == logs_pool.end()) {
      auto log = std::make_shared<spdlog::logger>(name, basic_file_sink(name));
      logs_pool.insert({name, log});
      return *log;
    } else {
      return *iter->second;
    }
  }

  //-> create logger:
  static spdlog::logger &create_file_logger(const std::string &name) {
    return get_logger(name);
  }

  static void set_pattern(const std::string &pattern,
                          spdlog::pattern_time_type time_type,
                          spdlog::logger &log = default_logger()) {
    log.set_pattern(pattern, time_type);
  }

  static void set_pattern(const std::string &pattern,
                          spdlog::logger &log = default_logger()) {
    set_pattern(pattern, spdlog::pattern_time_type::local, log);
  }

  static spdlog::level::level_enum set_level(
      spdlog::level::level_enum level, spdlog::logger &log = default_logger()) {
    auto old_level = log.level();
    log.set_level(level);
    return old_level;
  }

  static spdlog::level::level_enum set_info_level() {
    return set_level(spdlog::level::level_enum::info);
  }

  static spdlog::level::level_enum set_warn_level() {
    return set_level(spdlog::level::level_enum::warn);
  }

  static spdlog::level::level_enum set_error_level() {
    return set_level(spdlog::level::level_enum::err);
  }

  static spdlog::level::level_enum set_debug_level() {
    return set_level(spdlog::level::level_enum::debug);
  }

  static spdlog::level::level_enum off() {
    return set_level(spdlog::level::level_enum::off);
  }

  static spdlog::sink_ptr stdout_sink() {
    return std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  }
  static spdlog::sink_ptr basic_file_sink(const std::string &filename) {
    return std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
  }
  static void add_log_sink(const spdlog::sink_ptr &single_sink,
                           spdlog::logger &log = default_logger()) {
    log.sinks().emplace_back(single_sink);
  }
  static void add_log_sink(const spdlog::sinks_init_list &sinks,
                           spdlog::logger &log = default_logger()) {
    for (const auto &sink : sinks) {
      log.sinks().emplace_back(sink);
    }
  }
  static void add_log_sink(const std::string &filename,
                           spdlog::logger &log = default_logger()) {
    add_log_sink(basic_file_sink(filename), log);
  }
  static void set_log_sink(spdlog::sink_ptr single_sink,
                           spdlog::logger &log = default_logger()) {
    log.sinks() = {std::move(single_sink)};
  }
  static void set_log_sink(spdlog::sinks_init_list sinks,
                           spdlog::logger &log = default_logger()) {
    log.sinks() = sinks;
  }
  static void set_log_sink(const std::string &filename,
                           spdlog::logger &log = default_logger()) {
    set_log_sink(basic_file_sink(filename), log);
  }
};

}  // namespace chaos::utils

#define info_msg_handler_if(expr, cond, fmt, ...)                      \
  do {                                                                 \
    if (cond) {                                                        \
      chaos::utils::logger::default_logger().info(fmt, ##__VA_ARGS__); \
      expr;                                                            \
    }                                                                  \
  } while (0)

#define error_msg_handler_if(expr, cond, fmt, ...)                      \
  do {                                                                  \
    if (cond) {                                                         \
      chaos::utils::logger::default_logger().error(fmt, ##__VA_ARGS__); \
      expr;                                                             \
    }                                                                   \
  } while (0)

#define warn_msg_handler_if(expr, cond, fmt, ...)                      \
  do {                                                                 \
    if (cond) {                                                        \
      chaos::utils::logger::default_logger().warn(fmt, ##__VA_ARGS__); \
      expr;                                                            \
    }                                                                  \
  } while (0)

#define critical_msg_handler_if(expr, cond, fmt, ...)                      \
  do {                                                                     \
    if (cond) {                                                            \
      chaos::utils::logger::default_logger().critical(fmt, ##__VA_ARGS__); \
      expr;                                                                \
    }                                                                      \
  } while (0)

#ifndef NDEBUG
#define debug_msg_handler_if(expr, cond, fmt, ...)                      \
  do {                                                                  \
    if (cond) {                                                         \
      chaos::utils::logger::default_logger().debug(fmt, ##__VA_ARGS__); \
      expr;                                                             \
    }                                                                   \
  } while (0)
#else
#define debug_msg_handler_if(expr, cond, fmt, ...)
#endif

#define info_msg_if(cond, fmt, ...) \
  info_msg_handler_if(;, cond, fmt, ##__VA_ARGS__)
#define error_msg_if(cond, fmt, ...) \
  error_msg_handler_if(;, cond, fmt, ##__VA_ARGS__)
#define warn_msg_if(cond, fmt, ...) \
  warn_msg_handler_if(;, cond, fmt, ##__VA_ARGS__)
#define critical_msg_if(cond, fmt, ...)                                    \
  critical_msg_handler_if(throw std::logic_error("critical error!"), cond, \
                          fmt, ##__VA_ARGS__)
#define debug_msg_if(cond, fmt, ...) \
  debug_msg_handler_if(;, cond, fmt, ##__VA_ARGS__)

#define info_msg(fmt, ...) info_msg_if(true, fmt, ##__VA_ARGS__)
#define error_msg(fmt, ...) error_msg_if(true, fmt, ##__VA_ARGS__)
#define warn_msg(fmt, ...) warn_msg_if(true, fmt, ##__VA_ARGS__)
#define critical_msg(fmt, ...) critical_msg_if(true, fmt, ##__VA_ARGS__)
#define debug_msg(fmt, ...) debug_msg_if(true, fmt, ##__VA_ARGS__)

// Make a FOREACH macro
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X) FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X) FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X) FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X) FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X) FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X) FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X) FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X) FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X) FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X) FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X) FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT(X) FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT(X) FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT(X) FE_14(WHAT, __VA_ARGS__)
#define FE_16(WHAT, X, ...) WHAT(X) FE_15(WHAT, __VA_ARGS__)
#define FE_17(WHAT, X, ...) WHAT(X) FE_16(WHAT, __VA_ARGS__)
#define FE_18(WHAT, X, ...) WHAT(X) FE_17(WHAT, __VA_ARGS__)
#define FE_19(WHAT, X, ...) WHAT(X) FE_18(WHAT, __VA_ARGS__)
#define FE_20(WHAT, X, ...) WHAT(X) FE_19(WHAT, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, \
                  _14, _15, _16, _17, _18, _19, _20, NAME, ...)               \
  NAME
#define FOR_EACH(...)                                                       \
  GET_MACRO(__VA_ARGS__, FE_20, FE_19, FE_18, FE_17, FE_16, FE_15, FE_14,   \
            FE_13, FE_12, FE_11, FE_10, FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, \
            FE_3, FE_2, FE_1, FE_0)                                         \
  (__VA_ARGS__)

#define PRINT_PARAM(arg) \
  chaos::utils::logger::default_logger().error("\t{{ " #arg " :-> {} }}", arg);

#define CHAOS_ASSERT_EXT_HANDLER(handler, expr, event, ...)        \
  do {                                                             \
    if (!(expr)) {                                                 \
      chaos::utils::logger::default_logger().error(                \
          "@{}:{} [{}]", __FILE__, __LINE__, __PRETTY_FUNCTION__); \
      chaos::utils::logger::default_logger().error(                \
          "{} failed ==> [{}] is violated: {{", event, #expr);     \
      FOR_EACH(PRINT_PARAM, ##__VA_ARGS__);                        \
      chaos::utils::logger::default_logger().error("}");           \
      handler;                                                     \
    }                                                              \
  } while (0)

#define CHAOS_ASSERT_EXT(expr, event, ...)                             \
  CHAOS_ASSERT_EXT_HANDLER(throw std::logic_error(event), expr, event, \
                           ##__VA_ARGS__)

#define CHAOS_ASSERT(expr, ...) CHAOS_ASSERT_EXT(expr, #expr, ##__VA_ARGS__)

#define CHAOS_ASSERT_HANDLER(handler, expr, ...) \
  CHAOS_ASSERT_EXT_HANDLER(handler, expr, #expr, ##__VA_ARGS__)

#ifndef NDEBUG
#define CHAOS_DEBUG_ASSERT(expr, ...) CHAOS_ASSERT(expr, ##__VA_ARGS__)
#define CHAOS_DEBUG_ASSERT_EXT(expr, event, ...) \
  CHAOS_ASSERT_EXT(expr, event, ##__VA_ARGS__)
#else
#define CHAOS_DEBUG_ASSERT(expr, ...)
#define CHAOS_DEBUG_ASSERT_EXT(expr, event, ...)
#endif
