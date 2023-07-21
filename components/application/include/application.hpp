#ifndef APPLICATION_H
#define APPLICATION_H

#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <memory>

#include "DevCom.h"
#include "ductouts.hpp"
#include "ductsense.hpp"

// #ifdef __cplusplus
// extern "C" {
// #endif

void run_application();

// #ifdef __cplusplus
// }
// #endif

#endif
