#pragma once

#include <igl/opengl/glfw/Viewer.h>

namespace chaos::gui {
using Viewer = igl::opengl::glfw::Viewer;

class AppBase {
 public:
  AppBase() {}
  virtual ~AppBase() {}

  virtual int init(int argc, char* argv[]) = 0;
  virtual int mainLoop() = 0;

 protected:
  Viewer viewer;
};

}  // namespace chaos::gui
