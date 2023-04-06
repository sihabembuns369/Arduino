#include<Wire.h>
#include <RtcDS3231.h>
#define pinbtnA 35
#define pinbtnB 32
RtcDS3231<TwoWire> Rtc (Wire);

#include "BluetoothSerial.h"
#include "Adafruit_Thermal.h"
uint8_t jam, menit, detik;
BluetoothSerial SerialBT;
Adafruit_Thermal printer(&SerialBT);
uint8_t address[6]  = {0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF};
String name = "RPP02N";
char *pin = "0000";
bool connected;
void btkonek() {

  SerialBT.begin("ESP32test", true);    // master = true
  SerialBT.setPin(pin);
  connected = SerialBT.connect(address);
  //connected = SerialBT.connect(address);
  Serial.print("connected : ");
  Serial.println(connected);
  if (connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while (!SerialBT.connected(5000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
  SerialBT.connect();
  delay(100);
}


void printkarcis(String karcis) { //fungsi untuk mencetak nomer antrian berdasarkan tombol A atau B

  //  if (digitalRead(pinbtnA) == HIGH or digitalRead(pinbtnB) == HIGH) {

  Serial.println("mencetak karcis");
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  printer.feed(1);
  printer.setSize('M');
  printer.justify('C');
  printer.println(F("Karcis Nomor Antrian:"));

  printer.feed(1);

  printer.boldOn();
  printer.justify('C');
  printer.setSize('L');
  printer.println(karcis);
  printer.boldOff();

  printer.feed(1);

  printer.justify('C');
  printer.setSize('S');
  printer.println(F("Created by EMBUN'S 369"));
  printer.feed(3);

  printer.sleep();      // Tell printer to sleep
  delay(500L);         // Sleep for 3 seconds

  Serial.println("MUST wake() before printing again, even if reset");

  Serial.println("Restore printer to defaults mode");


  //  }
}
void setup() {
  Serial.begin(115200);
  Rtc.Begin(21, 22);
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  pinMode(pinbtnA, INPUT_PULLUP);
  pinMode(pinbtnB, INPUT_PULLUP);


  SerialBT.begin("ESP32test", true);    // master = true
  SerialBT.setPin(pin);
  while (!SerialBT.connected(5000)) {
    connected = SerialBT.connect(address);
    SerialBT.connect(address);
    Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
  }

  delay(100);
  if (connected) {
    Serial.println("ngeprint");
    printkarcis("b");
  }
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  jam = now.Hour();
  menit = now.Minute();
  detik = now.Second();

  //     Serial.print(now.Minute());
  //     Serial.print(" ");
  //     Serial.println(now.Second());

  Serial.println(digitalRead(pinbtnA));
  Serial.println(digitalRead(pinbtnB));

}
