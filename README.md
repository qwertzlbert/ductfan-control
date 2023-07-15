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
cmake --build build cmake --build build --parallel 23
cmake --build build --target test

-DCMAKE_TOOLCHAIN_FILE=/home/simon/Projekte/ductfan-control/build/_deps/esp-src/tools/cmake/toolchain-esp32.cmake -DTARGET=esp32

  PATH="${PATH}:/home/simon/Downloads/xtensa-esp32-elf/bin/"

PATH="${PATH}:~/.espressif/tools/xtensa-esp32-elf/esp-2022r1-11.2.0/xtensa-esp32-elf/bin/" IDF_PATH=/home/simon/Projekte/ductfan-control/build/_deps/esp-src cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -H. -DCMAKE_TOOLCHAIN_FILE=/home/simon/Projekte/ductfan-control/build-bak/_deps/esp-src/tools/cmake/toolchain-esp32.cmake -DTARGET=esp32

PATH="${PATH}:~/.espressif/tools/xtensa-esp32-elf/esp-2022r1-11.2.0/xtensa-esp32-elf/bin/" IDF_PATH=/home/simon/Projekte/ductfan-control/build/_deps/esp-src cmake cmake --build build --parallel 23 -DCMAKE_TOOLCHAIN_FILE=/home/simon/Projekte/ductfan-control/build-bak/_deps/esp-src/tools/cmake/toolchain-esp32.cmake -DTARGET=esp32
```

## Eventing



TODO

try:
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-esp-idf-in-custom-cmake-projects
and add target for ESP

- add ESP specific unit tests (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/unit-tests.html)
