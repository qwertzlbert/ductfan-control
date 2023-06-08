#ifndef SENSORS_H
#define SENSORS_H

namespace ductfan_control {
class BaseSensor {

public:
  virtual int get_current_value() = 0;
};

// Dummy sensor for write only devices
class DummySensor : public BaseSensor {
public:
  DummySensor();
  int get_current_value() { return 0; };
};
} // namespace ductfan_control

#endif
