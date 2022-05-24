add_library(chaos_problem INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_problem
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_problem
  INTERFACE
  chaos::common
  chaos::utils
  chaos::mapping
  )
