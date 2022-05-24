set(header type.h stopwatch.h stw_metric.h)
set(source stopwatch.cc clock_type.cc stw_metric.cc)

add_library(chaos_utils_stopwatch ${source} ${header})

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../ ABSOLUTE)

target_include_directories(chaos_utils_stopwatch
  INTERFACE
  ${ABS_INCLUDE_DIR})

target_link_libraries(chaos_utils_stopwatch
  PUBLIC
  chaos::utils::logger
  )

if(iporesult)
  set_target_properties(chaos_utils_stopwatch
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
