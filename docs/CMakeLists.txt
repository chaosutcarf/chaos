# Require dot, treat the other components as optional
cmake_policy(SET CMP0054 NEW)
find_package(
  Doxygen
  REQUIRED dot
  OPTIONAL_COMPONENTS mscgen dia)

option(BUILD_DOCUMENTATION
  "Create and install the HTML based API documentation (requires Doxygen)"
  ${DOXYGEN_FOUND})

if (BUILD_DOCUMENTATION)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  message(STATUS "DOXYGEN_VERSION     : ${DOXYGEN_VERSION}")

  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_MAN  YES)
  set(DOXYGEN_USE_MATHJAX YES)
  list(APPEND DOXYGEN_EXCLUDE_PATTERNS "*/3rd/*" "*/build*/*" "*/tests/*" "*/cmake/*")


  doxygen_add_docs(
    docs
    ${PROJECT_SOURCE_DIR}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generate man pages")

  install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION share/doc)

  add_symlink(
    ${CMAKE_BINARY_DIR}/docs/html/index.html
    ${CMAKE_BINARY_DIR}/docs/index.html)
endif()
