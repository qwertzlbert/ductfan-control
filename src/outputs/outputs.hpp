#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "driver/ledc.h"

namespace ductfan_control {
class BaseOutput {

public:
  virtual ~BaseOutput() = default;
  virtual void set_value(int value) = 0;
};

// Dummy output for read only devices
class DummyOutput : public BaseOutput {
public:
  DummyOutput();
  void set_value(int value){};
};

// output for ESP32 using hardware controlled
// PWM without fading (fading requires semaphores)
class Esp32PwmHighSpeed : public BaseOutput {
public:
  Esp32PwmHighSpeed(int pin, int channel);
  void set_value(int value);
};

} // namespace ductfan_control

#endif
