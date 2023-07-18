#include "ductsense.hpp"

namespace ductfan {

StatefullButton::StatefullButton(
    std::unique_ptr<button_handle_t> button_handle) {
  m_button = std::move(button_handle);
  m_state = 0;
}

int StatefullButton::get_current_value() {

  button_event_t b_event = iot_button_get_event(&m_button);

  bool change_event = false;

  // BUTTON_SINGLE_CLICK will change state
  // BUTTON_DOUBLE_CLICK will do nothing
  // BUTTON_PRESS_REPEAT needs to be counted to check if internal state needs to
  // change
  switch (b_event) {
  case BUTTON_SINGLE_CLICK:
    change_event = true;
    break;

  case BUTTON_PRESS_REPEAT:
    uint8_t repeat_count = iot_button_get_repeat(&m_button);
    if (repeat_count % 2 == 1) {
      change_event = true;
    }
    break;
  }

  // will cycle state between 0 and 1
  if (change_event) {
    m_state = (m_state + 1) % 2;
  }

  return m_state;
}

} // namespace ductfan
