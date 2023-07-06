#include "Devices.hpp"

namespace ductfan_control {

Button::Button(std::unique_ptr<BaseSensor> sensor) {

  m_sensor = std::move(sensor);
}

int Button::get_value() {

  int value = m_sensor->get_current_value();

  if (value > 0) {
    value = 1;
  } else {
    value = 0;
  }

  return value;
}

BoolStateInfo::BoolStateInfo(std::unique_ptr<BaseOutput> output) {
  m_output = std::move(output);
  m_state = 0;
}

void BoolStateInfo::set_value(int value) {

  m_output->set_value(value);
  if (value > 0) {
    m_state = 1;
  } else {
    m_state = 0;
  }
}

Fan::Fan(std::unique_ptr<BaseSensor> sensor,
         std::unique_ptr<BaseOutput> output) {
  m_output = std::move(output);
  m_sensor = std::move(sensor);
}

int Fan::get_value() { return m_sensor->get_current_value(); }

// this should include some validation
// to only allow percentage values
void Fan::set_value(int value) {
  int value_perc = 0;

  if (value > 100) {
    value_perc = 100;
  } else if (value > 0 and value < 101) {
    value_perc = value;
  }

  m_output->set_value(value_perc);
}

} // namespace ductfan_control
