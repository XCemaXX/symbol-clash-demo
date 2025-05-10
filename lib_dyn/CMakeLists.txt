project(lib_dyn)
add_library(lib_dyn SHARED lib_dyn.cpp)
set_target_properties(lib_dyn PROPERTIES OUTPUT_NAME dynamic)

target_include_directories(lib_dyn PUBLIC
    ${CMAKE_SOURCE_DIR}/lib_v1
)

target_link_libraries(lib_dyn PRIVATE lib_v1_shared)