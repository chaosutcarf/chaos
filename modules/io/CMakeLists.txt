add_library(chaos_io data_report.cc)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_io
  PUBLIC
  ${ABS_INCLUDE_DIR}
  )

set(chaos_io_modules
  line
  )

foreach(module ${chaos_io_modules})
  add_subdirectory(${module})
  string(CONCAT io_lib "chaos_io_" ${module})
  add_library(chaos::io::${module} ALIAS ${io_lib})
  message(STATUS "link library: ${io_lib}")
  target_link_libraries(chaos_io PUBLIC ${io_lib})
endforeach(module)

target_link_libraries(chaos_io PUBLIC chaos::utils::logger chaos::common)
