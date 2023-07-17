#ifndef DUCTOUTS_H
#define DUCTOUTS_H

#include "DevCom.h"

#include "driver/ledc.h"
#include "esp_err.h"
#include <stdio.h>

namespace ductfan {
// output for ESP32 using hardware controlled
// PWM without fading (fading requires semaphores)
class Esp32PwmHighSpeed : public devcom::BaseOutput {
private:
  ledc_mode_t m_speed_mode;
  ledc_channel_t m_channel;
  uint32_t m_current_speed;
  uint32_t m_duty_resolution_factor;

public:
  Esp32PwmHighSpeed(ledc_mode_t speed_mode, ledc_channel_t channel,
                    uint32_t duty_res);
  void set_value(int value);
};

} // namespace ductfan

#endif
