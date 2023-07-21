#include "application.hpp"

// just a wrapper function to wrap all c++ only classes and
// allow include into main
void run_application(void) {
  // eventmanager
  devcom::SimpleEventManager eventing;

  // should be moved to logging mechanism
  printf("PWM INIT\n");
  // pwm init
  ledc_mode_t speed_mode = LEDC_LOW_SPEED_MODE;
  ledc_timer_t timer = LEDC_TIMER_0;
  ledc_timer_bit_t timer_resolution = LEDC_TIMER_12_BIT;
  ledc_channel_t channel_fan_1 = LEDC_CHANNEL_0;
  int gpio_fan_1 = 16;

  // timer config
  // Prepare and then apply the LEDC PWM timer configuration
  ledc_timer_config_t ledc_timer = {.speed_mode = speed_mode,
                                    .duty_resolution = timer_resolution,
                                    .timer_num = timer,
                                    .freq_hz =
                                        2000, // Set output frequency at 2 kHz
                                    .clk_cfg = LEDC_AUTO_CLK};
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // pwm channel config
  // Prepare and then apply the LEDC PWM channel configuration
  // creates warning 'ledc_channel_config_t::flags'
  ledc_channel_config_t ledc_channel = {.gpio_num = gpio_fan_1,
                                        .speed_mode = speed_mode,
                                        .channel = channel_fan_1,
                                        .intr_type = LEDC_INTR_DISABLE,
                                        .timer_sel = timer,
                                        .duty = 0, // Set duty to 0%
                                        .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

  // button config
  button_config_t gpio_btn_cfg = {
      .type = BUTTON_TYPE_GPIO,
      .long_press_time = 0,
      .short_press_time = 0,
      .gpio_button_config =
          {
              .gpio_num = 21,
              .active_level = 0,
          },
  };

  // init Fan
  std::unique_ptr<devcom::BaseOutput> fan_1_out =
      std::make_unique<ductfan::Esp32PwmHighSpeed>(speed_mode, channel_fan_1,
                                                   timer_resolution);
  std::unique_ptr<devcom::BaseSensor> fan_1_in =
      std::make_unique<devcom::DummySensor>();
  std::shared_ptr<devcom::BaseDevice> fan_1 =
      std::make_shared<devcom::Fan>(std::move(fan_1_in), std::move(fan_1_out));

  // init buttons
  std::unique_ptr<devcom::BaseSensor> button_1_sense =
      std::make_unique<ductfan::StatefullButton>(gpio_btn_cfg);
  std::shared_ptr<devcom::BaseDevice> button_1 =
      std::make_shared<devcom::Button>(std::move(button_1_sense));

  // init messages
  std::vector<std::vector<std::string>> button_1_on_message = {
      {"speed", "100", "int"}};
  std::vector<std::vector<std::string>> button_1_off_message = {
      {"speed", "10", "int"}};

  // setup handlers
  std::unique_ptr<devcom::BaseHandler> fan_1_handler =
      std::make_unique<devcom::SimpleDeviceHandler>(fan_1, "speed");
  eventing.addHandler(std::move(fan_1_handler), 1);

  int button_1_before = 0;
  int button_1_state = 0;

  // should be moved to logging mechanism
  printf("Start main loop\n");
  while (1) {

    button_1_state = button_1->get_value();
    if (button_1_state != button_1_before) {
      // queue message
      if (button_1_state == 0) {
        std::unique_ptr<devcom::BaseMessage> button_1_off =
            std::make_unique<devcom::SimpleMessage>(button_1_off_message);

        eventing.addEvent(std::move(button_1_off), 1);
        // should be moved to logging mechanism
        printf("turn off \n");
      } else {
        std::unique_ptr<devcom::BaseMessage> button_1_on =
            std::make_unique<devcom::SimpleMessage>(button_1_on_message);
        eventing.addEvent(std::move(button_1_on), 1);
        // should be moved to logging mechanism
        printf("turn on \n");
      }
      button_1_before = button_1_state;
    }

    eventing.processEvent();

    // delay required for RTOS (?)
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
