#include "ductouts.hpp"

namespace ductfan {
// freq needs to be configured globaly by timer and channel config
Esp32PwmHighSpeed::Esp32PwmHighSpeed(ledc_mode_t speed_mode,
                                     ledc_channel_t channel,
                                     uint32_t duty_res) {

  m_speed_mode = speed_mode;
  m_channel = channel;
  m_duty_resolution_factor = pow(2, duty_res) - 1;
  m_current_speed = 0;

  // initialize value to 0
  set_value(0);
}

void Esp32PwmHighSpeed::set_value(int value) {

  u_int32_t freq = ((uint32_t)value * m_duty_resolution_factor / (uint32_t)100);

  printf("set percent to: %d \n", value);
  printf("set freq to: %lu \n", freq);
  printf("resolution is: %lu \n", m_duty_resolution_factor);

  // ledc_set_duty_and_update calls fade internally --> disable for now
  // esp_err_t error = ledc_set_duty_and_update(m_speed_mode, m_channel, freq,
  // 0);
  esp_err_t error = ledc_set_duty(m_speed_mode, m_channel, freq);
  esp_err_t update_error = ledc_update_duty(m_speed_mode, m_channel);

  if (error != ESP_OK or update_error != ESP_OK) {
    // reset channel by setting it to 0
    // ledc_set_duty_and_update calls fade internally --> disable for now
    // ESP_ERROR_CHECK(ledc_set_duty_and_update(m_speed_mode, m_channel, 0, 0));
    ESP_ERROR_CHECK(ledc_set_duty(m_speed_mode, m_channel, 0));
    ESP_ERROR_CHECK(ledc_update_duty(m_speed_mode, m_channel));
  }
}
} // namespace ductfan
