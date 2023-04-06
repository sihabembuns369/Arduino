#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini mp3;
void printDetail(uint8_t type, int value);

#define buttonA 32
#define buttonB 34
#define buttonloketA 25
#define buttonloketB 27
int nilaiAwal_a = 0;
int nilaiAwal_b = 0;
int tampung = 0;
int tampungpuluhan = 0;
#define belas 12
#define puluh 13
#define seratus 14
#define antrianA  15
#define antrianB 16
#define keloketA 17
#define keloketB 18
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
  delay(100);
mp3.begin(Serial2);
//  if (!mp3.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
//    Serial.println(F("Unable to begin:"));
//    Serial.println(F("1.Please recheck the connection!"));
//    Serial.println(F("2.Please insert the SD card!"));
//    while (true);
//  }
//  Serial.println(F("DFPlayer Mini online."));

  mp3.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  mp3.volume(18);  //Set volume value (0~30).
  mp3.volumeUp(); //Volume Up
  mp3.volumeDown(); //Volume Down
  mp3.EQ(DFPLAYER_EQ_NORMAL);
  mp3.outputDevice(DFPLAYER_DEVICE_SD);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);

   pinMode(buttonloketA, INPUT_PULLUP);
  pinMode(buttonloketB, INPUT_PULLUP);

}

void loop() {

  if (digitalRead(buttonloketA)) {
    nilaiAwal_a++;
    delay(300);
    terbilang(15,17,nilaiAwal_a);
  }else if(digitalRead(buttonloketB)){
     nilaiAwal_b++;
    delay(300);
    terbilang(16,18,nilaiAwal_b);
    }

//  Serial.println(nilaiAwal);
}

void terbilang(int antriannya , int keloket,int nilaipanggil) {
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
  }else if (nilaipanggil > 11 and nilaipanggil < 20) {
      mp3.play(antriannya);
    delay(2700);
    mp3.play(nilaipanggil - 10);
    delay(850);
    mp3.play(belas);
    delay(1350);
    mp3.play(keloket);
    delay(1000);
  }else  if (nilaipanggil == 20) {
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

}


//void berjalan(void){
////     dmd.clearScreen( true );
//   dmd.selectFont(Arial_Black_16_ISO_8859_1);
//   // Français, Österreich, Magyarország
//   const char *MSG = "Test coba a";
//   dmd.drawMarquee(MSG,strlen(MSG),(32*DISPLAYS_ACROSS)-1,0);
//   long start=millis();
//   long timer=start;
//   while(c){
//     if ((timer+30) < millis()) {
//       dmd.stepMarquee(-1,0);
//       timer=millis();
//     }
//   }
//  }
//
//  void atas(void){
//       dmd.selectFont(Arial_Black_16_ISO_8859_1);
//   // Français, Österreich, Magyarország
//   const char *MSGe = "369";
//   dmd.drawMarquee(MSGe,3,(32*DISPLAYS_ACROSS)-28,0);
//   long startr=millis();
//   long timerr=startr;
//   while(v){
//     if ((timerr+30) < millis()) {
//       dmd.stepMarquee(0,-1);
//       timerr=millis();
//     }
//     
//   }
//    }
