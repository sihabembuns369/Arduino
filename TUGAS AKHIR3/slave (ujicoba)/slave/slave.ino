
#include <Servo.h>
#include <Wire.h>
//=========================== water flow=================
int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 2; //Digital Pin 2
//int solenoidValve = 4; // Digital pin 5
unsigned int SetPoint = 500; //400 milileter
/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 72; //You can change according to your datasheet default 70

volatile byte pulseCount = 0;

float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long milis;
unsigned long oldTime = 0;

  int i = 0;


int x = 0;

Servo servo1; //
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;


//==================================================

// penerima
String data = "";
String hasilservo = "";
char input = "";
int servosusu = 9, servokopi = 10, servogula = 11, dinamomundur = A1, dinamomaju = A2 , input1 = 12, input2 = 8, sensorbotol = 4, pompaair = 7, sensorflow = 2, servoaduk = 5, servobotol = 6;
bool maju = true, mundur = true, s_input1 = true, s_input2 = true, s_input3 = true, dinamomju = true, dinamomndur = true, dinamostp = true, servojalanstate = true, servot = true, jalan = false, jalan2 = false;;
bool kopistate = true;
bool servogelasstate = true;
bool statepompa = true;
bool kopimanis = false;
int it = 0;
char abc[30];
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

void setup()
{
 //=======================================menerima request dari arduino master =============
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  pinMode(dinamomaju, OUTPUT);
  pinMode(dinamomundur, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(sensorbotol, INPUT);
  pinMode(pompaair, OUTPUT);
  pinMode(sensorflow, INPUT);

  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  //   servo1.attach(servokopi);
  //      servo2.attach(servogula);
  //         servo3.attach(servosusu);

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  delay(100);

  servo3.attach(servogula);
  servo3.write(30);
  servo4.attach(servoaduk); //gula
  servo4.write(0);
  delay(200);
}
void receiveEvent(int bytes)
{

  x = Wire.read();
  switch (x) {
    case 1:
      hasilservo = "kopimanis";
      break;
    case 2:
      hasilservo = "kopipahit";
      break;
    case 3:
      hasilservo = "kopisedang";
      break;
    case 4:
      hasilservo = "susu";
      break;
    case 5:
      hasilservo = "kopisusu";
      break;

  }

}

void loop(void)
{

  int input_1 = digitalRead(input1);
  int input_2 = digitalRead(input2);
  int sensorbtl = digitalRead(sensorbotol);



Serial.println(x);
  if (x > 0 || Serial.available() > 0 ) {
    Serial.println("ada pesan masuk");
    String abv = Serial.readString();
    x = abv.toInt();
    jalan = true;
    //    x = 0 ;
  }

Serial.println(jalan);

while(jalan == true){
  Serial.println(digitalRead(sensorbotol));
  Serial.println("jalan true");
 if(digitalRead(sensorbotol == 0) && servogelasstate == true){
      Serial.println("servo gelas jalan");
    //////////////////////////servo gelas/////////////////////////

    servo5.attach(servobotol);
  servo5.write(86); //servo maju
  delay(700);
      servo5.attach(servobotol);
  servo5.write(65); //servo nutup
  delay(700);

////  ////////////////////////servo gelas////////////////////////
  if(digitalRead(sensorbotol)){
    jalan = false;
    jalan2 =true;

    }
    }
  }
  // rencana b
    if (jalan2 == true) {
//      Serial.println("botol terdeteksi");
  
      if (sensorbtl == 1) {
//        Serial.println("botol terdeteksi");
        dinamo("maju");
        if (input_1 == 1 && s_input1 == true)
        {
          dinamomju = false;
//          Serial.println("sensor 1 terdeteksi");
          Serial.print(" ");
          dinamo("stop");
          s_input1 = false;
          //        dinamostp = false;
          delay(600);
  
          servo(hasilservo);

//Serial.println(hasilservo);
//if (hasilservo == "kopimanis") {
//    while (it < 25) { //awal servo kopi
//      it += 1;
//      servo1.attach(10);
//      servo1.write(10);
//      delay(300);
//      servo1.attach(10);
//      servo1.write(150);
//      delay(300);
//    }
//    ///akhir servo kopi
//
//
//    while (it < 28) { //awal servo gula
//      it += 1;
//      servo3.attach(servogula);
//      servo3.write(70);
//      delay(200);
//      servo3.attach(servogula);
//      servo3.write(30);
//      delay(200);
//    } //akhir servo gula
//
////kopimanis = false;
//  } else if (hasilservo == "kopipahit") {
//    while (it < 35) { //awal servo kopi
//      it += 1;
//      servo1.attach(10);
//      servo1.write(10);
//      delay(300);
//     servo1.attach(10);
//      servo1.write(150);
//      delay(300);
// 
//    }
//    ///akhir servo kopi
//
//
//    while (it < 38) { //awal servo gula
//      it += 1;
//       servo3.attach(servogula);
//      servo3.write(70);
//      delay(200);
//      servo3.attach(servogula);
//      servo3.write(30);
//      delay(200);
//    } //akhir servo gula
//
//
//  } else if (hasilservo == "kopisedang") {
//    while (it < 30) { //awal servo kopi
//      it += 1;
//         servo1.attach(10);
//      servo1.write(10);
//      delay(300);
//      servo1.attach(10);
//      servo1.write(150);
//      delay(300);
//   
//    }
//    ///akhir servo kopi
//
//
//    while (it < 33) { //awal servo gula
//      it += 1;
//      servo3.attach(servogula);
//      servo3.write(70);
//      delay(200);
//      servo3.attach(servogula);
//      servo3.write(30);
//      delay(200);
//    } //akhir servo gula


//  }
//
//
//  else if (hasilservo == "susu") {
//
//    while (it < 5) { //awal servo susu
//      it += 1;
//
//      servo2.attach(servosusu);
//      servo2.write(180);
//      delay(200);
//      servo2.attach(servosusu);
//      servo2.write(90);
//      delay(200);
//    } //akhir servo susu
//
//
//
//    while (it < 3) { //awal servo gula
//      it += 1;
//      servo3.attach(servogula);
//      servo3.write(70);
//      delay(200);
//      servo3.attach(servogula);
//      servo3.write(30);
//      delay(200);
//    } //akhir servo gula
//
//  } else if (hasilservo == "kopisusu")
//    while (it < 11) { //awal servo susu
//      it += 1;
//
//      servo2.attach(servosusu);
//      servo2.write(180);
//      delay(200);
//      servo2.attach(servosusu);
//      servo2.write(90);
//      delay(200);
//    } //akhir servo susu
//
//
//  while (it < 20) { //awal servo kopi
//    it += 1;
//    servo1.attach(servokopi);
//    servo1.write(70);
//    delay(200);
//    servo1.attach(servokopi);
//    servo1.write(30);
//    delay(200);
//  } ///akhir servo kopi
//
//
//  while (it < 23) { //awal servo gula
//    it += 1;
//    servo3.attach(servogula);
//    servo3.write(70);
//    delay(200);
//    servo3.attach(servogula);
//    servo3.write(30);
//    delay(200);
//  } //akhir servo gula


          delay(700);
//          digitalWrite(pompaair, HIGH);
          pompa();
                  dinamomju = true; //di aktifkan jika fungsi pompa() di matikan
          it = 0;
        }///akhir mengecek input1
  
  
        if (input_2 == 1 && s_input2 == true)
        {
          dinamostp = true;
          dinamomju = false;
          Serial.print(" ");
          dinamo("stop");
          s_input2 = false;
          servoadukk();
//delay(3000);
          dinamomju = true;
        }//akhir cek input2
  
      } // akhir cek apakah ada botol
  
      else  if (sensorbtl == 0) {
        jalan = false;
        x = 0;
        it = 0;
        delay(700);
        dinamo("mundur");
  
      } //akhir cek jika botol 0
  
      if (s_input1 == false && s_input2 == false && sensorbtl == 0) {
        Serial.println("semua bernilai false");
        Wire.beginTransmission(8);
        Wire.write(1);
        Wire.endTransmission();
        jalan = false;
        x = 0;
        it = 0;
        s_input1 = true;
        s_input2 = true;
      }
  
    }//tutup  cek apakah jalan bernilai true
  //akhir rencana b

  
if(sensorbtl == 0){
  
//  dinamo("mundur");
//       x = 0;
        it = 0;
        s_input1 = true;
        s_input2 = true;
            digitalWrite(pompaair, LOW);
      }
  


}//akhir fungsi loop
//

void pompa()
{

      digitalWrite(pompaair, HIGH);
  while (statepompa == true) {
      milis = millis();
  if ((milis - oldTime) > 1000)
  {
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / 72;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    unsigned int frac;
    Serial.print("Flow rate: ");
    Serial.print(flowMilliLitres, DEC);  // Print the integer part of the variable
    Serial.print("mL/Second");
    Serial.print("\t");

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres, DEC);
    Serial.println("mL");
    Serial.print("\t");
     
       if (totalMilliLitres > 140)
    {
      digitalWrite(pompaair, LOW);
      dinamomju = true;
      statepompa = false;
//      pulseCount = 0;

    }
         pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
  
 
  }
}


void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;

}

