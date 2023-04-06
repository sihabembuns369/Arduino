    /*
  L298N DC MOTOR DRIVER MODULE
  modified on 25 Sep 2020
  by Saeed Olfat @ Electropeak
  Home

  
*/

#include <Stepper.h>
const int stepsPerRevolution = 100;

// Initialize the stepper library on pins 8 through 11:
Stepper myStepper = Stepper(stepsPerRevolution,8,9,10,11);
void setup() {
    myStepper.setSpeed(100);
//  pinMode(8, OUTPUT); //IN2
//  pinMode(9, OUTPUT); //IN1
//  pinMode(10, OUTPUT); //Enable Pin
}
void loop() {

// Full speed forward
//  digitalWrite(8, HIGH);
//  digitalWrite(9, LOW);
//  digitalWrite(10, HIGH);
//
//  delay(3000);
//
//// Full speed backward
//  digitalWrite(8, LOW);
//  digitalWrite(9, HIGH);
//  digitalWrite(10, HIGH);
//
//  delay(3000);
//
//// 0 to 100% speed in forward mode
//  for (int i=0;i<130;i++)
//  {   digitalWrite(8, HIGH);
//      digitalWrite(9, LOW);
//      analogWrite(10, i);
//      delay(20);      
//      }
//
//  delay(50);
//
//  // 0 to 100% speed in backward mode
//        for (int i=0;i<130;i++)
//  {   digitalWrite(8, LOW);
//      digitalWrite(9, HIGH);
//      analogWrite(10, i);
//      delay(20);      
//      }
//
//        delay(50);
          // Step one revolution in one direction:
  myStepper.step(200);

  delay(50);

  // Step on revolution in the other direction:
  myStepper.step(-200);

  delay(50);

}
