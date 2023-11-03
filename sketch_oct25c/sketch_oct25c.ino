/*
 * Useless Box stepper motor control script
 * Cole Saldanha
 * Last updated 11/3/2023
 * Licensed under the MIT license
 */

#include <Stepper.h>

/*
 * A 28BYJ-48 motor has a step size
 * of 11.25 degrees, and the motor has a
 * 1/64 reduction gear set which equates
 * to a step size of 2048 per 1 full
 * revolution. In other words, do
 * not change this
 */
#define STEP_SIZE 2048 

Stepper stepper(STEP_SIZE, 4, 6, 5, 7);

const int switchPin = 10;
const int ledLeft = 0;
const int ledRight = 0;

bool priorState = false;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  
  stepper.setSpeed(10);
}

void loop() {
  bool switchState = !digitalRead(switchPin);
  if (switchState == HIGH && switchState != priorState) {
    Serial.print("on\n");
    stepper.step(STEP_SIZE);
    priorState = switchState;
    delay(500);
  }
  else if (switchState == LOW && switchState != priorState) {
    Serial.print("off\n");
    stepper.step(-STEP_SIZE);
    priorState = switchState;
    delay(500);
  }
}
