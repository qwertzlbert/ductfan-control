#include "eventHandlers.hpp"

namespace devcom {

SimpleIntParameterHandler::SimpleIntParameterHandler(
    std::function<void(int)> callback_function, std::string parameter_name) {
  // uuid_t uuid_native;
  // char uuid_char[32];
  // uuid_generate(uuid_native);
  // uuid_unparse_lower(uuid_native, uuid_char);

  // m_handler_id = uuid_char;
  m_handler_id = "BGw5yAtNgcsryz6V2CuuHt5ZAhU6buy2";

  m_callback_function = callback_function;
  m_parameter_name = parameter_name;
}

bool SimpleIntParameterHandler::execute_callback(
    std::shared_ptr<BaseMessage> message) {

  bool success = true;

  try {

    int param = decode_int_message(message->read_message()[m_parameter_name]);
    m_callback_function(param);

  } catch (std::exception &e) {
    // log something
    success = false;
  }

  return success;
}

SimpleDeviceHandler::SimpleDeviceHandler(std::shared_ptr<BaseDevice> device,
                                         std::string parameter_name) {
  m_handler_id = "ZGw5yAtNgcsLyz6V2CuuHt5ZAhU6bay2";
  m_parameter_name = parameter_name;
  m_device = device;
}

bool SimpleDeviceHandler::execute_callback(
    std::shared_ptr<BaseMessage> message) {
  bool success = true;

  try {

    int param = decode_int_message(message->read_message()[m_parameter_name]);
    m_device->set_value(param);

  } catch (std::exception &e) {
    // log something
    success = false;
  }

  return success;
}

} // namespace devcom
