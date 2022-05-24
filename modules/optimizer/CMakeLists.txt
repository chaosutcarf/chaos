add_library(chaos_optimizer INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_optimizer
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_optimizer
  INTERFACE
  chaos::common
  chaos::utils
  chaos::mapping
  )
