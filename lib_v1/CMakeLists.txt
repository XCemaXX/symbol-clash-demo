project(lib_v1)

add_library(lib_v1_shared SHARED main_v1.cpp)
set_target_properties(lib_v1_shared PROPERTIES OUTPUT_NAME shared_v1)

target_include_directories(lib_v1_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})