set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
if (CHAOS_BUILD_UNIT_TEST)
  include(CTest)
  include(Catch)

  file(GLOB_RECURSE test_units "unit_test/*.cc")
  add_unit(unit_test SRCS ${test_units} LIBS Catch2::Catch2 chaos)
  catch_discover_tests(unit_test)
endif(CHAOS_BUILD_UNIT_TEST)
