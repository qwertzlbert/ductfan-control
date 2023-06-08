#include "../../src/DuctFanControl.h"
#include "Catch2TestWithMainAndGMock.hpp"
#include "MockScopeGuard.hpp"

#include <memory>

using namespace ductfan_control;
using ::testing::AtLeast;
using ::testing::Return;

class MockSensor : public BaseSensor {
public:
  MOCK_METHOD(int, get_current_value, (), (override));
};

class MockOutput : public BaseOutput {
public:
  MOCK_METHOD(void, set_value, (int value), (override));
};

TEST_CASE("Test Sensors", "[devices]") {
  SECTION("Dummy Sensor") {

    DummySensor sensor;

    REQUIRE(sensor.get_current_value() == 0);
  }
}

TEST_CASE("Test Outputs", "[devices]") {
  SECTION("Dummy Output") {

    // as DummyOutput does nothing
    // we will only try to create an instance
    DummyOutput output;
  }
}

TEST_CASE("Test Devices", "[devices]") {
  SECTION("Statefull Button") {

    auto sensor = std::make_unique<MockSensor>();
    // MockSensor sensor;

    EXPECT_CALL(*sensor, get_current_value())
        .Times(AtLeast(1))
        .WillOnce(Return(0))
        .WillOnce(Return(1))
        .WillRepeatedly(Return(42));

    // init button
    StatefullButton button(std::move(sensor));

    REQUIRE(button.get_value() == 0);
    REQUIRE(button.get_value() == 1);
    REQUIRE(button.get_value() == 1);
  }
}
