
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Mono5x7.h>
#include <fonts/EMSans8x16.h> //bold/tebal
#include <Arial_Black_16_ISO_8859_1.h>
//----------------------------------------
#include <ESP8266WiFi.h>
#include <time.h>
#define DISPLAYS_WIDE 3 //--> jumlah panel
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

RtcDS3231<TwoWire> Rtc(Wire);

SoftwareSerial serial(D1, D2);

char jamtampil[16];
char menittampil[16];
char detiktampil[16];
int menit;

void setup() {
  
  Serial.begin(57600);
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(255); //--> Brightness level
  Disp.setFont(Arial_Black_16_ISO_8859_1); //--> Determine the font used

  serial.begin (9600);
  mp3_set_serial (serial);
  delay(1);
  mp3_reset();
  mp3_stop();
  delay(5); 
  mp3_set_volume (30);
  delay(1000);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    Rtc.Begin(D4,D9);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//    printDateTime(compiled);
    Serial.println();
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}


void loop() { 

  
  if(Serial.available()>0){
    String a = Serial.readStringUntil('\n');
    if(a.equals("1")){
      Serial.print("1");
      mp3_play(1);
      delay(10);
      } else if(a.equals("2")){
         Serial.print("2");
      mp3_play(2);
      delay(10);
      }else if(a.equals("3")){
         Serial.print("3");
      mp3_play(3);
      delay(10);
      }else if(a.equals("4")){
         Serial.print("4");
      mp3_play(5);
      delay(10);
      }
    
    }
    
   RtcDateTime now = Rtc.GetDateTime();
    Disp.loop();
int jam = now.Hour();
int menit = now.Minute();
int detik = now.Second();
int hari = now.Second();
int tahun = now.Second();
int bulan = now.Second();

//jam
String jame = String(jam);
jame.toCharArray(jamtampil,16);

//menit
String menite = String(menit);
menite.toCharArray(menittampil,16);


////detike
//String detike = String(detik);
//detike.toCharArray(detiktampil,16);
//
//// jam
//     Serial.println(now.Hour());/
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(1, 0, jamtampil);

// menit
//     Serial.println(now.Hour());/
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(19, 0, menittampil);


//detik
//     Serial.println(now.Hour());
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(32, 0, detiktampil);

     Scrolling_Text(0, 50);

     Serial.println(menit);
void suara();
     

   
 
}

static char *Text[] = {"HANYA UJI COBA SAJA"};

void Scrolling_Text(int y, uint8_t scrolling_speed) {
  static uint32_t pM;
  static uint32_t x;  int width = Disp.width();
  Disp.setFont(Mono5x7);
 // Disp.setFont(ElektronMart6x8);
  
  int fullScroll = Disp.textWidth(Text[0]) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, 9, Text[0]);
  }  
}
//
//void suara(){
//  if( menit == 33){
//       Serial.print("1");
//      mp3_play(1);
//      delay(10);
//      
//      }
//
//  
//
//  }
