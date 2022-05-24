set(source
  quadrature.cc
  details/gauss_legendre.cc
  details/tri.cc
  details/tet.cc
  )

add_library(chaos_core_quadrature ${source})

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_core_quadrature
  PUBLIC
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_core_quadrature
  PUBLIC
  chaos::common
  chaos::utils
  )
