#include "eventQueues.hpp"

namespace devcom {

SimpleFiFoQueue::SimpleFiFoQueue(int queue_size, int queue_type) {
  // uuid_t uuid_native;
  // char uuid_char[32];
  // uuid_generate(uuid_native);
  // uuid_unparse_lower(uuid_native, uuid_char);

  // m_event_queue_id = uuid_char;
  m_event_queue_id = "Cp9slMlam8hG4kGuuHyeulqXoPVdpPBs";

  m_queue_size = queue_size;
  m_queue_type = queue_type;

  m_event_queue.resize(m_queue_size);
}

bool SimpleFiFoQueue::is_empty() {

  bool empty = false;

  if (m_tail == m_head) {
    empty = true;
  }

  return empty;
}

bool SimpleFiFoQueue::is_full() {

  bool full = false;

  // This kind of wrap is more resilent and
  // computational cheaper than using modulo
  if (m_head == m_tail - 1 && m_tail != 0) {
    full = true;
  } else if (m_head == m_queue_size - 1 && m_tail == 0) {
    full = true;
  }

  return full;
}

std::tuple<bool, std::string>
SimpleFiFoQueue::add_event(std::unique_ptr<BaseMessage> event) {

  bool success = false;
  std::string message_id = event->get_message_id();

  // check if queue is full
  if (is_full() == false) {

    m_event_queue.at(m_head) = std::move(event);

    if (m_head == m_queue_size - 1) {
      m_head = 0;
    } else {
      m_head++;
    }

    success = true;
  }

  return {success, message_id};
}

std::unique_ptr<BaseMessage> SimpleFiFoQueue::pop_event() {

  std::unique_ptr<BaseMessage> event;
  if (is_empty() == false) {
    event = std::move(m_event_queue.at(m_tail));
    if (m_tail == m_queue_size - 1) {
      m_tail = 0;
    } else {
      m_tail++;
    }
  } else {
    throw std::runtime_error("Queue Empty - Can't pop any event");
  }

  // return std::move(event);
  return event;
}

} // namespace devcom
