#include <Servo.h>
Servo servo1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
  servo1.write(3600);
  delay(2000);

 
    servo1.write(-3600);
  delay(800);
  


  
}
