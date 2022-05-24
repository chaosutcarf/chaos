add_library(chaos_misc INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_misc
  INTERFACE
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_misc
  INTERFACE
  chaos::common
  chaos::utils
  )
