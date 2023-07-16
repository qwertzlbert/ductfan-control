
#include <AUnit.h>
#include <DuctFanControl.h>
#include <iostream>

#include <memory>

using namespace aunit;
using namespace ductfan_control;

std::unique_ptr<BaseSensor> testButton =
    std::make_unique<StatefullEzButton>(20);

Button realTestButton(std::move(testButton));

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only
}

void loop() { TestRunner::run(); }

test(invalid_pwm_value) {
  const int pwm_mod = 1000;

  bool test_passed = false;
  assertTrue(test_passed);
}

test(configure_pwm_value) {
  const int pwm_mode_a = 42;
  const int pwm_mode_b = 50;

  // testButton.setPwmMod(pwm_mode_a);
  // assertEqual(pwm_mode_a, testButton.getPwmMod());

  // testButton.setPwmMod(pwm_mode_b);
  // assertEqual(pwm_mode_b, testButton.getPwmMod());
}
