
// penerima
String data = "";
int servo1 = 9, servo2 = 10, servo3 = 11, servo4 = 3, dinamomundur = 6, dinamomaju = 5, input1 = 12, input2 = 13, input3 = 0, sensorbotol = 2, pompaair = 13, sensorflow = 4;
bool maju = true, mundur = true, s_input1 = true, s_input2 = true, s_input3 = true;
#include <Wire.h>
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(dinamomaju, OUTPUT);
  pinMode(dinamomundur, OUTPUT);
  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  pinMode(servo3, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  pinMode(sensorbotol, INPUT);
  pinMode(pompaair, OUTPUT);
  pinMode(sensorflow, INPUT);
  digitalWrite(dinamomaju,HIGH);
  digitalWrite(dinamomundur,HIGH);
//  Wire.begin(8);                   
//Wire.onRequest(requestEvent);  
}

void loop()
{
  

  Wire.requestFrom(8, 4); // 7 adalah alamat untuk perangkat yang akan terhubung dengan master, 10 adalah banyaknya data dalam bytes yang diterima

  //=======================================menerima request dari arduino master =============

  while (Wire.available() > 0)
  {
    char c = Wire.read();

    data += c;
  }
  //==============================================================================================

  if(data == "kopi")
  {
     digitalWrite(dinamomaju,LOW);
    digitalWrite(dinamomundur,LOW);
     delay(1500);
 digitalWrite(dinamomaju,HIGH);
    digitalWrite(dinamomundur,HIGH);
  delay(1500);
    // ketika request dari arduino master tidak kosong (ada isinya/request)
  Serial.println(data);
//    if (sensorbotol == HIGH){
      dinamo("maju");
      if (input1 == HIGH && s_input1 == true)
      {
        dinamo("stop");
        if (data == "kopimanis")
        {
          // servo untuk kopi jalan
          s_input1 = false;
        }
        else if (data == "kopisedang")
        {
          s_input1 = false;
        }
        else if (data == "kopipahit")
        {
          s_input1 = false;
        }
        else if (data == "kopisusu")
        {
          s_input1 = false;
        }
        else if (data == "susu")
        {
          s_input1 = false;
        }
        dinamo("maju");
      }

      if (input2 == HIGH && s_input2 == true)
      {
        dinamo("stop");
        pompa();
        s_input2 = false;
        dinamo("maju");
      }

      if (input3 == HIGH && s_input3 == true)
      {
        dinamo("stop"); // maju, mundur

        /// menjalakan mesin pengaduk
        Serial.println("mesin pengaduk");
        dinamo("maju");
      }

      if (s_input1 == false && s_input2 == false && s_input3 == false)
      {
        dinamo("mundur");
      }
//    }

    // int datasensor1 = digitalRead(sensor1);
    //  int datasensor2 = digitalRead(sensor2);
    //  if (digitalRead(sensor2) == 1) {
    //    delay(1000);
    //    analogWrite(dinamomundur, 240);
    //    //Serial.println("maju, sensor2");
    //  }
    //  if (digitalRead(sensor1) == 1) {
    //    delay(1000);
    //    analogWrite(dinamomaju, 240);
    //    //Serial.println("maju, sensor1");
    //  }

    // delay(500);
    data = "";
  
  }
}

void requestEvent() {   
Wire.write("selesai");  
}

void pompa()
{

  digitalWrite(pompaair, HIGH);
}

void dinamo(String dnmo)
{

  if (dnmo == "maju")
  {
    digitalWrite(dinamomaju, HIGH);
    digitalWrite(dinamomundur, LOW);
  }
  else if (dnmo == "mundur")
  {
    digitalWrite(dinamomaju, LOW);
    digitalWrite(dinamomundur, HIGH);
  }
  else if (dnmo == "stop")
  {
    digitalWrite(dinamomaju, LOW);
    digitalWrite(dinamomundur, LOW);
  }
}
