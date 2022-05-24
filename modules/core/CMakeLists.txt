add_library(chaos_core utils.h utils.cc)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_core
  PUBLIC
  ${ABS_INCLUDE_DIR}
  )

set(chaos_core_modules
  svd
  evd
  tridiag
  linearsolver
  quadrature
  )

foreach(module ${chaos_core_modules})
  add_subdirectory(${module})
  string(CONCAT core_lib "chaos_core_" ${module})
  add_library(chaos::core::${module} ALIAS ${core_lib})
  message(STATUS "link library: ${core_lib}")
  target_link_libraries(chaos_core PUBLIC ${core_lib})
endforeach(module)
