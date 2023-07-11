
#include "../../src/devcom/DuctFanControl.h"
#include <catch2/catch.hpp>

#include <memory>
#include <stdexcept>

using namespace ductfan_control;

int call_count = 0;
void test_callback(int param) { call_count++; }

void test_function(int param) { REQUIRE(param == param); }

TEST_CASE("Test message passing", "[eventing]") {

  SECTION("Basic Message and SimpleIntParameterHandler") {
    // Build basic handler
    SimpleIntParameterHandler handler_valid(test_function, "lorem");
    SimpleIntParameterHandler handler_invalid(test_function, "ipsum");
    std::string handler_id_valid = handler_valid.get_handler_id();
    std::string handler_id_invalid = handler_invalid.get_handler_id();

    // build basic messages
    std::vector<std::vector<std::string>> valid_message = {
        {"lorem", "1", "int"}};
    std::vector<std::vector<std::string>> invalid_message = {
        {"lorem", "ipsum", "dolor"}};

    // Create new message/event
    std::shared_ptr<BaseMessage> message =
        std::make_shared<SimpleMessage>(valid_message);

    // Get message ID for debugging reasons;
    std::string message_id = message->get_message_id();

    INFO("Message ID: " << message_id);
    INFO("Success Handler ID: " << handler_id_valid);
    INFO("Fail Handler ID: " << handler_id_invalid);

    SECTION("Basic Message and Handler init") {

      REQUIRE(message_id.length() > 0);
      REQUIRE(handler_id_valid.length() > 0);
      REQUIRE(handler_id_invalid.length() > 0);
    }

    SECTION("Test message output") {
      std::map<std::string, std::map<std::string, std::string>> message_val =
          message->read_message();

      REQUIRE(message_val["lorem"]["value"] == "1");
      REQUIRE(message_val["lorem"]["type"] == "int");
    }

    SECTION("Test handler callbacks") {

      bool callback_success = handler_valid.execute_callback(message);
      bool callback_fail = handler_invalid.execute_callback(message);

      REQUIRE(callback_success == true);
      REQUIRE(callback_fail == false);
    }
  }
}

TEST_CASE("Test event queing", "[eventing]") {

  // Should be a FIFO queue
  SECTION("Test SimpleFiFoQueue implementation") {
    // build basic messages

    SimpleFiFoQueue e_queue(10, 1);

    // check that new qure is empty
    REQUIRE(e_queue.is_empty() == true);
    REQUIRE(e_queue.is_full() == false);

    // fill queue until it is full
    int i = 0;
    bool full = false;
    while (!full) {
      std::vector<std::vector<std::string>> message = {
          {"lorem", std::to_string(i), "int"}};
      std::unique_ptr<BaseMessage> valid_message =
          std::make_unique<SimpleMessage>(message);
      e_queue.add_event(std::move(valid_message));
      i++;
      full = e_queue.is_full();
    }

    REQUIRE(e_queue.is_empty() == false);
    REQUIRE(e_queue.is_full() == true);

    // pop messages until queue is empty
    i = 0;
    bool empty = false;
    while (!empty) {
      std::unique_ptr<BaseMessage> message = e_queue.pop_event();
      INFO(message->get_message_id());
      REQUIRE(message->read_message()["lorem"]["value"] == std::to_string(i));
      i++;
      empty = e_queue.is_empty();
    }

    REQUIRE(e_queue.is_empty() == true);
    REQUIRE(e_queue.is_full() == false);

    // fill queue until it is full
    i = 0;
    full = false;
    while (!full) {
      std::vector<std::vector<std::string>> message = {
          {"lorem", std::to_string(i), "int"}};
      std::unique_ptr<BaseMessage> valid_message =
          std::make_unique<SimpleMessage>(message);
      e_queue.add_event(std::move(valid_message));
      i++;
      full = e_queue.is_full();
    }

    REQUIRE(e_queue.is_full() == true);
    i = 0;
    empty = false;
    while (i < 4) {
      std::unique_ptr<BaseMessage> message = e_queue.pop_event();
      INFO(message->get_message_id());
      REQUIRE(message->read_message()["lorem"]["value"] == std::to_string(i));
      i++;
      empty = e_queue.is_empty();
    }

    REQUIRE(e_queue.is_empty() == false);
    REQUIRE(e_queue.is_full() == false);

    // fill queue until it is full
    i = 0;
    full = false;
    while (!full) {
      std::vector<std::vector<std::string>> message = {
          {"lorem", std::to_string(i), "int"}};
      std::unique_ptr<BaseMessage> valid_message =
          std::make_unique<SimpleMessage>(message);
      e_queue.add_event(std::move(valid_message));
      i++;
      full = e_queue.is_full();
    }
  }
}

TEST_CASE("Test handler queing", "[eventing]") {

  SECTION("SimpleHandlerQueue") {

    // Setup handler queue
    SimpleHandlerQueue h_queue(5);

    std::string handler_uuid[5];

    for (int i = 0; i < 5; i++) {

      // Build basic handler
      // SimpleIntParameterHandler handler_valid(test_function, "lorem");

      std::unique_ptr<BaseHandler> handler_valid =
          std::make_unique<SimpleIntParameterHandler>(test_function, "lorem");
      // std::string handler_id_valid = handler_valid.get_handler_id();

      handler_uuid[i] = handler_valid->get_handler_id();

      h_queue.addHandler(std::move(handler_valid));
    }

    std::vector<std::unique_ptr<BaseHandler>> *handler_from_q =
        h_queue.getHandlers();

    int array_size = handler_from_q->size();

    REQUIRE(array_size == 5);

    for (int i = 0; i < 5; i++) {
      REQUIRE(handler_from_q->at(i)->get_handler_id() == handler_uuid[i]);
    }

    // add another handler to check if defined size is respected
    std::unique_ptr<BaseHandler> handler_valid =
        std::make_unique<SimpleIntParameterHandler>(test_function, "lorem");
    REQUIRE_THROWS_AS(h_queue.addHandler(std::move(handler_valid)),
                      std::runtime_error);
  }
}

TEST_CASE("Test eventing manager", "[eventing]") {
  SECTION("Test SimpleEventManager queue management") {

    // setup EventManager object
    SimpleEventManager event_manager;

    // add handler for 3 different queues
    for (int i = 0; i < 3; i++) {
      std::unique_ptr<BaseHandler> handler_valid =
          std::make_unique<SimpleIntParameterHandler>(test_callback, "lorem");

      event_manager.addHandler(std::move(handler_valid), i);
    }
    for (int i = 0; i < 3; i++) {
      std::unique_ptr<BaseHandler> handler_valid =
          std::make_unique<SimpleIntParameterHandler>(test_callback, "lorem");

      event_manager.addHandler(std::move(handler_valid), i);
    }

    // add single message for each handler
    for (int i = 0; i < 3; i++) {
      std::vector<std::vector<std::string>> message = {
          {"lorem", std::to_string(i), "int"}};
      std::unique_ptr<BaseMessage> valid_message =
          std::make_unique<SimpleMessage>(message);
      event_manager.addEvent(std::move(valid_message), i);
    }

    // process messages until empty
    for (int i = 0; i < 3; i++) {
      event_manager.processEvent();
    }

    REQUIRE(call_count == 6);

    // TODO test handler removal
  }
  SECTION("Test SimpleEventManager message processing") {}
}
