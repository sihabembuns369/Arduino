
//#include <Mouse.h>
#include <FastLED.h>
 //#include "RTClib.h"
#define NUM_LEDS 87
# define DATA_PIN D3
CRGB LEDs[NUM_LEDS];
//library eeprom
#include <EEPROM.h>

//librari rts ds3231
#include <Wire.h>

#include <RtcDS3231.h>

RtcDS3231 < TwoWire > Rtc(Wire);
// Change this color if you want another color, for example CRGB::Red
//CRGB color = CRGB::White;   
CRGB alternateColor = CRGB::Black;
CRGB alternateColor2 = CRGB::Black;
//RTC_DS3231 rtc;

//library wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <time.h>
#include "halaman_web.h"
#include "setwarna.h"

 //membuka server di port 80
ESP8266WebServer server(80);
const char * ssid = "Jam RGB";
const char * password = "88888888";

boolean state;
unsigned long waktu;
unsigned long waktu2;
unsigned long waktu3;
unsigned long waktulama;
byte angka1 = 0;
byte angka2 = 0;
byte angka3 = 0;
byte angka4 = 0;

//jamsekarang
int jamnya;
int menitnya;

String jam, menit, detik,cerah,aa,klike;
byte warnane;
int setcerah;
int klik, efek_1;
//int jame,menite;
// int jm,mn;

//set jam manual
int setjam;
int setmenit;
int setdetik;

 //setwarna
 int efekled;
 



byte warna1 = 0, warna2 = 0, warna3 = 0, warna4 = 0;

CRGB warna[] = {
    CRGB(255, 0, 0),
    CRGB(0, 255, 0),
    CRGB(255, 0, 0),
    CRGB(255, 255, 0),
    CRGB(0, 255, 255),
    CRGB(255, 0, 255),
    CRGB(0, 128, 0),
    CRGB(128, 0, 128),
    CRGB(0, 128, 128),
    CRGB(0, 0, 128),
};


CRGB warnaa[] = {
   CRGB(255, 0, 0),
    CRGB(0, 255, 0),
    CRGB(255, 0, 0),
    CRGB(255, 255, 0),
    CRGB(0, 255, 255),
    CRGB(255, 0, 255),
    CRGB(0, 128, 0),
    CRGB(128, 0, 128),
    CRGB(0, 128, 128),
    CRGB(0, 0, 128),
};

int kecerahan = 110;
bool a = true;

void handlejam() {
    server.send(200, "text/html", home);
}


void handlecerah() {
    String POS = server.arg("cerah");
    int pos = POS.toInt();
    FastLED.setBrightness(pos);
    Serial.print("cerahnya = ");
    Serial.println(pos);
    delay(15);
    server.send(200, "text/plane", "");
}

void handlewaktu() {
    jam = server.arg("jam");
    menit = server.arg("menit");
    detik = server.arg("detik");
    cerah = server.arg("aturcerah");

    String click = server.arg("klik");

    // int jam = jam.toInt();
    setjam = jam.toInt();
    setmenit = menit.toInt();
     setdetik = detik.toInt();
    setcerah = cerah.toInt();
    FastLED.setBrightness(100);
    Serial.print(click);
    Serial.print("menit : ");
    Serial.println(setmenit);
    Serial.print("jam : ");
    Serial.println(setjam);
       Serial.print("detik : ");
    Serial.println(setdetik);
    Serial.print("kecerahan : ");
    Serial.println(setcerah);

    //set waktu manual
    char userTime[8];
    userTime[0] = setjam / 10 + '0';
    userTime[1] = setjam % 10 + '0';
    userTime[2] = ':';
    userTime[3] = setmenit / 10 + '0';
    userTime[4] = setmenit % 10 + '0';
    userTime[5] = ':';
    userTime[6] = setdetik / 10 + '0';
    userTime[7] = setdetik % 10 + '0';
    RtcDateTime manual = RtcDateTime(__DATE__, userTime);
    Rtc.SetDateTime(manual);
    Serial.println(manual);
    //  
    //    EEPROM.write(alamatjam,setjam);
    //    EEPROM.write(alamatmenit,setmenit);
    //    EEPROM.commit();
    //    
    if (click == "1") {
        digitalWrite(D0, HIGH);
        delay(200);
        digitalWrite(D0, LOW);

    }
    // server.send(200, "application/json", "sukses");
    server.send(200, "text/html", home);
}


void handlewarna(){
server.send(200, "text/html", setwarna);  
}
    
void setting_warna(){
  aa = server.arg("warna");
   klike = server.arg("cek_warna");
  String efek1 = server.arg("efek1");

   efek_1 = efek1.toInt();
  efekled = aa.toInt();
  klik = klike.toInt();
//  String warna = server.arg("warna");
//  CRGB abcd  = warnane;
  Serial.print("klik = ");
  Serial.println(klik);

   Serial.print("efek = ");
  Serial.println(efek_1);
//  Serial.println(warna);
  server.send(200, "text/html", setwarna); 
}






