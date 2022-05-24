add_library(chaos_core_evd evd.cc evd.h)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_core_evd
  PUBLIC
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_core_evd
  PUBLIC
  chaos::common
  chaos::utils
  Spectra::Spectra
  )
