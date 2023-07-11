#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <uuid/uuid.h>

#include "eventing/eventHandlers/eventHandlers.hpp"
#include "eventing/eventMessages/eventMessages.hpp"
#include "eventing/eventQueues/eventQueues.hpp"
#include "eventing/handlerQueues/handlerQueues.hpp"

namespace ductfan_control {

// ABC for EventManagers
class EventManager {
public:
  virtual void processEvent() = 0;
  virtual void addEvent(std::unique_ptr<BaseMessage> event, int event_type) = 0;
  virtual void addHandler(std::unique_ptr<BaseHandler>, int event_type) = 0;
  virtual void removeHandler(std::string handler_id) = 0;
};

// This simple manager will use predefined queue types
// and won't allow manual configuration per queue type
class SimpleEventManager : public EventManager {
private:
  std::string m_event_manager_id;
  std::map<int, std::unique_ptr<HandlerQueue>> m_handler_queues;
  std::map<int, std::unique_ptr<BaseEventQueue>> m_event_queues;

  // this variable saves info about the event queue which was visited last
  std::map<int, std::unique_ptr<BaseEventQueue>>::iterator m_last_visited =
      m_event_queues.begin();

public:
  SimpleEventManager();
  void processEvent();
  void addEvent(std::unique_ptr<BaseMessage> event, int event_type);
  void addHandler(std::unique_ptr<BaseHandler> handler, int event_type);
  void removeHandler(std::string handler_id);
};

}; // namespace ductfan_control
#endif
