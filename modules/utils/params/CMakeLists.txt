add_library(chaos_utils_params INTERFACE)

target_compile_features(chaos_utils_params INTERFACE
  cxx_std_17)
get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_utils_params
  INTERFACE
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_utils_params
  INTERFACE
  chaos::utils::logger
  chaos::utils::fs
  CLI11::CLI11)

if (CHAOS_BUILD_WITH_JSON)
  target_link_libraries(chaos_utils_params
    INTERFACE
    nlohmann_json::nlohmann_json
    )
endif(CHAOS_BUILD_WITH_JSON)
