
#include <AUnit.h>
#include <DuctFanControl.h>
#include <iostream>

using namespace aunit;
using namespace ductfan_control;

FanButton testButton(21);

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only

  testButton.setDebounceTime(50);
}

void loop() { TestRunner::run(); }

test(invalid_pwm_value) {
  const int pwm_mod = 1000;

  bool test_passed = false;

  try {
    testButton.setPwmMod(pwm_mod);
  } catch (const std::runtime_error &e) {
    test_passed = true;
  }

  assertTrue(test_passed);
}

test(configure_pwm_value) {
  const int pwm_mode_a = 42;
  const int pwm_mode_b = 50;

  testButton.setPwmMod(pwm_mode_a);
  assertEqual(pwm_mode_a, testButton.getPwmMod());

  testButton.setPwmMod(pwm_mode_b);
  assertEqual(pwm_mode_b, testButton.getPwmMod());
}
