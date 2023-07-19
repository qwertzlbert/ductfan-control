#ifndef DUCTSENSE_H
#define DUCTSENSE_H

#include <memory>

#include "DevCom.h"

#include "iot_button.h"

namespace ductfan {

class StatefullButton : public devcom::BaseSensor {

private:
  button_handle_t m_button;
  int m_state;

public:
  StatefullButton(button_config_t &button_config);
  int get_current_value();
};

} // namespace ductfan

#endif
