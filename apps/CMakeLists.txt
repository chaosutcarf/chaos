set(chaos_apps
  )

foreach(app ${chaos_apps})
  add_subdirectory(${app})
endforeach(app)

if (CHAOS_BUILD_WITH_GUI)
endif(CHAOS_BUILD_WITH_GUI)
