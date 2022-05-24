add_library(chaos_maxima INTERFACE)

set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fdefault-real-8")

set(maxima_modules
  hyperelastic_strain_energy
  )

foreach(module ${maxima_modules})
  string(CONCAT module_lib "chaos_maxima_" ${module})
  add_mac2f90(${module_lib} ${module})
  message(STATUS "link library: ${module_lib}")
  target_link_libraries(chaos_maxima INTERFACE ${module_lib})
  add_library(chaos::maxima::${module} ALIAS ${module_lib})
endforeach(module)
