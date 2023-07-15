#include "eventMessages.hpp"

namespace devcom {

SimpleMessage::SimpleMessage(std::vector<std::vector<std::string>> message) {
  uuid_t uuid_native;
  char uuid_char[32];
  uuid_generate(uuid_native);
  uuid_unparse_lower(uuid_native, uuid_char);

  m_message_id = uuid_char;

  std::vector<std::vector<std::string>>::iterator iter = message.begin();

  for (iter; iter < message.end(); iter++) {

    m_message[(*iter)[0]] = {{"value", (*iter)[1]}, {"type", (*iter)[2]}};
  }
}

} // namespace devcom
