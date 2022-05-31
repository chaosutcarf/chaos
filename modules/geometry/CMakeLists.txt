add_library(chaos_geometry line.cc)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_geometry
  PUBLIC
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_geometry
  PUBLIC
  chaos::common
  chaos::utils
  )
