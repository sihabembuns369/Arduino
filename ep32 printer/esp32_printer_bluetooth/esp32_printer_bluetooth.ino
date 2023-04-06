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
  SerialBT.begin("ESP32test", true);    // master = true
    SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
  connected = SerialBT.connect(address);
  //connected = SerialBT.connect(address);
  Serial.print("connected : ");
  Serial.println(connected);
  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();

  if(connected){
      Serial.println("Test printer begin");
      printer.begin();        // Init printer (same regardless of serial type)

      // Test inverse on & off
      Serial.println("Test inverse on & off");
      printer.inverseOn();
      printer.println(F("Inverse ON"));
      printer.inverseOff();
    
      // Test character double-height on & off
      Serial.println("Test character double-height on & off");
      printer.doubleHeightOn();
      printer.println(F("Double Height ON"));
      printer.doubleHeightOff();
    
      // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
      Serial.println("Set text justification (right, center, left) -- accepts 'L', 'C', 'R'");
      printer.justify('R');
      printer.println(F("Right justified"));
      printer.justify('C');
      printer.println(F("Center justified"));
      printer.justify('L');
      printer.println(F("Left justified"));
    
      // Test more styles
      Serial.println("Test more styles");
      printer.boldOn();
      printer.println(F("Bold text"));
      printer.boldOff();
    
      printer.underlineOn();
      printer.println(F("Underlined text"));
      printer.underlineOff();


      // Set type size, accepts 'S', 'M', 'L'
      Serial.println("Set type size, accepts 'S', 'M', 'L'");
      printer.setSize('L');        
      printer.println(F("Large"));
      printer.setSize('M');
      printer.println(F("Medium"));
      printer.setSize('S');
      printer.println(F("Small"));
    
      printer.justify('C');
      printer.println(F("normal\nline\nspacing"));
      printer.setLineHeight(50);
      printer.println(F("Taller\nline\nspacing"));
      printer.setLineHeight(); // Reset to default
      printer.justify('L');
    
      // Barcode examples:
      Serial.println("Barcode examples");
      // CODE39 is the most common alphanumeric barcode:
      printer.printBarcode("ADAFRUT", CODE39);
      printer.setBarcodeHeight(100);
      // Print UPC line on product barcodes:
      printer.printBarcode("123456789123", UPC_A);
      printer.feed(2);
      
      printer.println(F("TytoMulyono.com"));
      printer.feed(2);
      printer.println(F("YouTube.com/TytoMulyono"));
      printer.feed(2);
      printer.println(F("Facebook.com/Tyto.Mulyono"));
      printer.feed(2);
      printer.println(F("Instagram.com/TytoMulyono"));
      printer.feed(2);
      printer.println(F("For Business WA 085220851888"));
      printer.feed(2);
      
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
  Serial.println("Looping...");
  printer.println(F("Looping..."));
  printer.feed(1);
  printer.println(F("TytoMulyono.com"));
  printer.feed(2);
  delay(20000);
}
