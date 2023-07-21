#include "ductsense.hpp"

namespace ductfan {

StatefullButton::StatefullButton(button_config_t &button_config_t) {
  m_button = iot_button_create(&button_config_t);
  m_state = 0;
  m_last_event = BUTTON_NONE_PRESS;
}

int StatefullButton::get_current_value() {

  button_event_t b_event = iot_button_get_event(m_button);

  bool change_event = false;

  // BUTTON_SINGLE_CLICK will change state
  // BUTTON_DOUBLE_CLICK will do nothing
  // BUTTON_PRESS_REPEAT needs to be counted to check if internal state needs to
  // change
  switch (b_event) {
  case BUTTON_PRESS_DOWN:
    if (m_last_event != b_event) {
      m_last_event = b_event;
      change_event = true;
      // should be moved to logging mechanism
      printf("PRESSED DOWN\n");
    }
    break;

  case BUTTON_PRESS_UP:
    if (m_last_event != b_event) {
      m_last_event = b_event;
      // should be moved to logging mechanism
      printf("PRESSED UP\n");
    }
    break;

  default:
    break;
  }

  // will cycle state between 0 and 1
  if (change_event) {
    m_state = (m_state + 1) % 2;
  }

  return m_state;
}

} // namespace ductfan
