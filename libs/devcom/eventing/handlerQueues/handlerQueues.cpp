#include "handlerQueues.hpp"

namespace devcom {

SimpleHandlerQueue::SimpleHandlerQueue(int queue_size) {
  // uuid_t uuid_native;
  // char uuid_char[32];
  // uuid_generate(uuid_native);
  // uuid_unparse_lower(uuid_native, uuid_char);

  // m_handler_queue_id = uuid_char;
  m_handler_queue_id = "uImfkc9g2970c5UObYOmr9ZJuqony9zE";
  m_queue_size = queue_size;
  // m_queue.resize(m_queue_size);
};

std::vector<std::unique_ptr<BaseHandler>> *SimpleHandlerQueue::getHandlers() {

  return &m_queue;
};

void SimpleHandlerQueue::removeHandler(std::string uuid){

};

void SimpleHandlerQueue::addHandler(std::unique_ptr<BaseHandler> handler) {

  if (m_queue.size() >= m_queue_size) {
    throw std::runtime_error("Handler queue for this eventtype is full!");
  } else {
    m_queue.push_back(std::move(handler));
  }
};

} // namespace devcom
