#include "eventManager.hpp"

namespace ductfan_control {

SimpleEventManager::SimpleEventManager() {
  uuid_t uuid_native;
  char uuid_char[32];
  uuid_generate(uuid_native);
  uuid_unparse_lower(uuid_native, uuid_char);

  m_event_manager_id = uuid_char;
}

void SimpleEventManager::addEvent(std::unique_ptr<BaseMessage> event,
                                  int event_type) {

  try {
    m_event_queues.at(event_type)->add_event(std::move(event));
  } catch (std::out_of_range) {
    std::unique_ptr<BaseEventQueue> queue =
        std::make_unique<SimpleFiFoQueue>(5, 1);
    queue->add_event(std::move(event));
    m_event_queues[event_type] = std::move(queue);
  }
}

void SimpleEventManager::addHandler(std::unique_ptr<BaseHandler> handler,
                                    int event_type) {

  try {
    m_handler_queues.at(event_type)->addHandler(std::move(handler));
  } catch (std::out_of_range) {

    std::unique_ptr<HandlerQueue> queue =
        std::make_unique<SimpleHandlerQueue>(5);
    queue->addHandler(std::move(handler));

    m_handler_queues[event_type] = std::move(queue);
  }
}

void SimpleEventManager::removeHandler(std::string handler_id) {}

void SimpleEventManager::processEvent() {

  // find message to broadcast
  std::map<int, std::unique_ptr<BaseEventQueue>>::iterator q_end;
  if (m_last_visited != m_event_queues.begin()) {
    q_end = m_last_visited--;
  } else {
    q_end = m_event_queues.end();
  }

  // cast to shared_ptr as ownership is now shared between all handlers as
  // long as message is processed
  std::shared_ptr<BaseMessage> message;

  // Check if any message is queued
  // Break loop if message was found
  // Using the class variable 'm_last_visited' and incrementing on it should
  // ensure that we will treat each queue equally and will iterate over all and
  // not don't prefer the ones queued first
  for (m_last_visited; m_last_visited != q_end; ++m_last_visited) {
    // check needs to be done so that message is left in queue if
    // we don't have any listener
    if (m_handler_queues[(m_last_visited->first)] != nullptr) {
      try {
        message = m_last_visited->second->pop_event();
        break;
      } catch (std::runtime_error) {
        // continue normally as queue was empty
      }
    }
    if (q_end != m_event_queues.end() and
        m_last_visited == m_event_queues.end()) {
      m_last_visited == m_event_queues.begin();
    }
  }

  // check if handlers for event type exist, otherwise leave message alone
  if (message != nullptr) {

    std::vector<std::unique_ptr<BaseHandler>> *handlers =
        m_handler_queues.at(m_last_visited->first)->getHandlers();

    for (int i = 0; i < handlers->size(); ++i) {
      handlers->at(i)->execute_callback(message);
    }
  }
}

} // namespace ductfan_control
