#include "WiFi.h"
 
void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress()); //mac adrress=9C:9C:1F:D5:89:48

}
 
void loop(){

}
