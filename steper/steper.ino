// Include the Stepper library:
#include <Stepper.h>

// Define number of steps per revolution:
const int stepsPerRevolution = 200;

// Initialize the stepper library on pins 8 through 11:
Stepper myStepper = Stepper(stepsPerRevolution, 6, 7, 8, 9);

void setup() {
  // Set the motor speed (RPMs):
  myStepper.setSpeed(120);
}

void loop() {
  // Step one revolution in one direction:
  myStepper.step(200);

  delay(500);

  // Step on revolution in the other direction:
  myStepper.step(-200);

  delay(500);
}
