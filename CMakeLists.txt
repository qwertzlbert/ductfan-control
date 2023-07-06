cmake_minimum_required(VERSION 3.14)
project(ductfan-control LANGUAGES CXX VERSION 0.0.1)

# disable warnings for now to prevent getting insane
set(CMAKE_CXX_FLAGS "-std=c++20")
add_link_options("-fuse-ld=mold")
# set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra")

## include gtest

include(FetchContent)
fetchcontent_declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)

## include catch2

fetchcontent_declare(
    catch2test
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10
)

fetchcontent_getproperties(catch2test)
if(NOT catch2test_POPULATED)
    fetchcontent_populate(catch2test)
endif()

add_library(ThirdParty.Catch2 INTERFACE)
target_include_directories(
    ThirdParty.Catch2
    INTERFACE "${catch2test_SOURCE_DIR}/single_include"
)
target_compile_features(ThirdParty.Catch2 INTERFACE cxx_std_14)

function(add_catch2test_with_main target cpp_file)
    add_executable(${target} "${cpp_file}")
    target_link_libraries(${target} PUBLIC ThirdParty.Catch2)
    target_compile_definitions(${target} PUBLIC "CATCH_CONFIG_MAIN")
endfunction()

add_compile_definitions(EPOXY_CORE_ESP8266)

## add ezButton lib
fetchcontent_declare(
    ezButton
    GIT_REPOSITORY https://github.com/ArduinoGetStarted/button.git
    GIT_TAG v1.0.4
)

fetchcontent_makeavailable(ezButton)

## add arduino mock
fetchcontent_declare(
    Arduino
    GIT_REPOSITORY https://github.com/bxparks/EpoxyDuino.git
    GIT_TAG v1.5.0
)

fetchcontent_makeavailable(Arduino)

add_library(Arduino SHARED "${arduino_SOURCE_DIR}/cores/epoxy/Arduino.cpp")
add_library(ezButton SHARED "${ezbutton_SOURCE_DIR}/src/ezButton.cpp")
include_directories(Arduino PUBLIC "${arduino_SOURCE_DIR}/cores/epoxy")
include_directories(ezButton PUBLIC "${ezbutton_SOURCE_DIR}/src")

install(TARGETS Arduino DESTINATION lib)
install(TARGETS ezButton DESTINATION lib)

# add esp-idf sources
fetchcontent_declare(
    esp
    GIT_REPOSITORY https://github.com/espressif/esp-idf.git
    GIT_TAG v5.1
)

fetchcontent_populate(esp)

include_directories(
    esp
    PUBLIC
    "${esp_SOURCE_DIR}/components/driver/ledc/include"
    "${esp_SOURCE_DIR}/components/driver/gpio/include"
    "${esp_SOURCE_DIR}/components/esp_common/include"
    "${esp_SOURCE_DIR}/components/esp_hw_support/include"
    "${esp_SOURCE_DIR}/components/hal/include"
    "${esp_SOURCE_DIR}/components/soc/esp32/include"
    "${esp_SOURCE_DIR}/components/esp_rom/include"
)

include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE test_SOURCES "tests/unit/*.cpp")
file(GLOB_RECURSE lib_SOURCES "src/**/*.cpp")

add_library(eventQueues SHARED ${lib_SOURCES})
install(TARGETS eventQueues DESTINATION lib)

add_library(eventHandlers SHARED ${lib_SOURCES})
install(TARGETS eventHandlers DESTINATION lib)

add_library(handlerQueues SHARED ${lib_SOURCES})
install(TARGETS handlerQueues DESTINATION lib)

add_library(eventMessages SHARED ${lib_SOURCES})
install(TARGETS eventMessages DESTINATION lib)

add_library(eventManager SHARED ${lib_SOURCES})
install(TARGETS eventManager DESTINATION lib)

add_library(Devices SHARED ${lib_SOURCES})
install(TARGETS Devices DESTINATION lib)

add_library(sensors SHARED ${lib_SOURCES})
install(TARGETS sensors DESTINATION lib)

add_library(outputs SHARED ${lib_SOURCES})
install(TARGETS outputs DESTINATION lib)

find_package(Catch2 REQUIRED)
add_executable(tests ${test_SOURCES})
target_link_libraries(
    tests
    ezButton
    eventQueues
    eventHandlers
    handlerQueues
    eventMessages
    eventManager
    Devices
    sensors
    outputs
    uuid
    gmock_main
    Arduino
)

include(CTest)
include(Catch)
catch_discover_tests(tests REPORTER console)
