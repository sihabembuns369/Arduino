#include <Servo.h>
#include <Wire.h>
//=========================== water flow=================
int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 2; //Digital Pin 2
int solenoidValve = 4; // Digital pin 5
unsigned int SetPoint = 500; //400 milileter

int x = 0;

Servo servo1;
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
char input = "";
int servosusu = 9, servokopi = 10, servogula = 11, dinamomundur = A1, dinamomaju = A2 , input1 = 12, input2 = 8, sensorbotol = 4, pompaair = 7, sensorflow = 2, servoaduk = 5, servobotol = 6;
bool maju = true, mundur = true, s_input1 = true, s_input2 = true, s_input3 = true, dinamomju = true, dinamomndur = true, dinamostp = true, servojalanstate = true, servot = true, jalan = false;



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
  /*The Hall-effect sensor is connected to pin 2 which uses interrupt 0. Configured to trigger on a FALLING state change (transition from HIGH
    (state to LOW state)*/

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  delay(100);
  //  digitalWrite(dinamomundur, LOW);
  servo3.attach(servogula);
  servo3.write(30);
  servo4.attach(servoaduk);
  servo4.write(75); //servo keatas
}
void receiveEvent(int bytes)
{
  x = Wire.read();
}

void loop()
{
  milis = millis();
  int input_1 = digitalRead(input1);
  int input_2 = digitalRead(input2);
  int sensorbtl = digitalRead(sensorbotol);
  //  int input_3 = digitalRead(input3);
  ////  Serial.print(input_1);
  //  Serial.print(digitalRead(input1));
  //  Serial.print(digitalRead(input2));
//    Serial.println(digitalRead(sensorbotol));

  //  //=======================================menerima request dari arduino master =============
  //
  //
Serial.print("sensor botol = ");
 Serial.println(sensorbtl);

if(x > 0){
  jalan = true;

  }

  Serial.print("nilai x = ");
  Serial.println(x);
  Serial.println(sensorbtl);
if(jalan == true){
  Serial.println("ada pesan masuk");
  if (sensorbtl == 1) {
    dinamo("maju");
    if (input_1 == 1 && s_input1 == true)
    {
      dinamomju = false;
      //      Serial.print("input 1 = ");
      //      Serial.println(input_1);
      Serial.println("sensor 1 terdeteksi");
      Serial.print(" ");
      dinamo("stop");
      s_input1 = false;
      dinamostp = false;
      delay(4000);
//      while(servot  == true){
////       servojalan_pesanan("kopi_manis");
//      }
      dinamomju = true;

    }
    //||==============proses peracikan minuan ===============||
    // ||                                                                                                                                    ||
    //||============================================||


    //
    if (input_2 == 1 && s_input2 == true)
    {
      dinamostp = true;
      dinamomju = false;
      //                s_input1 = false;
      //                 s_input2 = false;
      //      Serial.println(input_2);
      //         Serial.println("sensor 2 terdeteksi");
      Serial.print(" ");
      dinamo("stop");
      //      pompa();
      //      dinamo("stop");
      s_input2 = false;
      dinamostp = true;
      delay(700);

      servo4.attach(5);
  servo4.write(170); //servo ke bawah
  delay(5000);
  servo4.attach(servoaduk);
  servo4.write(75); //servo keatas
  delay(700);
     
      dinamomju = true;

      //      dinamo("maju");
    }


    }
  }
  else  if(sensorbtl == 0){
jalan = false;
 x = 0;
    delay(1500);
    dinamo("mundur");
   
        s_input1 = true;
    s_input2 = true;
//       Wire.beginTransmission(8);
//    Wire.write(1);
//    Wire.endTransmission();
//    Serial.println("kirim data k master");
  }
}
//

void pompa()
{

  //  digitalWrite(pompaair, HIGH);

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
    }

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;

    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
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

void servojalan_pesanan(String pesan) {
  if ("kopi_manis") {
    servo2.attach(servokopi);
    servo2.write(90);
    delay(500);
     servo2.attach(servokopi);
    servo2.write(30);
    delay(500);
  servo2.attach(servokopi);
    servo2.write(90);
    delay(500);
     servo2.attach(servokopi);
    servo2.write(30);
    delay(500);

    servot = false;
  } else if ("kopi_sedang") {
  } else if ("kopi_pahit") {
  } else if ("kopi_susu") {
  } else if ("susu") {
  }
}
void servojalan(String servohasil) {
  if (servohasil == "kopi" && servojalanstate == true) {
    Serial.println("halo apa kabar");
    servo1.attach(servokopi);
    servo1.write(30);
    delay(500);
    servo1.attach(servokopi);
    servo1.write(70);
    delay(500);
    //servojalanstate = false;
    //   dinamomju = true;

  }
  else  if (servohasil == "gula" && servojalanstate == true) {
    servo2.attach(servogula);
    servo2.write(30);
    delay(500);
    servo2.attach(servogula);
    servo2.write(70);
    //  delay(500);
    servojalanstate = false;
    dinamomju = true;
  }
  else  if (servohasil == "susu" && servojalanstate == true) {

    servo3.attach(servosusu);
    servo3.write(70);
    delay(500);
    servo3.attach(servosusu);
    servo3.write(70);
    delay(500);
    servojalanstate = false;
    dinamomju = true;
  }
  else {
    dinamomju = true;
  }
  //  else  if (servohasil == "kopimanis") {
  //  }
  //   else  if (servohasil == "kopisedang") {
  //  }
  //  else  if (servohasil == "susu") {
  //  }
  //   else  if (servohasil == "kopisusu") {
  //  }
}
