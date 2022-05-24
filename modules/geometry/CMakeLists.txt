add_library(chaos_geometry INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_geometry
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_geometry
  INTERFACE
  chaos::common
  chaos::utils
  )
