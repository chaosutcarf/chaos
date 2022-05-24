cmake_minimum_required(VERSION 3.9)

add_library(chaos INTERFACE)

target_include_directories(chaos INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  )

#----------------------------------------------------------------------------
# Common compile options and definitions
#----------------------------------------------------------------------------
target_compile_options(chaos INTERFACE
  # Compiler is GNU (g++):
  $<$<CXX_COMPILER_ID:GNU>:$<BUILD_INTERFACE:-Wall;-Wextra>>
  # Compiler is Clang:
  $<$<CXX_COMPILER_ID:Clang>:$<BUILD_INTERFACE:-Wall;-Wextra>>
  # Compiler is MSVC:
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
  $<$<CXX_COMPILER_ID:MSVC>:/wd4715>
  )

include(CheckIPOSupported)
check_ipo_supported(RESULT iporesult)

set(chaos_modules
  common utils   # 1st level
  io core mapping maxima # 2nd level
  problem optimizer # 3rd level
  geometry model misc # 4th level
  simulator # 5th level
  )

if(CHAOS_BUILD_WITH_GUI)
  add_subdirectory(gui)
  add_library(chaos::gui ALIAS chaos_gui)
endif(CHAOS_BUILD_WITH_GUI)

foreach (module ${chaos_modules})
  add_subdirectory(${module})
  string(CONCAT chaos_lib "chaos_" ${module})
  add_library(chaos::${module} ALIAS ${chaos_lib})
  message(STATUS "link library: ${chaos_lib}")
  target_link_libraries(chaos INTERFACE ${chaos_lib})
endforeach(module)
