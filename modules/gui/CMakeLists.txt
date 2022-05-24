add_library(chaos_gui gui.cc)

get_filename_component(ABS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ ABSOLUTE)

target_include_directories(chaos_gui
  PUBLIC
  ${ABS_INCLUDE_DIR})

set(chaos_gui_modules
  )

foreach(module ${chaos_gui_modules})
  add_subdirectory(${module})
  string(CONCAT gui_lib "chaos_gui_" ${module})
  add_library(chaos::gui::${module} ALIAS ${gui_lib})
  message(STATUS "link library: ${gui_lib}")
  target_link_libraries(chaos_gui PUBLIC ${gui_lib})
endforeach(module)

target_link_libraries(chaos_gui
  PUBLIC
  igl glad glfw imgui
  )

target_precompile_headers(chaos_gui
  PUBLIC
  appBase.h
  menuBase.h
  )
