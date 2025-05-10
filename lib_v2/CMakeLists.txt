project(lib_v2)
add_library(lib_v2_static STATIC main_v2.cpp)
set_target_properties(lib_v2_static PROPERTIES OUTPUT_NAME static_v2)

target_include_directories(lib_v2_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

####### Way2 to hide symbols from static lib
if(WITH_VISIBILITY_HIDDEN)
  message(STATUS "Adding -fvisibility=hidden flags to lib_v2 static")
  target_compile_options(lib_v2_static PRIVATE
    -fvisibility=hidden
    -fvisibility-inlines-hidden
  )
else()
  message(STATUS "Skipping visibility flags for lib_v2 static")
endif()