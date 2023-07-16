idf_component_register(SRCS ""
    INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/libs/devcom"
)
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/" build)

target_link_libraries(outputs PUBLIC ductouts)
