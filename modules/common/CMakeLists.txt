add_library(chaos_common common.cc)

target_compile_features(chaos_common PUBLIC
  cxx_std_17)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_common
  PUBLIC
  ${ABS_INCLUDE_DIR})

set(chaos_common_modules
  )

foreach(module ${chaos_common_modules})
  add_subdirectory(${module})
  string(CONCAT common_lib "chaos_common_" ${module})
  add_library(chaos::common::${module} ALIAS ${common_lib})
  message(STATUS "link library: ${common_lib}")
  target_link_libraries(chaos_common PUBLIC ${common_lib})
endforeach(module)

target_link_libraries(chaos_common
  PUBLIC
  Eigen3::Eigen
  chaos::utils::logger
  )
