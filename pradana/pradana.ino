#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
unsigned long waktu_lama;
unsigned long waktu_sekarang;
unsigned long detik;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int lampu =  13;
void setup() {
Serial.begin(9600);
     Serial.println("lampu nyala");
servo.attach(2);
 servo.write(0);
dht.begin();
lcd.init();
lcd.backlight();
pinMode(lampu,OUTPUT);
lcd.setCursor(1,0);
lcd.print("PENETAS TELUR");
lcd.setCursor(4,1);
lcd.print("OTOMATIS");
    digitalWrite(lampu, HIGH);
delay(3000);
lcd.clear();
}

void loop() {
  waktu_sekarang = millis();
  
//delay(500);
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
lcd.setCursor(0,3);
lcd.print("Sensor Eror");
return;
}

//lcd.clear();
lcd.setCursor(0,0);
lcd.print("suhu");
lcd.setCursor(5,0);
lcd.print(t);
lcd.setCursor(10,0);
lcd.print("c");
lcd.setCursor(0,1);
lcd.print("kelembaban");
lcd.setCursor(11,1);
lcd.print(h);

Serial.print("suhu = ");
Serial.println(t);
Serial.print("temperatur = ");
Serial.println(h);
if (t <= 37.5 and h >= 60){
    digitalWrite(lampu, LOW);
     Serial.println("lampu nyala");
//     lcd.setCursor(0,1);
//      lcd.print("s\uhu normal");
  }
  else if (t >= 39.05){
    digitalWrite(lampu, HIGH);
    Serial.println("lampu mati");
    lcd.setCursor(0,1);
      lcd.print("lampu mati, suhu naik");
  }

  
//servo berputar setiap 30 menit sekali
if((waktu_sekarang-waktu_lama) >=1000){
  detik++;
  waktu_lama = waktu_sekarang;
  if(detik == 601){
    detik = 0;
    }

  if(detik == 300){
    servo.write(190);
    }else if(detik == 600){
      servo.write(0);
      }
  }



    Serial.print("detik ke ");
  Serial.println(detik);
//    Serial.println(h);
//      Serial.println(t);

}
