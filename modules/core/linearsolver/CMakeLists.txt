set(source linearsolver.cc)
if (CHAOS_BUILD_WITH_PARDISO)
  set(source ${source} pardiso_solver.cc)
endif(CHAOS_BUILD_WITH_PARDISO)

add_library(chaos_core_linearsolver ${source})

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_core_linearsolver
  PUBLIC
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_core_linearsolver
  PUBLIC
  chaos::common
  chaos::utils
  )

if (CHAOS_BUILD_WITH_PARDISO)
  target_compile_definitions(chaos_core_linearsolver PUBLIC USE_PARDISO)
  target_link_libraries(chaos_core_linearsolver PUBLIC pardiso)
endif(CHAOS_BUILD_WITH_PARDISO)

if (CHAOS_BUILD_WITH_SUITESPARSE)
  target_compile_definitions(chaos_core_linearsolver PUBLIC USE_SUITESPARSE)
  target_link_libraries(chaos_core_linearsolver PUBLIC SuiteSparse::cholmod SuiteSparse::umfpack)
endif(CHAOS_BUILD_WITH_SUITESPARSE)
