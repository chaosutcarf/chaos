cmake_minimum_required(VERSION 3.16)

project(
  chaos
  VERSION 0.1
  DESCRIPTION "a spare time project with cmake"
  LANGUAGES C CXX Fortran)

# Detects whether this is a top-level project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CHAOS_TOPLEVEL_PROJECT ON)
else(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CHAOS_TOPLEVEL_PROJECT OFF)
endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

# Set some additional cmake search paths
set(ADDITIONAL_CMAKE_PATH
  "${PROJECT_SOURCE_DIR}/cmake/"
  "${PROJECT_SOURCE_DIR}/3rd/"
  )
set(CUSTOM_CMAKE_PATH
  ""
  CACHE STRING "customized cmake search/module path"
  )

list(PREPEND CMAKE_MODULE_PATH ${ADDITIONAL_CMAKE_PATH} ${CUSTOM_CMAKE_PATH})
list(PREPEND CMAKE_PREFIX_PATH ${ADDITIONAL_CMAKE_PATH} ${CUSTOM_CMAKE_PATH})

option(BUILD_SHARED_LIBS   "Build the chaos as shared libs"   ON)
# Build docs, tests and apps
option(CHAOS_BUILD_DOCS    "Build chaos docs"     ${CHAOS_TOPLEVEL_PROJECT})
option(CHAOS_BUILD_TESTS   "Build chaos tests"    ${CHAOS_TOPLEVEL_PROJECT})
option(CHAOS_BUILD_APPS    "Build chaos apps"     ${CHAOS_TOPLEVEL_PROJECT})
option(CHAOS_BUILD_COVERAGE "Build chaos coverage" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  option(CHAOS_BUILD_UNIT_TEST "Build chaos unit test" ${CHAOS_BUILD_TESTS})
else ()
  option(CHAOS_BUILD_UNIT_TEST "Build chaos unit test" OFF)
endif ()

if (WIN32)
  if (BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  endif ()
endif ()

# add some basic cmake functions
include(utility)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CHAOS_TOPLEVEL_PROJECT)
  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Docs only available if this is the main app
  if(CHAOS_BUILD_DOCS)
    add_subdirectory(docs)
  endif(CHAOS_BUILD_DOCS)
endif()

if(CHAOS_BUILD_COVERAGE)
  message(STATUS "Enabling coverage build")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
endif()

set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fdefault-real-8")

# set output binary/library output dir.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

# check external libs.
find_package(OpenMP REQUIRED)
include(${PROJECT_SOURCE_DIR}/deps/deps.cmake)

# create symbolic links.
add_symlink(${PROJECT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)

# core modules.
add_subdirectory(modules)

# build apps if this is the main app
if (CHAOS_BUILD_APPS)
  add_subdirectory(apps)
endif(CHAOS_BUILD_APPS)

# Testing only available if this is the main app
if (CHAOS_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(CHAOS_BUILD_TESTS)

if (CHAOS_USE_CLANGFORMAT)
  include(clangformat)
  code_format(
    modules/*.cc modules/*.h
    apps/*.cc apps/*.h
    tests/*.cc tests/*.h
    )
endif(CHAOS_USE_CLANGFORMAT)

if (CHAOS_USE_CLANGTIDY)
  include(clangtidy)
  code_tidy(
    modules/*.cc modules/*.h
    apps/*.cc apps/*.h
    tests/*.cc tests/*.h
    )
endif(CHAOS_USE_CLANGTIDY)
