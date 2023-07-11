#include "sensors.hpp"

namespace ductfan_control {

DummySensor::DummySensor(){};

// StatefullEzButton::StatefullEzButton(int pin) {
//   m_button = std::make_unique<ezButton>(pin);
//   m_button->setDebounceTime(50);
// };

// int StatefullEzButton::get_current_value() {
//   m_button->loop();
//   return m_button->getState();
// };

} // namespace ductfan_control
