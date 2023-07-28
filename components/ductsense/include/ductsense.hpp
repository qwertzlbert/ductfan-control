#ifndef DUCTSENSE_H
#define DUCTSENSE_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <memory>

#include "DevCom.h"

#include "driver/pulse_cnt.h"
#include "iot_button.h"

namespace ductfan {

class StatefullButton : public devcom::BaseSensor {

private:
  button_handle_t m_button;
  int m_state;
  button_event_t m_last_event;

public:
  StatefullButton(button_config_t &button_config);
  int get_current_value();
};

// need to add factor for signal per turn (some create 1 others 2, etc.)
// also need to add signal factor as some fans will put out
// rpm = signal/60hz ---> signal/s == rpm
// others will only create 1 signal per turn so that
// signal/s x 60 = rpm
class FanTachoSensor : public devcom::BaseSensor {

private:
  int m_speed;
  int m_max_speed;
  int m_pin_number;
  pcnt_unit_handle_t m_pcnt_unit;
  pcnt_channel_handle_t m_pcnt_chan;
  // task handle for class, required to prevent creation of additional tasks
  TaskHandle_t m_taskHandle;
  void update_speed_task();
  static void start_update_speed_task_wrapper(void *_this);

public:
  FanTachoSensor(int gpio_pin, int max_speed);
  int get_current_value();
};

} // namespace ductfan

#endif
