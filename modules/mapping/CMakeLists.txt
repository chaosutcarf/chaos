add_library(chaos_mapping INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_mapping
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_mapping
  INTERFACE
  chaos::common
  chaos::utils
  )
