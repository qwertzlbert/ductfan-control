cmake_minimum_required(VERSION 3.16)
project(ductfan-control LANGUAGES CXX VERSION 0.0.1)

# disable warnings for now to prevent getting insane
set(CMAKE_CXX_FLAGS "-std=c++20")
add_link_options("-fuse-ld=mold")
# set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra")

include_directories("${PROJECT_SOURCE_DIR}/src/devcom")
add_subdirectory(src/devcom)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/unit)
