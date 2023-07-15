#ifndef EVENTQUEUES_H
#define EVENTQUEUES_H

#include "eventing/eventMessages/eventMessages.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <uuid/uuid.h>
#include <vector>

namespace devcom {

// ABC for event queues
class BaseEventQueue {
public:
  virtual bool is_full() = 0;
  virtual bool is_empty() = 0;
  virtual std::tuple<bool, std::string>
  add_event(std::unique_ptr<BaseMessage> event) = 0;
  virtual std::unique_ptr<BaseMessage> pop_event() = 0;
  virtual std::string get_queue_id() = 0;
};

// simple FIFO queue implemented as
// a ring buffer with a fixed size
// using arrays
class SimpleFiFoQueue : public BaseEventQueue {
private:
  int m_queue_size = 0;

  std::vector<std::unique_ptr<BaseMessage>> m_event_queue;

  int m_head = 0;
  int m_tail = 0;

  int m_queue_type;

  std::string m_event_queue_id;

public:
  SimpleFiFoQueue(int queue_size, int queue_type);

  bool is_full();
  bool is_empty();

  // should retun success or failure + event id
  std::tuple<bool, std::string> add_event(std::unique_ptr<BaseMessage> event);

  std::unique_ptr<BaseMessage> pop_event();
  virtual std::string get_queue_id() { return m_event_queue_id; };
};

}; // namespace devcom

#endif
