#ifndef DUCTOUTS_H
#define DUCTOUTS_H

#include "DevCom.h"
namespace ductfan {
// output for ESP32 using hardware controlled
// PWM without fading (fading requires semaphores)
class Esp32PwmHighSpeed : public devcom::BaseOutput {
public:
  Esp32PwmHighSpeed(int pin, int channel);
  void set_value(int value);
};

} // namespace ductfan

#endif
