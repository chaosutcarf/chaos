# dependencies libraries.
option(CHAOS_BUILD_WITH_GUI "Build chaos with gui" ON)
option(CHAOS_BUILD_WITH_PARDISO "Build chaos with pardiso" OFF)
option(CHAOS_BUILD_WITH_SUITESPARSE "Build chaos with suitesparse" ON)
option(CHAOS_BUILD_WITH_JSON "Build chaos with nlohmann_json" ON)
option(CHAOS_BUILD_WITH_NANOFLANN "Build chaos with nanoflann" ON)
option(CHAOS_USE_CLANGTIDY "Use clang tidy" ON)
option(CHAOS_USE_CLANGFORMAT "Use clang format" ON)
option(CHAOS_USE_PYTHON_BINDINGS "Use python bindings" ON)

#=====================================================================================
require_git_package(spdlog "ssh://git@ryon.ren:10022/mirrors/spdlog.git"   "v1.9.2"
  CMAKE_ARGS "-DSPDLOG_BUILD_EXAMPLE=OFF"
  VERSION "1.9.2")
require_git_package(CLI11 "ssh://git@ryon.ren:10022/mirrors/CLI11.git" "v2.2.0"
  CMAKE_ARGS "-DCLI11_BUILD_EXAMPLES=OFF"
  CMAKE_ARGS "-DCLI11_BUILD_TESTS=OFF"
  CMAKE_ARGS "-DCLI11_BUILD_DOCS=OFF"
  VERSION "2.2.0"
  )
require_git_package(Eigen3   "ssh://git@ryon.ren:10022/mirrors/eigen3.git"   "3.4.0"
  CMAKE_ARGS "-DEIGEN_BUILD_DOC=OFF"
  CMAKE_ARGS "-DBUILD_TESTING=OFF"
  VERSION "3.4.0"
)
require_git_package(Spectra "git@github.com:yixuan/spectra.git" "v1.0.0"
  VERSION "1.0.0"
  )
require_git_package(igl "ssh://git@ryon.ren:10022/mirrors/libigl.git"   "v2.3.0"
  SOURCE_DIR "${PROJECT_SOURCE_DIR}/3rd/libigl"
  DO_NOT_BUILD
  )
require_git_package(autodiff "ssh://git@ryon.ren:10022/mirrors/autodiff.git" "v0.6.8"
  CMAKE_ARGS "-DAUTODIFF_BUILD_TESTS=OFF"
  CMAKE_ARGS "-DAUTODIFF_BUILD_PYTHON=OFF"
  CMAKE_ARGS "-DAUTODIFF_BUILD_EXAMPLES=OFF"
  CMAKE_ARGS "-DAUTODIFF_BUILD_DOCS=OFF"
  VERSION "0.6.8"
  PATCH_COMMAND "git restore . && git apply ${PROJECT_SOURCE_DIR}/cmake/autodiff.patch && echo patch applied"
)

# optimizer.
require_git_package(alglib "git@github.com:LamKamhang/alglib-cmake-wrapper.git" "origin/master")
# osqp
require_git_package(osqp "git@github.com:osqp/osqp.git" "1a2f2d32")
require_git_package(OsqpEigen "git@github.com:robotology/osqp-eigen.git" "v0.7.0"
  VERSION "0.7.0"
)

# for nanoflann
if (CHAOS_BUILD_WITH_NANOFLANN)
  require_git_package(nanoflann "git@github.com:jlblancoc/nanoflann.git" "v1.4.2"
    CMAKE_ARGS "-DNANOFLANN_BUILD_EXAMPLES=OFF"
    CMAKE_ARGS "-DNANOFLANN_BUILD_TESTS=OFF"
    VERSION "1.4.2"
    )
endif(CHAOS_BUILD_WITH_NANOFLANN)
# for json
if (CHAOS_BUILD_WITH_JSON)
  require_git_package(nlohmann_json "git@github.com:nlohmann/json.git" "v3.10.5"
    CMAKE_ARGS "-DJSON_BuildTests=OFF"
    VERSION "3.10.5"
    )
endif(CHAOS_BUILD_WITH_JSON)

# for gui.
if (CHAOS_BUILD_WITH_GUI)
  require_git_package(glfw3 "ssh://git@ryon.ren:10022/mirrors/glfw.git" "3.3.4"
    CMAKE_ARGS "-DGLFW_BUILD_EXAMPLES=OFF"
    CMAKE_ARGS "-DGLFW_BUILD_TESTS=OFF"
    CMAKE_ARGS "-DGLFW_BUILD_DOCS=OFF"
    VERSION "3.3.4"
    )
  require_git_package(glad "git@github.com:LamKamhang/glad.git" "6ee1551" DO_NOT_BUILD)
  require_git_package(imgui "ssh://git@ryon.ren:10022/mirrors/imgui.git" "v1.84.2"
    SOURCE_DIR "${PROJECT_SOURCE_DIR}/3rd/imgui_wrapper/imgui"
    DO_NOT_BUILD
    )
  if (NOT EXISTS "${IGL_DIR}/external/libigl-imgui")
    add_git_3rd_project(libigl-imgui "ssh://git@ryon.ren:10022/mirrors/libigl-imgui.git" "7e1053e7"
      SOURCE_DIR "${IGL_DIR}/external/libigl-imgui"
      DO_NOT_BUILD
      )
  endif()
endif(CHAOS_BUILD_WITH_GUI)

# linear solver.
if (CHAOS_BUILD_WITH_PARDISO)
  find_package(pardiso REQUIRED)
endif(CHAOS_BUILD_WITH_PARDISO)

if (CHAOS_BUILD_WITH_SUITESPARSE)
  require_git_package(SuiteSparse "ssh://git@ryon.ren:10022/JinkengLIN/suitesparse-wrapper.git" "9e10f806d9"
    CMAKE_ARGS "-DSHARED=ON"
    VERSION "5.9.0"
    )
endif(CHAOS_BUILD_WITH_SUITESPARSE)

# python bindings.
if (CHAOS_USE_PYTHON_BINDINGS)
  require_git_package(pybind11 "git@github.com:pybind/pybind11.git" "v2.8.1"
    CMAKE_ARGS "-DPYBIND11_TEST=OFF"
    VERSION "2.8.1"
    )
  add_subdirectory(pychaos)
endif(CHAOS_USE_PYTHON_BINDINGS)

if (CHAOS_BUILD_UNIT_TEST)
  require_git_package(Catch2 "ssh://git@ryon.ren:10022/mirrors/Catch2.git" "v2.13.7"
    CMAKE_ARGS "-DCATCH_BUILD_TESTING=OFF"
    CMAKE_ARGS "-DCATCH_INSTALL_DOCS=OFF"
    VERSION "2.13.7"
    )
endif(CHAOS_BUILD_UNIT_TEST)
