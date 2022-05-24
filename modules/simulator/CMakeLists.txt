add_library(chaos_simulator INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_simulator
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_simulator
  INTERFACE
  chaos::geometry
  chaos::model
  chaos::misc
  )
