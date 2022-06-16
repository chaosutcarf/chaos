file(GLOB_RECURSE source "*.cc")
file(GLOB_RECURSE header "*.hpp")
add_library(chaos_mapping ${source} ${header})

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_mapping
  PUBLIC
  ${ABS_INCLUDE_DIR}
  )

target_link_libraries(chaos_mapping
  PUBLIC
  chaos::common
  chaos::utils
  OpenMP::OpenMP_CXX
  )
