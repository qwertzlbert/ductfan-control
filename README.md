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

```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -H.
cmake -Bbuild -H.
cmake --build build cmake --build build --parallel 23
cmake --build build --target test

```

## Eventing
