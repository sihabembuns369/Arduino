void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}#include <DMD32.h>
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_Black_16_ISO_8859_1.h"
#include "fonts/Arial_black_16.h"

#include "BluetoothSerial.h"
#include "Adafruit_Thermal.h"

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini mp3;
void printDetail(uint8_t type, int value);

int nilaiAwal_a = 0;
int nilaiAwal_b = 0;
#define belas 12
#define puluh 13
#define seratus 14

/////////////////////////
String NomerA = "A00";
String NomerB = "B00";

String nomer_a, nomer_b; //hasil akhir yang akan di print ke bt
int nilaiA, nilaiB = 0; //untuk menampung nilai dari buttonA dan buttonB
unsigned long lalu,lalu2 ;
unsigned long waktusekarang;
bool state = false;
bool panelA = false;
///////////////////////////

///////////////////////////////
BluetoothSerial SerialBT;
Adafruit_Thermal printer(&SerialBT);
uint8_t address[6]  = {0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF};
String name = "RPP02N";
char *pin = "0000";
bool connected;
//////////////////////////////////
#define buttonA 34 //25 //14 //32
#define buttonB 32 //27 //12 //34

#define buttonloketA 25
#define buttonloketB 14

#define panggilulangA 27
#define panggilulangB 12

const char *nmr_a = "A00";
const char *nmr_b = "B00";

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
int x = 1;
int c = 1;
int v = 1;
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
const int defaultBrightness = (15 * 255) / 100;
//Timer setup
//create a hardware timer  of ESP32
hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void setup(void)
{ Serial.begin(115200);
  Serial2.begin(9600);
  mp3.begin(Serial2);
  mp3.setTimeOut(500); //Set serial communictaion time out 500ms
  mp3.volume(30);  //Set volume value (0~30).
  mp3.volumeUp(); //Volume Up
  mp3.volumeDown(); //Volume Down
  mp3.EQ(DFPLAYER_EQ_NORMAL);
  mp3.outputDevice(DFPLAYER_DEVICE_SD);

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

  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonloketA, INPUT_PULLUP);
  pinMode(buttonloketB, INPUT_PULLUP);
  pinMode(panggilulangA, INPUT_PULLUP);
  pinMode(panggilulangB, INPUT_PULLUP);

  //

  uint8_t cpuClock = ESP.getCpuFreqMHz();
  timer = timerBegin(0, cpuClock, true);
  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 300, true);
  timerAlarmEnable(timer);

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  //Bluetooth device name
  dmd.setBrightness(100); //1-255
  dmd.selectFont(Arial_Black_16_ISO_8859_1);
//  mp3.play(19);

  loketA();
  loketB();
}



void loketA() {

  dmd.selectFont(Arial_Black_16_ISO_8859_1);

  dmd.drawString( 4,  1, nmr_a, 3, GRAPHICS_NORMAL    );   // clock colon overlay off


}

void loketB() {

  dmd.selectFont(Arial_Black_16_ISO_8859_1);

  dmd.drawString( 36,  1, nmr_b, 3, GRAPHICS_NORMAL    );   // clock colon overlay off


}


void buttonAA() {
  String NomerAA = "A00";
  String nomer_aa;
  if (digitalRead(buttonA) == HIGH) {
    nilaiA++;
    //    nomer = String(nilaiA);
    if (nilaiA < 10) {
      NomerAA = + "A0";
    } else if (nilaiA >= 10 && nilaiA < 31) {
      NomerAA = + "A";
    }
    nomer_aa = NomerAA + String(nilaiA);

    printkarcis(nomer_aa); //mencetak ke printer tehermal
    delay(300);
  }

  if (nilaiA > 30) {
    nilaiA = 0;
  }

}

