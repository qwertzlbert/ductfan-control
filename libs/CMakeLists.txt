cmake_minimum_required(VERSION 3.16)
project(ductfan-control LANGUAGES C CXX VERSION 0.0.1)

message("Build testing is ${BUILD_TESTING}")

# disable warnings for now to prevent getting insane
# set(CMAKE_CXX_FLAGS "-std=c++20")
add_link_options("-fuse-ld=mold")
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra -Wno-unused-parameter")

message("Project directory: ${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/devcom")
add_subdirectory(devcom)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests/unit)
endif()

install(FILES devcom/DevCom.h TYPE INCLUDE COMPONENT devcom)
