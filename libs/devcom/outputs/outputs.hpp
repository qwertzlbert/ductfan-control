#ifndef OUTPUTS_H
#define OUTPUTS_H

// #include "driver/ledc.h"

namespace devcom {
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

} // namespace devcom

#endif
