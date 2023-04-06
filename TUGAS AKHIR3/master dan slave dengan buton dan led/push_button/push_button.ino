#include <Wire.h>
//#define buton1  11
//#define buton2  12
#define buton3  10
int val = 0;
int  led1 =  9;
int x = 0;
void setup() {
  pinMode (led1, OUTPUT);
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
//  pinMode(buton1, INPUT_PULLUP);
//  pinMode(buton2, INPUT_PULLUP);
   pinMode(buton3, INPUT_PULLUP);
}

void loop() {
//  Wire.begin();
  //   put your main code here, to run repeatedly:
//  Serial.print("buton 1 = ");
//  Serial.println(digitalRead(buton1));
////  Serial.println("");
//  Serial.print("buton 2 = ");
//  Serial.println(digitalRead(buton2));

//  Serial.println(value);
//  if (digitalRead(buton2) > 0) {
//    value++;
//  }
//  if (value > 20) {
//    value = 0;
//  }
//  if (digitalRead(buton1) == 1) {
//
//    Wire.beginTransmission(9);
//    Wire.write(1);
//    Wire.endTransmission();
//  } else if (digitalRead(buton2) == 1) {
//
//    Wire.beginTransmission(9);
//    Wire.write(2);
//    Wire.endTransmission();
//  }
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
    Wire.beginTransmission(9);
    Wire.write(3);
    Wire.endTransmission();
//    value = 0;
  }else  if (val > 2) {
Serial.println("mati oke");
    Wire.beginTransmission(9);
    Wire.write(4);
    Wire.endTransmission();
//    value = 0;
  }

    if (x == 3)
  {
    digitalWrite(led1, HIGH);

  }if(x == 4){
        digitalWrite(led1, LOW);
//            x = 0;
    }
  
}


void receiveEvent(int bytes)
{
  x = Wire.read();
}
