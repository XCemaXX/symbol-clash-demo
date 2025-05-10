project(main_app)
add_executable(main_app main.cpp)

target_include_directories(main_app PRIVATE
    ${CMAKE_SOURCE_DIR}/lib_v2
    ${CMAKE_SOURCE_DIR}/lib_dyn
)

target_link_libraries(main_app PRIVATE lib_v2_static lib_dyn)

######## Way1 to hide symbols from static lib
if(WITH_EXCLUDE_LIB2)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Adding -Wl,--exclude-libs,libstatic_v2.a flags to main_app")
    target_link_options(main_app PRIVATE 
      #"-Wl,--exclude-libs,ALL" 
      "-Wl,--exclude-libs,libstatic_v2.a"
    )
  else()
    message(STATUS "NOT SUPPORTED: Skipping exclude libs flags for main_app")
  endif()
else()
  message(STATUS "Skipping exclude libs flags for main_app")
endif()

if(WITH_VERSION_SCRIPT)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Adding -Wl,--version-script flag to main_app")
    target_link_options(main_app PRIVATE 
      "-Wl,--version-script=${CMAKE_SOURCE_DIR}/main/main_app.map"
    )
  else()
    message(STATUS "NOT SUPPORTED: Skipping version-script flag for main_app")
  endif()
else()
  message(STATUS "Skipping version-script flag for main_app")
endif()


if(COMMENT_TEMPLATE_STATIC_CALL)
  message(STATUS "Will comment out direct multiply<int> in main_app")
  target_compile_definitions(main_app
    PRIVATE COMMENT_TEMPLATE_STATIC_CALL
  )
else()
  message(STATUS "Direct multiply<int> in main_app is active")
endif()