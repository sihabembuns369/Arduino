#include "BluetoothSerial.h"
#include "Adafruit_Thermal.h"

BluetoothSerial SerialBT;
Adafruit_Thermal printer(&SerialBT);

//uint8_t address[6]  = {0x66, 0x22, 0x21, 0x67, 0x34, 0xC8};
uint8_t address[6]  = {0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF};
String name = "RPP02N";
char *pin = "0000";
bool connected;

void setup() {
  Serial.begin(115200);
   SerialBT.setPin(pin);
  SerialBT.begin("Sihab", true);
 while (!SerialBT.connected(1000)) {
 Serial.print("Menyambungan Ke");
 Serial.println(name);
      connected = SerialBT.connect(address);

      Serial.println("Menyambungkan ke Perngkat");
    }
  if (connected) {
    Serial.println("Test printer begin");
    printer.begin();        // Init printer (same regardless of serial type)


    // Set type size, accepts 'S', 'M', 'L'
    Serial.println("Set type size, accepts 'S', 'M', 'L'");
    printer.feed(1);
    printer.setSize('M');
    printer.justify('C');
    printer.println(F("Karcis Nomor Antrian:"));

    printer.feed(1);

    printer.boldOn();
    printer.justify('C');
    printer.setSize('L');
    printer.println(F("A001"));
    printer.boldOff();

    printer.feed(1);

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("Created by EMBUN'S 369"));
    printer.feed(3);

    Serial.println("Tell printer to sleep");
    printer.sleep();      // Tell printer to sleep
    delay(3000L);         // Sleep for 3 seconds

    Serial.println("MUST wake() before printing again, even if reset");
    printer.wake();       // MUST wake() before printing again, even if reset

    Serial.println("Restore printer to defaults mode");
    printer.setDefault(); // Restore printer to defaults
  }

}
void loop() {

  while(!SerialBT.connected(1000)){
      Serial.print("Menyoba menyambunngkan ulang");
    SerialBT.connect(address);
    }
}
