#ifndef DUCTSENSE_H
#define DUCTSENSE_H

#include <memory>

#include "DevCom.h"

#include "iot_button.h"

namespace ductfan {

class StatefullButton : public devcom::BaseSensor {

private:
  std::unique_ptr<button_handle_t> m_button;

public:
  StatefullButton(std::unique_ptr<button_handle_t> button_handle);
  int get_current_value() { return 0; };
};

} // namespace ductfan

#endif
