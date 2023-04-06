#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
#include <WiFiClient.h>
#define triggerPin  D6
#define echoPin     D5

const char* ssid = "Salaf Putra";    //Your Wifi SSID
const char* password = "ngaji123";   //Wifi Password

//#ifndef STASSID
//#define STASSID "Salaf Putra"
//#define STAPSK  "ngaji123"
//#endif
String server_addr = "padangebulan.000webhostapp.com/"; //your server address or computer IP
WiFiClient client;
void setup() {
  
  
  Serial.begin(57600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop() {
//    ESP.wdtDisable();
  long duration;
  int jarak;
        digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = (duration / 2) / 29.1;
  Serial.println("jarak :");
  Serial.print(jarak);
  Serial.println(" cm");
    //equate with your Server address (computer's IP address) and your directory application
    String  url = "http://" + server_addr + "/add.php?data_sensor=" + jarak;

      WiFiClient wificlient;
     HTTPClient http;
    http.begin(wificlient, url);
    http.GET();        //Send the GET request
//    String payload;
//    Serial.print("Response: ");
//    if (httpCode > 0) {               //Check the returning code
//      payload = http.getString();   //Get the request response payload
//      payload.trim();               //remove \n character
//      if ( payload.length() > 0 ) {
//        Serial.println(payload + "\n");
//      }
//    }
//    http.end();   //Close connection



}
