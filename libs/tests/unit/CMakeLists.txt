include(CTest)
include(FetchContent)

## include gtest

fetchcontent_declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
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

add_executable(tests deviceTests.cpp eventTests.cpp)
target_link_libraries(
    tests
    eventQueues
    eventHandlers
    handlerQueues
    eventMessages
    eventManager
    devices
    sensors
    outputs
    uuid
    gmock_main
)

add_test(NAME tests COMMAND $<TARGET_FILE:tests>)

find_package(Catch2 REQUIRED)
include(Catch)
catch_discover_tests(tests REPORTER console)
