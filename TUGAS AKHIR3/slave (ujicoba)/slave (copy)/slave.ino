#include <Servo.h>
#include <Wire.h>
//=========================== water flow=================
int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 2; //Digital Pin 2
int solenoidValve = 4; // Digital pin 5
unsigned int SetPoint = 500; //400 milileter

int x = 0;

Servo servo1; //
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 72; //You can change according to your datasheet default 70

volatile byte pulseCount = 0;

float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long milis;
unsigned long oldTime = 0;
//==================================================

// penerima
String data = "";
String hasilservo;
char input = "";
int servosusu = 9, servokopi = 10, servogula = 11, dinamomundur = A1, dinamomaju = A2 , input1 = 12, input2 = 8, sensorbotol = 4, pompaair = 7, sensorflow = 2, servoaduk = 5, servobotol = 6;
bool maju = true, mundur = true, s_input1 = true, s_input2 = true, s_input3 = true, dinamomju = true, dinamomndur = true, dinamostp = true, servojalanstate = true, servot = true, jalan = false;
bool kopistate = true;
bool statepompa = true;
int it = 0;
char abc[30];
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

void setup()
{
  //  Wire.begin(8);
  //  Wire.onReceive(terimaevent);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  pinMode(dinamomaju, OUTPUT);
  pinMode(dinamomundur, OUTPUT);
  //  pinMode(servokopi, OUTPUT);
  //  pinMode(servosusu, OUTPUT);
  //  pinMode(servogula, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  //  pinMode(input3, INPUT);
  pinMode(sensorbotol, INPUT);
  pinMode(pompaair, OUTPUT);
  pinMode(sensorflow, INPUT);
  //  digitalWrite(dinamomaju, HIGH);
  //  digitalWrite(dinamomundur,  HIGH);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  //   servo1.attach(servokopi);
  //      servo2.attach(servogula);
  //         servo3.attach(servosusu);

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  delay(100);
  //  digitalWrite(dinamomundur, LOW);
  servo3.attach(servogula);
  servo3.write(30);
  servo4.attach(servoaduk); //gula
  servo4.write(75);
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
  milis = millis();
  int input_1 = digitalRead(input1);
  int input_2 = digitalRead(input2);
  int sensorbtl = digitalRead(sensorbotol);
  //  int input_3 = digitalRead(input3);
  ////  Serial.print(input_1);
  //  Serial.print(digitalRead(input1));
  //  Serial.print(digitalRead(input2));
  //  Serial.println(digitalRead(sensorbotol));

  //  //=======================================menerima request dari arduino master =============
  //
  //
  //  sprintf(abc , "%02d:%02d:%02d",input_1, input_2, sensorbtl);
  //      PRINT("\nsensor ", abc);
  //  Serial.println();
  //

  //servo("kopisusu");

  if (x > 0 || Serial.available() > 0 ) {
    Serial.println("ada pesan masuk");
    String abv = Serial.readString();
    x = abv.toInt();
    jalan = true;
//    x = 0 ;
  }


// while(jalan ==true){
//  Serial.println("jalan terdeteksi");
//  while(sensorbtl != 1 && jalan2 == false){
//       Serial.print("halo    ");
//       Serial.println(sensorbtl);
//  if(digitalRead(sensorbotol)== 1){
//        Serial.println("sensor botol1 terdeteksi");
//    jalan2 = true;
//   
//    }
//   }
// if(jalan2 == true){
// if(digitalRead(sensorbotol) ==1){
//    Serial.println("sensor botol2 terdeteksi");
//    dinamo("maju");
//  }else if(sensorbtl ==0){
//dinamo("mundur");
//  }
// }
// }



//if(sensorbtl ==0){
//  
//  dinamo("mundur");}
 
 if(jalan == true) {
   Serial.println("botol terdeteksi");
    if (sensorbtl == 1) {
      Serial.println("botol terdeteksi");
      dinamo("maju");
      if (input_1 == 1 && s_input1 == true)
      {
        dinamomju = false;
        Serial.println("sensor 1 terdeteksi");
        Serial.print(" ");
        dinamo("stop");
        s_input1 = false;
        dinamostp = false;
        delay(600);

        servo(hasilservo);
        digitalWrite(pompaair, HIGH);
        //    pompa();
        dinamomju = true;
        it = 0;

      }///akhir mengecek input1


      if (input_2 == 1 && s_input2 == true)
      {
        dinamostp = true;
        dinamomju = false;
        Serial.print(" ");
        dinamo("stop");
        s_input2 = false;
        dinamostp = true;
        /////////////////servo aduk////////////////
        delay(500);
        servo4.attach(servoaduk);
        servo4.write(170); //servo ke bawah
        delay(5000);
        servo4.attach(servoaduk);
        servo4.write(75); //servo keatas
        delay(700);
        //////////////////servo
        dinamomju = true;
      }//akhir cek input2
    } // akhir cek apakah ada botol
    
    else  if (sensorbtl == 0) {
      jalan = false;
      x = 0;
      delay(1500);
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

  //}
//
//  if(s_input1 == false && s_input2 == false && sensorbtl == 0){
//         Wire.beginTransmission(8);
//          Wire.write(1);
//          Wire.endTransmission();
//           jalan = false;
//        x = 0;
//           s_input1 = true;
//      s_input2 = true;
//      }
}
//

void pompa()
{

  //  digitalWrite(pompaair, HIGH);
  while (statepompa == true) {
    if ((milis - oldTime) > 1000)   // Only process counters once per second
    {
      // Disable the interrupt while calculating flow rate and sending the value to the host
      detachInterrupt(sensorInterrupt);

      // Because this loop may not complete in exactly 1 second intervals we calculate the number of milliseconds that have passed since the last execution and use that to scale the output. We also apply the calibrationFactor to scale the output based on the number of pulses per second per units of measure (litres/minute in this case) coming from the sensor.
      flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

      // Note the time this processing pass was executed. Note that because we've
      // disabled interrupts the millis() function won't actually be incrementing right
      // at this point, but it will still return the value it was set to just before
      // interrupts went away.
      oldTime = millis();

      // Divide the flow rate in litres/minute by 60 to determine how many litres have
      // passed through the sensor in this 1 second interval, then multiply by 1000 to
      // convert to millilitres.
      flowMilliLitres = (flowRate / 60) * 1000;

      // Add the millilitres passed in this second to the cumulative total
      totalMilliLitres += flowMilliLitres;

      unsigned int frac;

      // Print the flow rate for this second in litres / minute
      Serial.print("Flow rate: ");
      Serial.print(flowMilliLitres, DEC);  // Print the integer part of the variable
      Serial.print("mL/Second");
      Serial.print("\t");

      // Print the cumulative total of litres flowed since starting
      Serial.print("Output Liquid Quantity: ");
      Serial.print(totalMilliLitres, DEC);
      Serial.println("mL");
      Serial.print("\t");

      if (totalMilliLitres > 150)
      {
        digitalWrite(pompaair, HIGH);
        statepompa = false;
      }

      // Reset the pulse counter so we can start incrementing again
      pulseCount = 0;

      // Enable the interrupt again now that we've finished sending output
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
  int i = 0;

  if (requesservo == "kopimanis") {


    while (it < 20) { //awal servo kopi
      it += 1;
      servo1.attach(servokopi);
      servo1.write(70);
      delay(300);
      servo1.attach(servokopi);
      servo1.write(30);
      delay(300);
    }
    ///akhir servo kopi


    while (it < 25) { //awal servo gula
      it += 1;
      servo3.attach(servogula);
      servo3.write(70);
      delay(200);
      servo3.attach(servogula);
      servo3.write(30);
      delay(200);
    } //akhir servo gula


  } else if (requesservo == "kopipahit") {
    while (it < 30) { //awal servo kopi
      it += 1;
      servo1.attach(servokopi);
      servo1.write(70);
      delay(300);
      servo1.attach(servokopi);
      servo1.write(30);
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


  } else if (requesservo == "kopisedang") {
    while (it < 30) { //awal servo kopi
      it += 1;
      servo1.attach(servokopi);
      servo1.write(70);
      delay(300);
      servo1.attach(servokopi);
      servo1.write(30);
      delay(3300);
    }
    ///akhir servo kopi


    while (it < 335) { //awal servo gula
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
      servo2.write(140);
      delay(50);
      servo2.attach(servosusu);
      servo2.write(75);
      delay(100);
    } //akhir servo susu



    while (it < 10) { //awal servo gula
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
      servo2.write(140);
      delay(50);
      servo2.attach(servosusu);
      servo2.write(75);
      delay(100);
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


  while (it < 25) { //awal servo gula
    it += 1;
    servo3.attach(servogula);
    servo3.write(70);
    delay(200);
    servo3.attach(servogula);
    servo3.write(30);
    delay(200);
  } //akhir servo gula

}
