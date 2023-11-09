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

// Set pins of stepper, switch, and LEDS to however they're configured in YOUR circuit:

/*
 * Note on stepper pins:
 * Arduino library hooks up pins to the motor's control wires in a weird way following this diagram:
 * Step C0 C1 C2 C3
 *    1  1  0  1  0
 *    2  0  1  1  0
 *    3  0  1  0  1
 *    4  1  0  0  1
 * This means that if you have your motors pin hooked up in the order (4, 5, 6, 7), then you need
 * to switch the two middle control wires when entering it into the stepper constructor (4, 6, 5, 7)
 */
Stepper stepper(STEP_SIZE, 4, 6, 5, 7);

const int switchPin = 10;
const int ledLeft = 0;
const int ledRight = 0;

bool priorState = false;
int stepper_threshold = 0;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  
  stepper.setSpeed(10);
}

void loop() {
  // Toggle Switch State
  bool switchState = !digitalRead(switchPin);
  if (switchState == HIGH && switchState != priorState) {
    Serial.print("on\n");
    priorState = switchState;
    delay(50); // small delay in order for hardware (switch) to fully change states
  }
  else if (switchState == LOW && switchState != priorState) {
    Serial.print("off\n");
    priorState = switchState;
    delay(50); // small delay in order for hardware (switch) to fully change states
  }

  // Stateful Operations
  if (switchState == HIGH) {
    // Do all Continuous Operations while switch is toggled ON:
    stepper.step(1);
    stepper_threshold++;
  }
  else if (switchState == LOW && stepper_threshold > 0) {
    // Do all Continuous Operations while switch is toggled OFF:
    stepper.step(-1);
    stepper_threshold--;
  }
}
