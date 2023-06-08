#include "Devices.hpp"

namespace ductfan_control {

StatefullButton::StatefullButton(std::unique_ptr<BaseSensor> sensor) {

  m_sensor = std::move(sensor);
}

int StatefullButton::get_value() {

  int value = m_sensor->get_current_value();

  if (value > 0) {
    value = 1;
  } else {
    value = 0;
  }

  return value;
}

} // namespace ductfan_control
