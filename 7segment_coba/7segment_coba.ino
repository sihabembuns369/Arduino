#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "TM1637.h"

#define CLK D7   
#define DIO D8
TM1637 tm1637(CLK, DIO);

const char *ssid     = "CANGKIR TERAKHIR";
const char *password = "gudanggaram";

const long utcOffsetInSeconds = 25200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

int hh, mm, ss;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
 Serial.print ( "tersambung" );
  timeClient.begin();
  tm1637.init();
  tm1637.set(7);
}

void loop() {
  timeClient.update();
  hh = timeClient.getHours();
  mm = timeClient.getMinutes();
  ss = timeClient.getSeconds();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(hh);
  Serial.print(":");
  Serial.print(mm);
  Serial.print(":");
  Serial.println(ss);
  Serial.println(timeClient.getFormattedTime());
  tm1637.point(POINT_OFF);
tm1637.display(0, hh / 10);  // hour
  tm1637.display(1, hh % 10);
  tm1637.display(2, mm / 10); // minutes
  tm1637.display(3, mm % 10); //
  delay(500);
  tm1637.point(POINT_ON);
  tm1637.display(0, hh / 10);  // hour
  tm1637.display(1, hh % 10);
  tm1637.display(2, mm / 10); // minutes
  tm1637.display(3, mm % 10); //
  delay(500);
}
