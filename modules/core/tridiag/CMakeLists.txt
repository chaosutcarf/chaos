add_library(chaos_core_tridiag tridiagonal.cc)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_core_tridiag
  PUBLIC
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_core_tridiag
  PUBLIC
  chaos::common
  chaos::utils
  )
