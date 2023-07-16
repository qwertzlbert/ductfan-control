#ifndef SENSORS_H
#define SENSORS_H

#include <memory>

// for arduino
// #include <ezButton.h>

namespace devcom {

// implements an internal interface to abstract away
// external dependencies
class BaseSensor {

public:
  virtual ~BaseSensor() = default;
  virtual int get_current_value() = 0;
};

// Dummy sensor for write only devices
class DummySensor : public BaseSensor {
public:
  DummySensor();
  int get_current_value() { return 0; };
};

// state aware button using ezButton library
// class StatefullEzButton : public BaseSensor {

//   std::unique_ptr<ezButton> m_button;

// public:
//   StatefullEzButton(int pin);
//   int get_current_value();
// };

} // namespace devcom

#endif
