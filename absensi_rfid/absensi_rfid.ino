#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include "icon.h"
#include <WiFiClient.h>

//inisialisasi OLED
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64   
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


#define RST_PIN         D3          
#define SS_PIN          D4
byte buzzer = 2; //pin D0
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


const char* ssid = "Abcd abcd ";    //Your Wifi SSID
const char* password = "abcdefghij";   //Wifi Password
String server_addr= "192.168.0.5";  //your server address or computer IP

byte readCard[4];   
uint8_t successRead;    
String UIDCard;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);                                         // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                           // Init MFRC522 card
  Serial.println(F("Read Uid data on a MIFARE PICC:"));    //shows in serial that it is ready to read
  ShowReaderDetails();                                          // Show details of PCD - MFRC522 Card Reader details
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  
  // just intro
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(38,20);  display.println(F("ARDUCODING"));
  display.setCursor(35,35);  display.println(F("Mesin Absen"));
  display.display();
  delay(1000); 
  ConnectWIFI(); 
  delay(2000);
}

void loop() { 
  display.clearDisplay(); 
  display.drawBitmap(32, 0, cardBitmap, 68, 50, WHITE);
  display.setTextSize(1);
  display.setCursor(30,55);display.print("Tap Your Card!");
  display.display();
  successRead = getID();
 
}

uint8_t getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   
    return 0;
  }
  UIDCard ="";
  Serial.println(F("Scanned PICC's UID:"));
   
  for ( uint8_t i = 0; i < mfrc522.uid.size; i++) {  
    UIDCard += String(mfrc522.uid.uidByte[i], HEX);
  }
  UIDCard.toUpperCase(); //Capital
  Serial.print("UID:");
  Serial.println(UIDCard);
  Serial.println(F("**End Reading**"));
  digitalWrite(buzzer, HIGH);delay(200);
  digitalWrite(buzzer, LOW);delay(200);
  digitalWrite(buzzer, HIGH);delay(200);
  digitalWrite(buzzer, LOW);
  
  storeData(); //store data to DB
  delay(2000); 
  
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

void storeData(){
   if(WiFi.status() != WL_CONNECTED){
  ConnectWIFI(); //check wifi connection
   }else{
  String  massage, first_name;
  
  //equate with your Server address (computer's IP address) and your directory application
 String  url ="http://"+server_addr+"/absensi/webapi/api/create.php?uid="+UIDCard;
    HTTPClient http;  
  WiFiClient wificlient;
  
  http.begin(wificlient, url);
  int httpCode = http.GET();        //Send the GET request
  String payload; 
  Serial.print("Response: "); 
  if (httpCode > 0) {               //Check the returning code    
      payload = http.getString();   //Get the request response payload
      payload.trim();               //remove \n character
      if( payload.length() > 0 ){
         Serial.println(payload + "\n");
      }
  }
  http.end();   //Close connection  

  const size_t capacity = JSON_OBJECT_SIZE(4) + 70; //simulate your JSON data https://arduinojson.org/v6/assistant/
  DynamicJsonDocument doc(capacity);
      
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);
  
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  
  const char* waktu_res = doc["waktu"];
  String nama_res = doc["nama"]; 
  const char* uid_res = doc["uid"]; 
  String status_res = doc["status"]; 

  //char * first_name;

  for(int i = 0; i < nama_res.length(); i++){
    if(nama_res.charAt(i) == ' '){
      first_name = nama_res.substring(0, i);
      break;
    }
  }
  
  display.clearDisplay(); 
  display.drawBitmap(0, 5, userBitmap, 50, 60, WHITE);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  //Print Data 
  if (status_res == "INVALID"){
    massage = "Who are you?";
    display.setCursor(52,15);display.print(massage);
    display.setCursor(52,30);display.print(uid_res);
    display.setCursor(52,40);display.print(status_res);
  }else{
    if (status_res =="IN"){
      massage = "Welcome!";
    }
    else{
      massage = "See you!";
    }
    display.setCursor(52,15);display.print(massage);
    display.setCursor(52,30);display.print(first_name);
    display.setCursor(52,40);display.print(waktu_res);
  }
  display.display();
  delay(3000);
}
}
void ConnectWIFI(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int i=0;
    int a=0;
    while(WiFi.status() != WL_CONNECTED){ 
      Serial.print(".");
      display.clearDisplay(); 
      display.setTextSize(1);
      if (a==0){
        display.drawBitmap(52, 20, wifi_icon, 16, 16, WHITE);
        a=1;
        
      }else{
        display.drawBitmap(52, 20, wifi_icon, 16, 16, BLACK);
        a=0;
      }
      display.setCursor(25,50);display.print("Connecting ...");
      display.display();
      delay(1000); 
      ++i;
      if (i==30){
        i=0;
        Serial.println("\n Failed to Connect.");
        break;
      }    
    }
    Serial.println("\n Connected!"); 
    Serial.print("alamat ip = ");
     Serial.println(WiFi.localIP());
    display.clearDisplay(); 
    display.setTextSize(1);
    display.drawBitmap(52, 20, wifi_icon, 16, 16, WHITE);
    display.setCursor(33,50);display.print("Connected!");
    display.display();
   
    delay(2000);
  }
}


void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown),probably a chinese clone?"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
    Serial.println(F("SYSTEM HALTED: Check connections."));
    while (true); // do not go further
  }
}