//=======================dinamo state ====================
void dinamostate() {
  if (dinamomju == true) {
    dinamo("maju");
  }
  if (dinamomju == false) {
    dinamo("stop");
  }
  //      if{
  //
  //        }

}
//=================================================


//=========================dinamo ===================
void dinamo(String dnmo)
{
  //  Serial.println("ini dinamo ");
  if (dnmo == "maju" && dinamomju == true )
  {
    Serial.println("ini dinamo maju");
    digitalWrite(dinamomundur, LOW);
    digitalWrite(dinamomaju, HIGH);
    //    digitalWrite(dinamomundur, LOW);

  }
  else if (dnmo == "mundur" && dinamomndur == true)
  {
    //        digitalWrite(dinamomaju, HIGH);
    digitalWrite(dinamomundur, HIGH);
    digitalWrite(dinamomaju, LOW);
    Serial.println("ini dinamo mundur");

  }
  else if (dnmo == "stop" && dinamostp == true)
  {
    Serial.println("ini dinamo stop");
    digitalWrite(dinamomaju, LOW);
    digitalWrite(dinamomundur, LOW);
  }

}
//=================================================

void servo(String requesservo) {

  if (requesservo == "kopimanis") {


    while (it < 25) { //awal servo kopi
      it += 1;
      servo1.attach(10);
      servo1.write(10);
      delay(300);
      servo1.attach(10);
      servo1.write(150);
      delay(300);
    }
    ///akhir servo kopi


    while (it < 28) { //awal servo gula
      it += 1;
      servo3.attach(servogula);
      servo3.write(70);
      delay(200);
      servo3.attach(servogula);
      servo3.write(30);
      delay(200);
    } //akhir servo gula


  } else if (requesservo == "kopipahit") {
    while (it < 35) { //awal servo kopi
      it += 1;
      servo1.attach(10);
      servo1.write(10);
      delay(300);
     servo1.attach(10);
      servo1.write(150);
      delay(300);
 
    }
    ///akhir servo kopi


    while (it < 38) { //awal servo gula
      it += 1;
       servo3.attach(servogula);
      servo3.write(70);
      delay(200);
      servo3.attach(servogula);
      servo3.write(30);
      delay(200);
    } //akhir servo gula


  } else if (requesservo == "kopisedang") {
    while (it < 30) { //awal servo kopi
      it += 1;
         servo1.attach(10);
      servo1.write(10);
      delay(300);
      servo1.attach(10);
      servo1.write(150);
      delay(300);
   
    }
    ///akhir servo kopi


    while (it < 33) { //awal servo gula
      it += 1;
      servo3.attach(servogula);
      servo3.write(70);
      delay(200);
      servo3.attach(servogula);
      servo3.write(30);
      delay(200);
    } //akhir servo gula


  }


  else if (requesservo == "susu") {

    while (it < 5) { //awal servo susu
      it += 1;

      servo2.attach(servosusu);
      servo2.write(180);
      delay(200);
      servo2.attach(servosusu);
      servo2.write(90);
      delay(200);
    } //akhir servo susu



    while (it < 3) { //awal servo gula
      it += 1;
      servo3.attach(servogula);
      servo3.write(70);
      delay(200);
      servo3.attach(servogula);
      servo3.write(30);
      delay(200);
    } //akhir servo gula

  } else if (requesservo == "kopisusu")
    while (it < 11) { //awal servo susu
      it += 1;

      servo2.attach(servosusu);
      servo2.write(180);
      delay(200);
      servo2.attach(servosusu);
      servo2.write(90);
      delay(200);
    } //akhir servo susu


  while (it < 20) { //awal servo kopi
    it += 1;
    servo1.attach(servokopi);
    servo1.write(70);
    delay(200);
    servo1.attach(servokopi);
    servo1.write(30);
    delay(200);
  } ///akhir servo kopi


  while (it < 23) { //awal servo gula
    it += 1;
    servo3.attach(servogula);
    servo3.write(70);
    delay(200);
    servo3.attach(servogula);
    servo3.write(30);
    delay(200);
  } //akhir servo gula

}

void servoadukk(){
    
/////////////////servo aduk////////////////
              delay(500);
          servo4.attach(servoaduk);
          servo4.write(120); //servo ke bawah
          delay(10000);
      servo4.attach(servoaduk);
          servo4.write(70); //servo keatas
           delay(700);
           servo4.attach(servoaduk);
          servo4.write(50); //servo keatas
           delay(700);
     servo4.attach(servoaduk);
          servo4.write(0); //servo keatas
          delay(1000);
  //////////////////servo aduk
  }
