#include <Wire.h>
//int  led1 =  8;
int led2 =  9;
int val = 0;
int x = 0;
#define buton3  10
void setup() {
//  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
     pinMode(buton3, INPUT_PULLUP);
  // put your setup code here, to run once:

}

void receiveEvent(int bytes)
{
  x = Wire.read();
}

void loop() {
 Serial.print("buton 3 = ");
  Serial.println(digitalRead(buton3));
//  val = digitalRead(buton3);
//
if(digitalRead(buton3) == 1){
  val++;
  }
  if(val >= 5){
    val = 0;
    }
    Serial.println(val);
  if (digitalRead(buton3) == 1) {
Serial.println("nyalai oke");
    Wire.beginTransmission(8);
    Wire.write(3);
    Wire.endTransmission();
//    value = 0;
  }else  if (val > 2) {
Serial.println("mati oke");
    Wire.beginTransmission(8);
    Wire.write(4);
    Wire.endTransmission();
//    value = 0;
  }

    if (x == 3)
  {
    digitalWrite(led2, HIGH);

  }if(x == 4){
        digitalWrite(led2, LOW);
//            x = 0;
    }
//  else if (x == 2)
//  {
//    digitalWrite(led2, HIGH);
////    x = 0;
//  } else if (x == 3){
//    Serial.begin("mati");
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, LOW);
//    x = 0;
//  }

}
