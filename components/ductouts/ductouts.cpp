#include "ductouts.hpp"

namespace ductfan {
// freq needs to be configured globaly by timer
Esp32PwmHighSpeed::Esp32PwmHighSpeed(int pin, int channel){
    // Prepare and then apply the LEDC PWM timer configuration

    // ledc_timer_config_t ledc_timer = {
    //     .speed_mode       = LEDC_LOW_SPEED_MODE,
    //     .timer_num        = LEDC_TIMER,
    //     .duty_resolution  = LEDC_DUTY_RES,
    //     .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5
    // kHz
    //     .clk_cfg          = LEDC_AUTO_CLK
    // };
    // ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // // Prepare and then apply the LEDC PWM channel configuration
    // ledc_channel_config_t ledc_channel = {
    //     .speed_mode     = LEDC_MODE,
    //     .channel        = LEDC_CHANNEL,
    //     .timer_sel      = LEDC_TIMER,
    //     .intr_type      = LEDC_INTR_DISABLE,
    //     .gpio_num       = LEDC_OUTPUT_IO,
    //     .duty           = 0, // Set duty to 0%
    //     .hpoint         = 0
    // };
};

void Esp32PwmHighSpeed::set_value(int value){};

} // namespace ductfan
