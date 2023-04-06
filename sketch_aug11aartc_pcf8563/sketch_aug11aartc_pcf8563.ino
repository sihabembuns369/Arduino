#include "Wire.h"
#define PCF8563address 0x51
 
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
 
byte bcdToDec(byte value){
  return ((value / 16) * 10 + value % 16);
}
 
byte decToBcd(byte value){
  return (value / 10 * 16 + value % 10);
}
 
void setPCF8563(){
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.write(decToBcd(second));  
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));     
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(dayOfWeek));  
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}
 
void readPCF8563(){
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(PCF8563address, 7);
  second     = bcdToDec(Wire.read() & B01111111); 
  minute     = bcdToDec(Wire.read() & B01111111); 
  hour       = bcdToDec(Wire.read() & B00111111); 
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek  = bcdToDec(Wire.read() & B00000111);  
  month      = bcdToDec(Wire.read() & B00011111);  
  year       = bcdToDec(Wire.read());
}
 
void setup(){
  Wire.begin();
  Serial.begin(9600);
  // change the following to set your initial time
  second = 0;
  minute = 28;
  hour = 9;
  dayOfWeek = 2;
  dayOfMonth = 13;
  month = 8;
  year = 13;
  setPCF8563();
}
 
void loop(){
  readPCF8563();
  Serial.print(days[dayOfWeek]); 
  Serial.print(" ");  
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/20");
  Serial.print(year, DEC);
  Serial.print(" - ");
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");  
  if (second < 10){
    Serial.print("0");
  }  
  Serial.println(second, DEC);  
  delay(1000);
}
