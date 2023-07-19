#include "application.hpp"

// just a wrapper function to wrap all c++ only classes and
// allow include into main
extern "C" void run_application(void) {
  // eventmanager
  devcom::SimpleEventManager eventing;

  // init buttons
  button_config_t gpio_btn_cfg = {
      .type = BUTTON_TYPE_GPIO,
      .long_press_time = 0,
      .short_press_time = 0,
      .gpio_button_config =
          {
              .gpio_num = 0,
              .active_level = 0,
          },
  };

  // init buttons
  std::unique_ptr<devcom::BaseSensor> button_1_sense =
      std::make_unique<ductfan::StatefullButton>(gpio_btn_cfg);
  std::shared_ptr<devcom::BaseDevice> button_1 =
      std::make_shared<devcom::Button>(std::move(button_1_sense));

  std::unique_ptr<devcom::BaseHandler> button_1_handler =
      std::make_unique<devcom::SimpleDeviceHandler>(button_1, "test");
  eventing.addHandler(std::move(button_1_handler), 1);
}
