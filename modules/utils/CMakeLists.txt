add_library(chaos_utils INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_utils
  INTERFACE
  ${ABS_INCLUDE_DIR})

set(chaos_utils_modules
  logger
  stopwatch
  fs
  params
  )

foreach(module ${chaos_utils_modules})
  add_subdirectory(${module})
  string(CONCAT utils_lib "chaos_utils_" ${module})
  add_library(chaos::utils::${module} ALIAS ${utils_lib})
  message(STATUS "link library: ${utils_lib}")
  target_link_libraries(chaos_utils INTERFACE ${utils_lib})
endforeach(module)
