#ifndef DEVICES_H
#define DEVICES_H

#include <memory>
#include <string>

#include "outputs/outputs.hpp"
#include "sensors/sensors.hpp"

namespace ductfan_control {

class BaseDevice {
public:
  virtual int get_value() = 0;
  virtual void set_value(int value) = 0;
};

class StatefullButton : public BaseDevice {
private:
  std::unique_ptr<BaseSensor> m_sensor;
  const std::string unit = "bool";

public:
  StatefullButton(std::unique_ptr<BaseSensor> sensor);
  int get_value();
  void set_value(int value){};
};

} // namespace ductfan_control

#endif
