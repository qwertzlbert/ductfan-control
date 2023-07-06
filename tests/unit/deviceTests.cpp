#include "../../src/DuctFanControl.h"
#include "Catch2TestWithMainAndGMock.hpp"

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
  SECTION("StatefullEzButton") {

    // Only test if class can be instantiated. Otherwise this would require to
    // override the non-virtual ezButton class which is not worth it
    StatefullEzButton sensor(2);

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
  SECTION("Button") {

    auto sensor = std::make_unique<MockSensor>();
    // MockSensor sensor;

    EXPECT_CALL(*sensor, get_current_value())
        .Times(AtLeast(1))
        .WillOnce(Return(0))
        .WillOnce(Return(1))
        .WillRepeatedly(Return(42));

    // init button
    Button button(std::move(sensor));

    REQUIRE(button.get_value() == 0);
    REQUIRE(button.get_value() == 1);
    REQUIRE(button.get_value() == 1);

    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(sensor.get()));
  }

  SECTION("BoolStateInfo") {

    auto output = std::make_unique<MockOutput>();

    EXPECT_CALL(*output, set_value(10)).Times(AtLeast(1));

    BoolStateInfo statusLight(std::move(output));

    // initial state should be 0
    REQUIRE(statusLight.get_value() == 0);

    statusLight.set_value(10);

    // after toggle it should be 1
    REQUIRE(statusLight.get_value() == 1);
    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(output.get()));
  }

  SECTION("Fan") {
    auto output = std::make_unique<MockOutput>();
    auto sensor = std::make_unique<MockSensor>();

    EXPECT_CALL(*output, set_value(10)).Times(AtLeast(1));

    EXPECT_CALL(*sensor, get_current_value())
        .Times(AtLeast(1))
        .WillOnce(Return(0))
        .WillRepeatedly(Return(3000));

    Fan ductFan(std::move(sensor), std::move(output));

    ductFan.set_value(10);

    REQUIRE(ductFan.get_value() == 0);
    REQUIRE(ductFan.get_value() == 3000);
    REQUIRE(ductFan.get_value() == 3000);

    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(sensor.get()));
    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(output.get()));
  }
}