void setup() {
    // Initialize LED strip
    Serial.begin(9600);
    FastLED.delay(3000);
    FastLED.setBrightness(100);

   
    FastLED.addLeds < WS2812B, DATA_PIN, GRB > (LEDs, NUM_LEDS);

    //setup wifi dengan mode acces point/p2p
    //   WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    IPAddress apip = WiFi.softAPIP();

    Serial.println("");
    Serial.print("AP Name : ");
    //  Serial.println(ssidString);
    Serial.print("Password : ");
    //  Serial.println(passString);

    Serial.print("visit: \n");
    Serial.println(apip);
    
    server.on("/", handlejam);
    server.on("/setcerah", handlecerah);
    server.on("/setjam", handlewaktu);
    
    //lingkup warna
    server.on("/setwarna", handlewarna);
    server.on("/aturwarna", setting_warna);


    server.begin(); //memulai server
    Rtc.Begin(D4, D9);

    //    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    //    printDateTime(compiled);



}



void detiknya(int startindex, CRGB color2) {

    for (int i = 0; i < 2; i++) {
        LEDs[i + startindex] = (1 << i) ? color2 : alternateColor2;
    }



}

void displayTime(int startindex, int number, CRGB color) {

    //angka di jam sesuai urutan array
    int numbers[] = {
        0b0000111111111111111111, //0
        0b0000000000000111111000, //1
        0b0111000111111000111111, //2
        0b0111000000111111111111, //3
        0b0111111000000111111000, //4
        0b0111111000111111000111, //5
        0b0111111111111111000111, //6
        0b0000000000000111111111, //7
        0b0111111111111111111111, //8
        0b0111111000111111111111, //9 
    };

    for (int i = 0; i < 21; i++) {
        LEDs[i + startindex] = ((numbers[number] & 1 << i) == 1 << i) ? color : alternateColor;
    }



}



  
void loop() {
    server.handleClient();
    RtcDateTime now = Rtc.GetDateTime();
    int hl = now.Hour() / 10;
    int hr = now.Hour() % 10;
    int ml = now.Minute() / 10;
    int mr = now.Minute() % 10;
    

    jamnya = now.Hour();
    menitnya = now.Minute();

   int hari = now.DayOfWeek();
   //buat nyimpen data alarm
int alrm[7] = {EEPROM.read(34),EEPROM.read(35),EEPROM.read(36),EEPROM.read(37),EEPROM.read(38),EEPROM.read(39),EEPROM.read(40)};

    if ((millis() - waktu) >= 50) {
        waktu = millis();
        angka4++;
        warna4++;
        if (angka4 == 10) {
            warna4 = 0;
            angka3++;
            warna3++;
            angka4 = 0;
            if (angka3 == 10) {
                warna3 = 0;
                angka2++;
                warna2++;
                angka3 = 0;
                if (angka2 == 10) {
                    warna2 = 0;
                    angka1++;
                    warna1++;
                    angka2 = 0;
                    if (angka1 == 10) {
                        warna1 = 0;
                        angka1 = 0;
                    }
                }
            }
        }

    }

    // FastLED.setBrightness(kecerahan);
    // FastLED.setBrightness(255);
    // Serial.println(kecerahan);
CRGB  warnane;
warnane = CRGB(0,255,0); //default warna hijau
// Serial.println(warnane);
 

   if(klik == 1 && efek_1 == 0){
    Serial.println("random");
    warnane = warna[warna3];
      displayTime(1, hl, warnane);
      displayTime(22, hr, warnane);
      displayTime(45, ml, warnane);
      displayTime(66, mr, warnane);
    }else if(efek_1 == 2 && klik == 0){
      Serial.println("efek");

        displayTime(1, hl, warnaa[angka4+5]);

      displayTime(22, hr, warnaa[angka4+4]);

      displayTime(45, ml,warnaa[angka4+2]);

      displayTime(66, mr, warnaa[angka4+1]);
      
      }else if(klik == 0 && efek_1 == 0){
//        Serial.println("warna");
      switch(efekled){
    case 1: //merah
    warnane = CRGB(255,0,0);
    break;
    case 2: //hijau
    warnane = CRGB(0,255,0);
    break;
    case 3: //biru
    warnane = CRGB(0,0,255);
    break;
    case 4: //kuning
    warnane = CRGB(255,255,0);
    break;
    case 5: //ungu
    warnane = CRGB(128,0,128);
    break;
    case 6: //coklat
    warnane = CRGB(165,42,42);
    break;
    case 7: //putih
    warnane = CRGB(255,255,255);
    break;
    }
              displayTime(1, hl, warnane);

              displayTime(22, hr, warnane);
              
              displayTime(45, ml, warnane);

              displayTime(66, mr, warnane);
 }

     


    if ((millis() - waktulama) >= 1000) {
        waktulama = millis();
        if (state == 0) {
            state = 1;
        } else if (state == 1) {
            state = 0;
        }
    }
    //          Serial.println(state);
    if (state == 1) {
        detiknya(43, warna[warna4+3]);

    } else if (state == 0) {
        detiknya(43, warna[warna4+3]);
    }

    FastLED.show();
    delay(1000);
  
    //alarm


  
}
