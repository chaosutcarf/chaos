add_library(chaos_core_svd INTERFACE)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_core_svd
  INTERFACE
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_core_svd
  INTERFACE
  Eigen3::Eigen
  )
