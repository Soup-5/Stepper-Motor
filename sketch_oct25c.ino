#include <Stepper.h>
#define STEP_SIZE 2048

Stepper stepper(STEP_SIZE, 4, 6, 5, 7);
const int switchPin = 10;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  stepper.setSpeed(10);
}

void loop() {
  bool switchState = !digitalRead(switchPin);
  if (switchState == HIGH) {
    stepper.step(-1);
  }
  else {
    stepper.step(1);
  }
}
