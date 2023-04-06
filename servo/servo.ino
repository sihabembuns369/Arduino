
int i = 0;
int b;
#include <Servo.h>
//int trig_pin = D2;
//int echo_pin = D3;
//
int pos;
//int duration = 0;
//int distance = 0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int  s1 = 5; //susu
int  s2 = 6; //kopi
int  s3 = 11; //gula
//const int led = 6;
//int pin = 2;
void setup() {

  Serial.begin(9600);
  // pinMode(pin,INPUT);
  //
  //  pinMode(trig_pin, OUTPUT);
  //  pinMode(echo_pin, INPUT);
  //  digitalWrite(trig_pin, LOW);
//  servo1.attach(s3);
//  servo1.write(30);
  servo2.attach(5);
  servo1.attach(6);
  
  //pinMode(led,OUTPUT);

}

void loop() {

  //kiri
  //buka 70, tutup 180

  //kanan
  //buka  0, 80
  //  Serial.println(digitalRead(pin));
  if (Serial.available() > 0) {
    String a = Serial.readString();
    b = a.toInt();
    //  servo.write(b);
    servo2.attach(6);
    servo2.write(b);
    delay(100);
    Serial.print("nilai servo = ");
    Serial.println(b);
  }

  //  digitalWrite(led,HIGH);
  //  delay(500);
  //    digitalWrite(led,LOW);
  //  delay(500);

//for(pos = 90; pos>= 40; pos -=1){
//    servo1.attach(6);
//      servo1.write(pos); //servo maju
//  delay(15);
//  
//  }
//
//  for(pos = 40; pos <= 90; pos +=1){
//    servo1.attach(pos);
//  delay(15);
//  
//  }


//  kanan
//  servo1.attach(6);
//majuuuu
  servo1.write(90); //servo maju
  servo2.write(95); //servo maju
//  servo2.attach(5);

  //kiri
  delay(800);

//    servo1.attach(6);
//nutup
  //balek
  servo1.write(35); //servo nutup
    servo2.write(150); //servo 
//  servo2.attach(5);

  delay(800);


  ////////////////////////servo gelas/////////////////////////
  //
  //    servo1.attach(6);
  //  servo1.write(86); //servo maju
  //  delay(700);
  //      servo1.attach(6);
  //  servo1.write(65); //servo nutup
  //  delay(700);
  //  ////////////////////////servo gelas////////////////////////


  /////////////////servo aduk////////////////
  //              delay(500);
  //          servo3.attach(5);
  //          servo3.write(120); //servo ke bawah
  //          delay(5000);
  //          servo3.attach(5);
  //          servo3.write(70); //servo keatas
  //           delay(1000);
  //         servo3.attach(5);
  //          servo3.write(50); //servo keatas
  //           delay(1000);
  //          servo3.attach(5);
  //          servo3.write(0); //servo keatas
  //          delay(700);
  //////////////////servo aduk
  //


  //servo kopi
  //    servo3.attach(10);
  //    servo3.write(10); // ke atas
  //    delay(300);
  //    servo3.attach(10);
  //    servo3.write(150); //ke bawah
  //    delay(300);
  //   // servo kopi
  //   }

  //    //servo susu
  //        servo4.attach(9);
  //      servo4.write(180); // ke bawah
  //      delay(200);
  //      servo4.attach(9);
  //      servo4.write(90); // ke atas
  //      delay(200);
  //      //servo susu

  //
  // digitalWrite(trig_pin, HIGH);
  //delayMicroseconds(1000);
  //  digitalWrite(trig_pin, LOW);
  //  duration = pulseIn(echo_pin , HIGH);
  //  distance = (duration/2) / 29.1 ;
  //  Serial.print(distance);
  //  Serial.println(" cm");
  //
  //
  //  if(distance > 3 and distance <20){
  //     servo2.attach(D4);
  //     servo2.write(0);
  //     delay(1000);
  //
  //    }else{
  //       servo2.attach(D4);
  //       servo2.write(180);
  //      }
  int b = 10;
  int c = 90;

  //Servo servo1;
  //Servo servo2;
  //Servo servo3;
  //
  //  s1 = 9; gula
  //int  s2 = 10; kopi
  //int  s3 = 11; susu

  //tengah/s3 tutup 70, buka 140
  // 1 kanan dan kiri buka 30 tutup 70
  //  servo1.attach(s1);
  //  servo1.write(140); //susu buka
  //   servo2.attach(s2);
  //  servo2.write(b);
  //
  //   servo1.attach(s1); //gula
  //  servo1.write(30);
  //  delay(200);
  //    servo1.attach(s1);
  //  servo1.write(65); //ssusu tutup
  //   servo2.attach(s2);
  //  servo2.write(c);
  //   servo1.attach(s1); //gula
  //  servo1.write(120);
  //  delay(200);
  ////buka 30, tutup 70
  //if(Serial.available()>0){
  //  String a = Serial.readString();
  //  int b = a.toInt();
  ////  servo.write(b);
  //  servo3.attach(s3);
  //  servo3.write(b);
  ////   servo2.attach(s2);
  ////  servo2.write(b);
  ////   servo3.attach(s3);
  ////  servo3.write(b);
  //  delay(500);
  //  Serial.print("nilai servo = ");
  //  Serial.println(b);
  //  }
}
