//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <time.h>
ESP8266WebServer server(80);
const char * ssid = "Jam RGB";
const char * password = "88888888";

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <RtcDS3231.h>
#include <Wire.h>
#include <EEPROM.h>
RtcDS3231 < TwoWire > Rtc(Wire);
#include "setalarm.h"

char nama_hari[7][12] = {"sabtu", "minggu", "senen", "selasa", "rabu", "kamis", "jumat"};


void setup()
{
  
    Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
    Rtc.Begin();
  // Print a message to the LCD.
  lcd.backlight();
    server.begin(); //memulai server

     RtcDateTime manual = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(manual);
  Serial.println(manual);
  //

  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
//  
//  lcd.setCursor(0,1);
//  lcd.print("Hello, world!");

    WiFi.softAP(ssid, password);
  IPAddress apip = WiFi.softAPIP();

//  Serial.println("");
//  Serial.print("AP Name : ");
//  //  Serial.println(ssidString);
//  Serial.print("Password : ");
//  //  Serial.println(passString);
//
//  Serial.print("visit: \n");
//  Serial.println(apip);

}


void loop()
{
    RtcDateTime now = Rtc.GetDateTime();

      int hl = now.Hour() ;
  int mr = now.Minute() ;
  Serial.println( now.Minute());
}
