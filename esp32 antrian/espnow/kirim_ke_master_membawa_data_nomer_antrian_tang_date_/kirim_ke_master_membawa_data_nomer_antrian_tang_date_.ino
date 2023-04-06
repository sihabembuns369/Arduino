
#include <esp_now.h>
#include <WiFi.h>
#include<Wire.h>
#include <RtcDS3231.h>
#define pinbtnA 35
#define pinbtnB 32
RtcDS3231<TwoWire> Rtc (Wire);
uint8_t jam, menit, detik;
#include "BluetoothSerial.h"
#include "TPrinter.h"
#include <Arduino.h>

BluetoothSerial SerialBT;
const int printerBaudrate = 9600;  // or 19200 usually

const byte dtrPin = 4;  // if used
uint8_t address[6]  = {0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF};
String name = "RPP02N";
char *pin = "0000"; 
bool connected;

Tprinter myPrinter(&SerialBT, printerBaudrate);
// you can assign here other stream like Serial1, Serial2, Serial3 etc


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xE7, 0xC7, 0x8C};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {

  int butonA;
  int butonB;
//  uint8_t jam;
//  uint8_t menit;
//  uint8_t detik;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  // Serial.begin(115200);

    micros();
  Serial.begin(9600);  

  Rtc.Begin(21, 22);
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  pinMode(pinbtnA, INPUT_PULLUP);
  pinMode(pinbtnB, INPUT_PULLUP);

                                        // monitor
 
  myPrinter.begin();                                          // you can edit what be happen in Tprinter.cpp, like delay time(2s)
  myPrinter.enableDtr(dtrPin, LOW);    
                    

  SerialBT.setPin(pin);
  SerialBT.begin("Sihab", true);
 while (!SerialBT.connected(5000)) {
    connected = SerialBT.connect(address);
    SerialBT.connect(address);
    Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
  }
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
    myPrinter.justify('C');
  myPrinter.println("center");
  myPrinter.justify('R');
  myPrinter.println("right");
  myPrinter.justify('L');
  myPrinter.println("left");

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // RtcDateTime now = Rtc.GetDateTime();
 
  // // Set values to send
  myData.jam = now.Hour();
  myData.menit = now.Minute();
  myData.detik = now.Second();
   myPrinter.printFromSerial();
  // Send message via ESP-NOW
 esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  delay(2000);
}
