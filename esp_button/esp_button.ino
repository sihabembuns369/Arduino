#include "BluetoothSerial.h"
#include "Adafruit_Thermal.h"
/////////////////////////
String NomerA = "A";
String NomerB = "B";
String nomer_a, nomer_b; //hasil akhir yang akan di print
int nilaiA, nilaiB = 0; //untuk menampung nilai dari buttonA dan buttonB
///////////////////////////

///////////////////////////////
BluetoothSerial SerialBT;
Adafruit_Thermal printer(&SerialBT);
uint8_t address[6]  = {0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF};
String name = "RPP02N";
char *pin = "0000";
bool connected;
//////////////////////////////////


#define buttonA 32 //25 //12 //32
#define buttonB 34 //27 //14 //34
void setup() {
  Serial.begin(115200);

  /////////////////////////// memulai koneksi ke printer thermal(bluetooth)///////////////////
  
    SerialBT.begin("ESP32test", true);    // master = true
    SerialBT.setPin(pin);
    connected = SerialBT.connect(address);
    //connected = SerialBT.connect(address);
    Serial.print("connected : ");
    Serial.println(connected);
    if (connected) {
      Serial.println("Connected Succesfully!");
    } else {
      while (!SerialBT.connected(10000)) {
        Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
      }
    }
     SerialBT.connect();
  //
  ///////////////////////////koneksi ke printer thermal(bluetooth)///////////////////
  
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
}

void loop() {
  buttonAA();
  buttonBB();

}

void buttonAA() {
  if (digitalRead(buttonA)) {
    nilaiA++;
    //    nomer = String(nilaiA);
    if (nilaiA < 10) {
      NomerA = + "A00";
    } else if (nilaiA >= 10 && nilaiA < 100) {
      NomerA = + "A0";
    }else if(nilaiA == 100){
      NomerA =+ "A";
      }
    nomer_a = NomerA + String(nilaiA);
         printkarcis(nomer_a); //mencetak ke printer tehermal
    delay(300);
  }

  if (nilaiA > 99) {
    nilaiA = 0;
  }


  Serial.println(nomer_a);
}

void buttonBB() {
  if (digitalRead(buttonB)) {
    nilaiB++;
    //    nomer = String(nilaiA);
    if (nilaiB < 10) {
      NomerB = + "B00";
    } else if (nilaiB >= 10 && nilaiB < 100) {
      NomerB = + "B0";
    }else if(nilaiB == 100){
      NomerB =+ "B";
      }
    nomer_b = NomerB + String(nilaiB);
        printkarcis(nomer_b);
    delay(300);
  }

  if (nilaiB > 99) { //apabila nilai dari tombol b lebih dari angka 99, maka akan kembali ke 0
    nilaiB = 0;
  }

  Serial.println(nomer_b);
}


void printkarcis(String karcis) { //fungsi untuk mencetak nomer antrian berdasarkan tombol A atau B

  if (digitalRead(buttonA) == HIGH or digitalRead(buttonB) == HIGH) {

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


  }
}
