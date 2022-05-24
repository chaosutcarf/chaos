#include "utils/logger/logger.h"

#include <catch2/catch.hpp>
#include <exception>
#include <iostream>
using namespace chaos::utils;
using namespace std;

TEST_CASE("logger callable", "[logger]") {
  CHECK_NOTHROW(logger::default_logger());
  CHECK_NOTHROW(logger::set_level(spdlog::level::warn));
  CHECK_NOTHROW(logger::set_level(spdlog::level::info));
  CHECK_NOTHROW(logger::set_level(spdlog::level::err));
  CHECK_NOTHROW(logger::set_level(spdlog::level::critical));
  CHECK_NOTHROW(logger::set_level(spdlog::level::debug));

  /// enable filelogger
  logger::add_log_sink("logger.log");
  info_msg("chaos info: {}", 1);
  info_msg_if(1 == 1, "chaos info condition: 1==1");
  info_msg_if(1 == 2, "chaos info condition: 1==2, do not show");
  info_msg_handler_if({ cout << "info handler" << endl; }, 1 == 1,
                      "test handler");
  warn_msg("chaos warn: {}", 1);
  warn_msg_if(1 == 1, "chaos warn condition: 1==1");
  warn_msg_if(1 == 2, "chaos warn condition: 1==2, do not show");
  warn_msg_handler_if({ cout << "warn handler" << endl; }, 1 == 1,
                      "test handler");
  error_msg("chaos error: {}", 1);
  error_msg_if(1 == 1, "chaos error condition: 1==1");
  error_msg_if(1 == 2, "chaos error condition: 1==2, do not show");
  error_msg_handler_if({ cout << "error handler" << endl; }, 1 == 1,
                       "test handler");

  try {
    critical_msg("chaos critical: {}", 1);
    critical_msg_if(1 == 1, "chaos critical condition: 1==1");
    critical_msg_if(1 == 2, "chaos critical condition: 1==2, do not show");
    critical_msg_handler_if({ cout << "critical handler" << endl; }, 1 == 1,
                            "test handler");
  } catch (std::exception &e) {
    CHECK(e.what() == std::string("critical error!"));
  }

  debug_msg("chaos debug: {}", 1);
  debug_msg_if(1 == 1, "chaos debug condition: 1==1");
  debug_msg_if(1 == 2, "chaos debug condition: 1==2, do not show");
  debug_msg_handler_if({ cout << "debug handler" << endl; }, 1 == 1,
                       "test handler");

  //-> this will change the prefix to [debug/info/...]
  //-> can be found here:
  //-> https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
  chaos::utils::logger::set_pattern("[%^%l%$] %v");

  //-> get logger and create new logger
  auto &logger2 = chaos::utils::logger::create_file_logger("test.logger");
  auto &get_log2 = chaos::utils::logger::get_logger("test.logger");
  CHECK(&logger2 == &get_log2);
}
