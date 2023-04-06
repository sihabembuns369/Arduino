#include "PinChangeInterrupt.h"
volatile int pulse = 0;
int koin;
int pin = 10;
int harga = 4000;
void coin_value() {
  pulse = pulse + 1;
  Serial.println("oke");
  
}

void setup() {
  Serial.begin(9600);
  //pinMode(2, INPUT);
 // Serial.println("Ready to be collected");
  /// attachInterrupt(digitalPinToInterrupt(3),  coin_value, CHANGE);
  //attachInterrupt(1, coin_value, CHANGE);
   attachPCINT(digitalPinToPCINT(10), coin_value, FALLING);
}

void loop() {

  if (pulse > 0)
    {
    
    delay (400);   // let the other pulses arrive
    if (pulse == 1) {
      Serial.println("500");
     
      harga -=500;
    }
    if (pulse == 2) {
      Serial.println("1000");
      
       harga -=1000;
    }
//    if (pulse == 1) {
//      Serial.println("500");
//   
//       harga -=1000;
//    }
    
    pulse = 0;  // clear for next time
  }
Serial.println(harga);


}
