set(devcom_SRC
    "${CMAKE_SOURCE_DIR}/libs/devcom/devices/devices.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/eventing/eventHandlers/eventHandlers.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/eventing/eventManager/eventManager.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/eventing/eventMessages/eventMessages.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/eventing/eventQueues/eventQueues.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/eventing/handlerQueues/handlerQueues.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/outputs/outputs.cpp"
    "${CMAKE_SOURCE_DIR}/libs/devcom/sensors/sensors.cpp"
)

# Please read the warning regarding GLOB_RECURSE
# at https://cmake.org/cmake/help/latest/command/file.html#filesystem
# file(GLOB_RECURSE devcom_SRC "${CMAKE_SOURCE_DIR}/libs/devcom/**/*.cpp")

idf_component_register(SRCS "${devcom_SRC}"
    INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/libs/devcom"
)
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/" build)

target_link_libraries(outputs PUBLIC ductouts)
target_link_libraries(sensors PUBLIC ductsense)
target_link_libraries(eventManager PUBLIC application)
