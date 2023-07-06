#ifndef DEVICES_H
#define DEVICES_H

#include <memory>
#include <string>

#include "outputs/outputs.hpp"
#include "sensors/sensors.hpp"

namespace ductfan_control {

class BaseDevice {
public:
  virtual ~BaseDevice() = default;
  virtual int get_value() = 0;
  virtual void set_value(int value) = 0;
};

// class which implements a sensor which
// only knows bool on/off states
class Button : public BaseDevice {
private:
  std::unique_ptr<BaseSensor> m_sensor;
  // should be replaced by constrain class
  // const std::string unit = "bool";

public:
  Button(std::unique_ptr<BaseSensor> sensor);
  int get_value();
  void set_value(int value){};
};

// class to implement output device which
// only knows on/off state
class BoolStateInfo : public BaseDevice {
private:
  std::unique_ptr<BaseOutput> m_output;
  // should be replaced by constrain class
  // const std::string unit = "bool";
  int m_state;

public:
  BoolStateInfo(std::unique_ptr<BaseOutput> output);
  int get_value() { return m_state; };
  void set_value(int value);
};

// class to implement a fan object
class Fan : public BaseDevice {
private:
  std::unique_ptr<BaseOutput> m_output;
  std::unique_ptr<BaseSensor> m_sensor;
  // should be replaced by constrain class
  // const std::string unit = "rpm";

public:
  Fan(std::unique_ptr<BaseSensor> sensor, std::unique_ptr<BaseOutput> output);
  int get_value();
  void set_value(int value);
};

} // namespace ductfan_control

#endif
