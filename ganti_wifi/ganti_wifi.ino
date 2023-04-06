#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <time.h>
ESP8266WebServer server(80);
const char * ssid = "Jam RGB";
const char * password = "88888888";

void setup() {
  EEPROM.begin(512);
    String ssidString = read_String(3);
  String passString = read_String(16);
  const char *ssid = ssidString.c_str();
  const char *password = passString.c_str();
  
 writeString(3,ssidName);
  writeString(16,passwordName);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[256]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

//void(*ku_reset)(void)=0;


void(*ku_reset)(void)=0;
