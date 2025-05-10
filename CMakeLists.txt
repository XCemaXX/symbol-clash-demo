cmake_minimum_required(VERSION 3.10)
project(MultiLibExample)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib_v1)
add_subdirectory(lib_v2)
add_subdirectory(lib_dyn)
add_subdirectory(main)

option(WITH_VISIBILITY_HIDDEN "Compile lib_v2 with -fvisibility=hidden" OFF)
option(WITH_EXCLUDE_LIB2 "Compile main_app with -Wl,--exclude-libs,libstatic_v2.a" OFF)
option(WITH_VERSION_SCRIPT "Compile main_app with -Wl,--version-script" OFF)