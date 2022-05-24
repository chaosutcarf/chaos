set(header fshelper.h)
set(source fshelper.cc)
add_library(chaos_utils_fs ${header} ${source})
add_library(chaos::utils::fs ALIAS chaos_utils_fs)

target_compile_features(chaos_utils_fs PUBLIC
  cxx_std_17)
get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_utils_fs
  PUBLIC
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_utils_fs
  PUBLIC
  chaos::utils::logger)