void buttonBB() {
  String NomerBB = "B00";
  String nomer_bb;
  if (digitalRead(buttonB) == HIGH) {
    nilaiB++;
    if (nilaiB < 10) {
      NomerBB = + "B0";
    } else if (nilaiB >= 10 && nilaiB < 31) {
      NomerBB = + "B";
    }
    nomer_bb = NomerBB + String(nilaiB);

    printkarcis(nomer_bb);
    delay(300);
  }

  if (nilaiB > 30) { //apabila nilai dari tombol b lebih dari angka 99, maka akan kembali ke 0
    nilaiB = 0;
  }

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



void terbilang(int antriannya , int keloket, int nilaipanggil) {

  if (nilaipanggil < 10) {
    mp3.play(antriannya);
    delay(2600);
    mp3.play(nilaipanggil);
    delay(965);
    mp3.play(keloket);
    delay(1000);
  } else if (nilaipanggil == 10) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(10);
    delay(900);
    mp3.play(keloket);
    delay(1000);
  } else if (nilaipanggil == 11) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(11);
    delay(950);
    mp3.play(keloket);
    delay(1000);
  } else if (nilaipanggil > 11 and nilaipanggil < 20) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(nilaipanggil - 10);
    delay(850);
    mp3.play(belas);
    delay(1350);
    mp3.play(keloket);
    delay(1000);
  } else  if (nilaipanggil == 20) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(2);
    delay(850);
    mp3.play(puluh);
    delay(1000);
    mp3.play(keloket);
    delay(1000);
  } else if (nilaipanggil > 20 and nilaipanggil < 30) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play((nilaipanggil - (nilaipanggil % 10)) / 10);
    delay(1500);
    mp3.play(puluh);
    delay(955);
    mp3.play(nilaipanggil % 10);
    delay(1000);
    mp3.play(keloket);
    delay(1000);
  } else if (nilaipanggil == 30) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(3);
    delay(1200);
    mp3.play(puluh);
    delay(1000);
    mp3.play(keloket);
    delay(1000);
  }

  Serial.print("Nilai Awal = ");
  Serial.println(nilaiAwal_a);
  if ( nilaiAwal_a > 30 or nilaiAwal_b > 30) {

    nilaiAwal_a = 0;
    nilaiAwal_b = 0;
  }
//    panelA = false;
  //  panelB = false;

}



void loop(void)
{

  buttonAA();
  buttonBB();

  if (!digitalRead(buttonA) and !digitalRead(buttonB)) {
    if (digitalRead(buttonloketA) == HIGH and nilaiAwal_a < nilaiA  ) {
      nilaiAwal_a++;
      panelA = true;
      delay(300);
      if (nilaiAwal_a < 10) {
        NomerA = + "A0";
      } else if (nilaiAwal_a >= 10 && nilaiAwal_a < 31) {
        NomerA = + "A";
      }

      nomer_a = NomerA + String(nilaiAwal_a);
      nmr_a = nomer_a.c_str();

      if (nilaiAwal_a > 30) {
        nilaiAwal_a = 0;
      }

 
      dmd.drawString( 4,  1, nmr_a, 3, GRAPHICS_NORMAL    );
      terbilang(15, 17, nilaiAwal_a);
//      panelA =false;
    }
    else if (digitalRead(buttonloketB) == HIGH and nilaiAwal_b < nilaiB ) {
      Serial.println("button loket B ok");
      nilaiAwal_b++;
      delay(300);
      if (nilaiAwal_b < 10) {
        NomerB = + "B0";
      } else if (nilaiAwal_b >= 10 && nilaiAwal_b < 31) {
        NomerB = + "B";
      }

      nomer_b = NomerB + String(nilaiAwal_b);
      nmr_b = nomer_b.c_str();

      if (nilaiAwal_b > 30) {
        nilaiAwal_b = 0;
      }
      dmd.drawString( 36,  1, nmr_b, 3, GRAPHICS_NORMAL    );   
      terbilang(16, 18, nilaiAwal_b);

    } else {
      if (digitalRead(panggilulangA) == HIGH) {
        terbilang(15, 17, nilaiAwal_a);
      } else if (digitalRead(panggilulangB) == HIGH) {
        terbilang(16, 18, nilaiAwal_b);
      }

    }
    

  }


}
