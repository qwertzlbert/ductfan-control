#ifndef EVENTMESSAGES_H
#define EVENTMESSAGES_H

#include <map>
#include <stdexcept>
#include <string>
#include <uuid/uuid.h>
#include <vector>

namespace devcom {

class BaseMessage {

public:
  virtual std::map<std::string, std::map<std::string, std::string>>
  read_message() = 0;
  virtual std::string get_message_id() = 0;
};

class SimpleMessage : public BaseMessage {
private:
  std::map<std::string, std::map<std::string, std::string>> m_message;
  std::string m_message_id;

public:
  SimpleMessage(std::vector<std::vector<std::string>> message);
  std::map<std::string, std::map<std::string, std::string>> read_message() {
    return m_message;
  };
  std::string get_message_id() { return m_message_id; };
};

// inline decoder functions
inline int decode_int_message(std::map<std::string, std::string> &message) {

  // validate if we should decode the message
  if (message["type"] != "int") {
    throw std::invalid_argument(
        "Provided type not supported by decoder method");
  }

  return stoi(message["value"]);
}

inline std::string
decode_string_message(std::map<std::string, std::string> &message) {
  // validate if we should decode the message
  if (message["type"] != "string") {
    // should throw more precise error message
    throw;
  }

  return message["value"];
}

}; // namespace devcom

#endif
