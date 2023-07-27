# Ductfan control

- Random project to control a ductfan with an ESP32 via PWM
- Custom C++ eventing classes to pass messages locally


## Setup

- ESP32
- Buttons
- Ductfan (0-10v)
- PWM to 0-10v board


## CMAKE

ESP-IDF tools
- pull project
- install compiler via setup
- set paths

```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -H.
cmake -Bbuild -H.
cmake --build build --parallel 23
cmake --build build --target test

-DCMAKE_TOOLCHAIN_FILE=/home/simon/Projekte/ductfan-control/build/_deps/esp-src/tools/cmake/toolchain-esp32.cmake -DTARGET=esp32

```

Using custom CMake project not possible with espressif due to bug when importing espressif cmake
- https://github.com/espressif/esp-idf/issues/7483
- https://github.com/espressif/esp-idf/issues/7482

---> easier to use espressif buildsystem and include library as component

## Eventing



TODO

try:
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-esp-idf-in-custom-cmake-projects
and add target for ESP

- add ESP specific unit tests (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/unit-tests.html)

- use singleton pattern for UUID generator and Logger
    - logger module will create global logging object which can be configured, e.g. by using differnt loggers
    - same for UUID generator

- Dont forget to fix error handling (ESP_ERROR_CHECK flood is for testing only)
