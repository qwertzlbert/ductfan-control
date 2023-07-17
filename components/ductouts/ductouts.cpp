#include "ductouts.hpp"

namespace ductfan {
// freq needs to be configured globaly by timer and channel config
Esp32PwmHighSpeed::Esp32PwmHighSpeed(ledc_mode_t speed_mode,
                                     ledc_channel_t channel,
                                     uint32_t duty_res) {

  m_speed_mode = speed_mode;
  m_channel = channel;
  m_duty_resolution_factor = (2 ^ duty_res) - 1;
  m_current_speed = 0;

  // initialize value to 0
  set_value(0);
}

void Esp32PwmHighSpeed::set_value(int value) {

  int freq = (value / 100) * m_duty_resolution_factor;

  esp_err_t error = ledc_set_duty_and_update(m_speed_mode, m_channel, freq, 0);

  if (error != ESP_OK) {
    // reset channel by setting it to 0
    ESP_ERROR_CHECK(ledc_set_duty_and_update(m_speed_mode, m_channel, 0, 0));
  }
}
} // namespace ductfan
