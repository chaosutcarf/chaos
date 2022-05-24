#!/usr/bin/env python3

import os
import sys

PROJ_ROOT=os.path.dirname(os.path.dirname(os.path.realpath(sys.argv[0])))
CMAKE_FILE=os.path.join(PROJ_ROOT, "deps", "deps.cmake")

URLS= {}
URLS["ssh://git@ryon.ren:10022/mirrors/Catch2.git"]="https://github.com/catchorg/Catch2.git"
URLS["ssh://git@ryon.ren:10022/mirrors/spdlog.git"]="https://github.com/gabime/spdlog.git"
URLS["ssh://git@ryon.ren:10022/mirrors/CLI11.git"]="https://github.com/CLIUtils/CLI11.git"
URLS["ssh://git@ryon.ren:10022/mirrors/eigen3.git"]="https://gitlab.com/libeigen/eigen.git"
URLS["ssh://git@ryon.ren:10022/JinkengLIN/suitesparse-wrapper.git"]="https://github.com/LamKamhang/suitesparse-wrapper.git"
URLS["9e10f806d9"]="ba8a9c5"
URLS["ssh://git@ryon.ren:10022/mirrors/autodiff.git"]="https://github.com/autodiff/autodiff.git"
URLS["ssh://git@ryon.ren:10022/mirrors/libigl.git"]="https://github.com/libigl/libigl.git"
URLS["ssh://git@ryon.ren:10022/mirrors/glfw.git"]="https://github.com/glfw/glfw.git"
URLS["ssh://git@ryon.ren:10022/mirrors/imgui.git"]="https://github.com/ocornut/imgui.git"
URLS["ssh://git@ryon.ren:10022/mirrors/libigl-imgui.git"]="https://github.com/libigl/libigl-imgui"

URLS["git@github.com:"]="https://github.com/"

def main():
    print(CMAKE_FILE)
    print(URLS)
    with open(CMAKE_FILE) as f:
        content=f.read()
    for k,v in URLS.items():
        content = content.replace(k, v)
    with open(CMAKE_FILE, 'w') as f:
        f.write(content)

if __name__ == '__main__':
    main()
