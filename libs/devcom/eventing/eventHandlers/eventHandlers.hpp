#ifndef EVENTHANDLERS_H
#define EVENTHANDLERS_H

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
// #include <uuid/uuid.h>
#include <vector>

#include "devices/devices.hpp"
#include "eventing/eventMessages/eventMessages.hpp"

namespace devcom {

// ABC handler
class BaseHandler {

public:
  virtual std::string get_handler_id() = 0;
  virtual bool execute_callback(std::shared_ptr<BaseMessage> message) = 0;
};

// Simple handler for functions with int parameters
class SimpleIntParameterHandler : public BaseHandler {
private:
  std::string m_handler_id;
  std::function<void(int)> m_callback_function;
  std::string m_parameter_name;

public:
  SimpleIntParameterHandler(std::function<void(int)> callback_function,
                            std::string parameter_name);
  std::string get_handler_id() { return m_handler_id; };
  bool execute_callback(std::shared_ptr<BaseMessage> message);
};

// MISSING TEST
// Simple handler for BaseDevice
class SimpleDeviceHandler : public BaseHandler {
private:
  std::string m_handler_id;
  std::string m_parameter_name;
  std::shared_ptr<BaseDevice> m_device;

public:
  SimpleDeviceHandler(std::shared_ptr<BaseDevice> device,
                      std::string parameter_name);
  std::string get_handler_id() { return m_handler_id; };
  bool execute_callback(std::shared_ptr<BaseMessage> message);
};

} // namespace devcom

#endif
