#ifndef OUTPUTS_H
#define OUTPUTS_H

namespace ductfan_control {
class BaseOutput {

public:
  virtual void set_value(int value) = 0;
};

// Dummy output for read only devices
class DummyOutput : public BaseOutput {
public:
  DummyOutput();
  void set_value(int value){};
};
} // namespace ductfan_control

#endif
