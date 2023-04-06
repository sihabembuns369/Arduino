#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Ganti dengan password Jaringan WiFi yang user miliki
const char* ssid = "O";
const char* password = "abcdefghij";
 
ESP8266WebServer server(80);   //Inisialisasi server pada port 80
 
const char page[] = 
"<script>" \
"strLine = \"\";" \
"function SendText()" \
"{" \
"  var kirimkenodemcu = new XMLHttpRequest();" \
"  strLine = \"&MSG=\" + document.getElementById(\"txt_form\").Message.value;" \
"  kirimkenodemcu.open(\"GET\", strLine, true);" \
"  kirimkenodemcu.send();" \
"}" \
"</script>" \
"<div id=\"container\">"\
"<form id=\"txt_form\" name=\"frmText\">" \
"<label>Message:<input type=\"text\" name=\"Message\" maxlength=\"255\"></label>%ltbr><br>" \
"</form>" \
"<br>" \
"<input type=\"submit\" value=\"Send Text\" onclick=\"SendText()\">" ;
//int LEDPin = LED_BUILTIN; //Pin yang digunakan untuk mengendalikan LED
void setup(void){
  //the HTML of the web page
//  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  //Inisialisasi pin D4 padam ketika NodeMCU pertama kali menyala
  pinMode( LED_BUILTIN, OUTPUT);
  digitalWrite( LED_BUILTIN, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
//   
//  server.on("/", [](){
//    server.send(200, "text/html", page);
//  });
//  server.on("/strLine", [](){
//    server.send(200, "text/html", page);
//    digitalWrite( LED_BUILTIN, HIGH);
//    Serial.println(strLine);
//    delay(1000);
//  });
//  server.on("/LEDOff", [](){
//    server.send(200, "text/html", page);
//    digitalWrite( LED_BUILTIN, LOW);
//    delay(1000); 
//  });


  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
