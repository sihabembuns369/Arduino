/*
   Source:
   https://github.com/leonvandenbeukel/7-Segment-Digital-Clock

   External libraries you need:
   Adafruit RTCLib:   https://github.com/adafruit/RTClib
   FastLED:           https://github.com/FastLED/FastLED
*/
//library led rgb
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
#include "setwifi.h"
#include "setalarm.h"
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

String jam, menit, detik, cerah, aa, klike;
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

//set alarm
int set_alarm_jam ;
int set_alarm_menit;

//hari
String hariminggu ;
String harisenen ;
String hariselasa ;
String harirabu;
String harikamis;
String harijumat;
String harisabtu;
const char *abcd;

char nama_hari[7][12] = {"sabtu", "minggu", "senen", "selasa", "rabu", "kamis", "jumat"};


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

bool a = true;

//buzzer
int buzzer = D6;

void handlejam() {
  server.send(200, "text/html", home);
}


void handlecerah() {
  String POS = server.arg("cerah");
  int pos = POS.toInt();
  EEPROM.write(44, pos);
  EEPROM.commit();
  FastLED.setBrightness(EEPROM.read(44));
  Serial.print("cerahnya = ");
  Serial.println(pos);
  delay(15);
  server.send(200, "text/plane", "");
}

void handlewaktu() {
  jam = server.arg("jam");
  menit = server.arg("menit");
  detik = server.arg("detik");


  String click = server.arg("klik");

  // int jam = jam.toInt();
  setjam = jam.toInt();
  setmenit = menit.toInt();
  setdetik = detik.toInt();

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


void handlewarna() {
  server.send(200, "text/html", setwarna);
}

void setting_warna() {
  klike = server.arg("warna");
  String efek1 = server.arg("warnaa");

  efek_1 = efek1.toInt();
  klik = klike.toInt();
  //  String warna = server.arg("warna");
  //  CRGB abcd  = warnane;
  Serial.print("klik = ");
  Serial.println(klik);

  Serial.print("efek = ");
  Serial.println(efek_1);
  EEPROM.write(42, efek_1);
  EEPROM.write(43, klik);
  EEPROM.commit();

  //  Serial.println(warna);
  server.send(200, "text/html", setwarna);
}


void(*ku_reset)(void) = 0;


void handlealarm() {
  server.send(200, "text/html", setalarm);
  //  server.send(200, "text/plain",String(kecerahan).c_str());
}

void setting_alarm() {
  String jam = server.arg("jam");
  String menit = server.arg("menit");
  String alarm_state = server.arg("alarm");
  String minggu = server.arg("minggu");
  String senen = server.arg("senen");
  String selasa = server.arg("selasa");
  String rabu = server.arg("rabu");
  String kamis = server.arg("kamis");
  String jumat = server.arg("jumat");
  String sabtu = server.arg("sabtu");

  int minggu1 = minggu.toInt();
  int senen1 = senen.toInt();
  int selasa1 = selasa.toInt();
  int rabu1 = rabu.toInt();
  int kamis1 = kamis.toInt();
  int jumat1 = jumat.toInt();
  int sabtu1 = sabtu.toInt();
  int alarm_state1 = alarm_state.toInt();
  set_alarm_jam = jam.toInt();
  set_alarm_menit = menit.toInt();
  //simpan waktu alam kedalam eeprom
  EEPROM.write(30, set_alarm_jam);
  EEPROM.write(32, set_alarm_menit);

  //simpan hari kedalam alarm
  EEPROM.write(34, minggu1);
  EEPROM.write(35, senen1);
  EEPROM.write(36, selasa1);
  EEPROM.write(37, rabu1);
  EEPROM.write(38, kamis1);
  EEPROM.write(39, jumat1);
  EEPROM.write(40, sabtu1);
  EEPROM.write(41, alarm_state1);
  EEPROM.commit();


  // Serial.println(EEPROM.read(34));
  //   Serial.println(EEPROM.read(35));
  //  Serial.println(EEPROM.read(36));
  //     Serial.println(EEPROM.read(37));
  //     Serial.println(EEPROM.read(38));
  //       Serial.println(EEPROM.read(39));
  //       Serial.println(EEPROM.read(40));

  server.send(200, "text/html", setalarm);
}


void handlewifi() {
  server.send(200, "text/html", setwifi);
}


void setting_wifi() {
  String ssidName = server.arg("wifi");
  String passwordName = server.arg("password");

  writeString(3, ssidName);
  Serial.print("SSID : ");
  Serial.println(ssidName);
  delay(500);
  writeString(16, passwordName);
  Serial.print("Password : ");
  Serial.println(passwordName);

  Serial.println(ssidName);
  Serial.println( passwordName);
  server.send(200, "text/plane", "");
  delay(1000);
  ku_reset();
}




void setup() {
  // Initialize LED strip
  Serial.begin(9600);
  FastLED.delay(3000);
  FastLED.setBrightness(100);
  pinMode(buzzer, OUTPUT);
  EEPROM.begin(512);
  String ssidString = read_String(3);
  String passString = read_String(16);
  const char *ssid = ssidString.c_str();
  const char *password = passString.c_str();
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

  //lingkup wifi
  server.on("/setwifi", handlewifi);
  server.on("/aturwifi", setting_wifi);

  //lingkup alarm
  server.on("/setalarm", handlealarm);
  server.on("/aturalarm", setting_alarm);

  //    server.on("/setwifi", handleForm);
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


void writeString(char add, String data)
{
  int _size = data.length();
  int i;
  for (i = 0; i < _size; i++)
  {
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.write(add + _size, '\0');
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[256]; //Max 100 Bytes
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < 500)
  {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}

//void(*ku_reset)(void)=0;




void loop() {
  server.handleClient();
  RtcDateTime now = Rtc.GetDateTime();
  int hl = now.Hour() / 10;
  int hr = now.Hour() % 10;
  int ml = now.Minute() / 10;
  int mr = now.Minute() % 10;
  FastLED.setBrightness(EEPROM.read(44));

  jamnya = now.Hour();
  menitnya = now.Minute();

  int hari = now.DayOfWeek();
  //buat nyimpen data alarm
  int alrm[7] = {EEPROM.read(34), EEPROM.read(35), EEPROM.read(36), EEPROM.read(37), EEPROM.read(38), EEPROM.read(39), EEPROM.read(40)};

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
  //warnane = CRGB(0, 255, 0); //default warna hijau
  // Serial.println(warnane);

  //klik == 0 and efek1 == 1
  if (EEPROM.read(43) == 1 && EEPROM.read(42) == 1) {
    Serial.println("random");
    warnane = warna[warna3];

    displayTime(1, hl, warnane);
    displayTime(22, hr, warnane);
    displayTime(45, ml, warnane);
    displayTime(66, mr, warnane);
  } else if (EEPROM.read(42) == 2 && EEPROM.read(43) == 1) { //efek1 == 2 and klik == 0
    Serial.println("efek");

    displayTime(1, hl, warnaa[angka4 + 5]);

    displayTime(22, hr, warnaa[angka4 + 4]);

    displayTime(45, ml, warnaa[angka4 + 2]);

    displayTime(66, mr, warnaa[angka4 + 1]);

  } else if (EEPROM.read(43) > 0 && EEPROM.read(42) == 0 ) { // klik == 0 and efek1 == 0

           Serial.println("warna");
    switch (EEPROM.read(43)) {
      case 1: //merah
        warnane =  CRGB(0, 255, 0);
        break;
      case 2: //hijau
        warnane = CRGB(255, 0, 0);
        break;
      case 3: //biru
        warnane = CRGB(0, 0, 255);
        break;
      case 4: //kuning
        warnane = CRGB(255, 255, 0);
        break;
      case 5: //ungu
        warnane = CRGB(128, 0, 128);
        break;
      case 6: //coklat
        warnane = CRGB(165, 42, 42);
        break;
      case 7: //putih
        warnane = CRGB(255, 255, 255);
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
    detiknya(43, warna[warna4 + 3]);

  } else if (state == 0) {
    detiknya(43, warna[warna4 + 3]);
  }

  FastLED.show();
  delay(1000);

  //alarm


  if (EEPROM.read(30) == jamnya and EEPROM.read(32) == menitnya and EEPROM.read(41) == 1 and alrm[now.DayOfWeek()] == hari) {
    Serial.println("alarm nyala");
    digitalWrite(buzzer, HIGH);

  } else {
    digitalWrite(buzzer, LOW);
  }

  Serial.println(alrm[now.DayOfWeek()]);

  Serial.println(now.DayOfWeek());
  Serial.println(nama_hari[now.DayOfWeek()]);
}
