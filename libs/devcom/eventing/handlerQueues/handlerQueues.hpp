#ifndef HANDLERQUEUES_H
#define HANDLERQUEUES_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
// #include <uuid/uuid.h>
#include <vector>

#include "eventing/eventHandlers/eventHandlers.hpp"

namespace devcom {

class HandlerQueue {
public:
  virtual void addHandler(std::unique_ptr<BaseHandler> handler) = 0;
  virtual void removeHandler(std::string uuid) = 0;
  // will return unique pointers to each handler, so it can get
  // updated by the Event and get executed  by the EventManager
  virtual std::vector<std::unique_ptr<BaseHandler>> *getHandlers() = 0;
  virtual std::string get_handler_queue_id() = 0;
};

// simple event_type handler queue implemented using
// a map
class SimpleHandlerQueue : public HandlerQueue {
private:
  std::string m_handler_queue_id;
  std::vector<std::unique_ptr<BaseHandler>> m_queue;
  int m_queue_size;

public:
  SimpleHandlerQueue(int queue_size);
  std::string get_handler_queue_id() { return m_handler_queue_id; };
  std::vector<std::unique_ptr<BaseHandler>> *getHandlers();
  void removeHandler(std::string uuid);
  void addHandler(std::unique_ptr<BaseHandler> handler);
};

} // namespace devcom
#endif
