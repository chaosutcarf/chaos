set(header line.h)
set(source line.cc)
add_library(chaos_io_line ${header} ${source})

target_link_libraries(chaos_io_line
  PUBLIC
  chaos::common)
