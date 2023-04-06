#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//the pin you connect the ds18b20 to
#define DS18B20 12
#define relayheater 11
OneWire ourWire(DS18B20);
DallasTemperature sensors(&ourWire);

void setup()
{
Serial.begin(9600);
delay(1000);
//start reading
sensors.begin();
pinMode(relayheater, OUTPUT);
//digitalWrite(relayheater,HIGH);
  lcd.init(); // initialize the lcd
  lcd.backlight();

 
}

void loop()
{
//read temperature and output via serial
sensors.requestTemperatures();
Serial.print(sensors.getTempCByIndex(0));
Serial.println("degrees C");
 lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Temperatur");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print(sensors.getTempCByIndex(0)); // print message at (2, 1)
if(sensors.getTempCByIndex(0) > 95.00){
  digitalWrite(relayheater,HIGH); //relay mati
  }else{
    digitalWrite(relayheater,LOW); //relay hidup
    }
}
