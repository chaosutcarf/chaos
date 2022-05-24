set(header logger.h)
add_library(chaos_utils_logger INTERFACE)

target_compile_features(chaos_utils_logger INTERFACE
  cxx_std_17)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_utils_logger
  INTERFACE
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_utils_logger
  INTERFACE
  spdlog::spdlog)
