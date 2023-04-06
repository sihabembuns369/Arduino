#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
const char *ssid = "CANGKIR";
const char *password = "123456789";
ESP8266WebServer server(80);
void writeString(char add,String data);
String read_String(char add);


const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h2>eNZet Asy Project<h2>
<h3>Ganti SSID dan Password ESP8266/ NodeMCU / Wemos </h3>

<form action="/action_page">
  SSID Name :<br>
  <input type="text" name="ssid_name" value="">
  <br>
  Password AP :<br>
  <input type="text" name="password_name" value="">
  <br><br>
  <input type="submit" value="Simpan-Restart">
</form> 

</body>
</html>
)=====";


IPAddress local_ip(192,168,4,100);
IPAddress gateway(192,168,4,100);
IPAddress subnet(255,255,255,0);



void(*ku_reset)(void)=0;

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleForm() {
 String ssidName = server.arg("ssid_name"); 
 String passwordName = server.arg("password_name"); 
 writeString(3,ssidName);
 Serial.print("SSID : ");
 Serial.println(ssidName);
 delay(500);
 writeString(5,passwordName);
 Serial.print("Password : ");
 Serial.println(passwordName);
 delay(1000);
 String s = "<a href='/'> Berhasil </a>";
 server.send(200, "text/html", s); //Send web page
 delay(1000);
 ku_reset();
}

void setup(void){
  Serial.begin(115200);
  EEPROM.begin(512);
  String ssidString = read_String(3);
  String passString = read_String(5);
  const char *ssid = ssidString.c_str();
  const char *password = passString.c_str();
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ssid", "password");
//  WiFi.softAPConfig(local_ip, gateway, subnet);/
   IPAddress apip = WiFi.softAPIP();
  delay(100);

  Serial.println("");
  Serial.print("AP Name : ");
  Serial.println(ssidString);
  Serial.print("Password : ");
  Serial.println(passString);
  Serial.print("IP address: ");
  Serial.println("192.168.4.100");  
 
  server.on("/", handleRoot);      
  server.on("/action_page", handleForm); 

  server.begin();                  
  Serial.println("HTTP server started");
  EEPROM.begin(512);
  //String data = read_String(10);
  //Serial.println(data);
}


void loop(void){
  server.handleClient();          
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
