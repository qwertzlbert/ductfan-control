#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <inttypes.h>
#include <stdio.h>

#include "application.hpp"

extern "C" void app_main(void) {

  // initialize hardware

  // initialize eventingmanager
  // SimpleEventManager eventManager;
  run_application();
  printf("Restarting now.\n");
}
