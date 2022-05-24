add_library(chaos_model INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_model
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_model
  INTERFACE
  chaos::common
  chaos::utils
  )
