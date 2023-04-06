#include "PinChangeInterrupt.h"
#include "gambar.h"
#include "home.h"
#include "hitung.h"
#include "bayar.h"
#include "pilihanminuman.h"
#include "variabel_dan_defisi.h"
#include "koin.h"
#include "koin_expired.h"








#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <Fonts/Org_01.h>
#include <EEPROM.h>
#include <Wire.h> 

void coin_value() {
  pulse = pulse + 1;
}
//akhir untuk coin acceptor




//int bayar(int get){
//
//  while(Serial.available()>0){
//    String bayarnya = Serial.readString();
//     get = bayarnya.toInt();
////    Serial.println(get);
//    return get;
//
//    }
//  }
void tunggu() {
  abc = true;
  abcd = true;
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 10);
  tft.print("silahkan tunggu pesanan anda sedang di buat");
 double bb = 1;
 double  e = 2.7;
  for (int i = 0 ; i < 269; i++) {
    bb += 1;
 tft.drawRoundRect(15, 180, 280, 40, 8, WHITE);
    tft.fillRoundRect(bb, 188, bb, 25, 10, RED);
     tft.setTextColor(BLACK);
       tft.setTextSize(2);
     tft.setCursor(bb - 34, 182);
    //tft.print(bb/e,0);
   // tft.print("%");
 //  tft.fillRoundRect(20, 189, bb - 10 , 25, 8, BLACK);
     Serial.println(bb/e,0);
 
  }
  
 
  done = false;

}

void trimakasih() {
  abc = true;
  abcd = true;
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 10);
  tft.print("TRIMAKASIH TELAH PESAN!");
    tft.drawBitmap(105, 51, smile, 126, 118, BLACK, WHITE);
  delay(3000);
}


void setup()
{
  tft.reset();
  tft.begin(0x9341);
  Serial.begin(9600);
  Serial.println();
  

  attachPCINT(digitalPinToPCINT(10), coin_value, CHANGE);
  Wire.begin(8); 
  Serial.print("reading id...");
  delay(500);
  Serial.println(tft.readID(), HEX);
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  home();
                  
 
}


void mesin_jalan(){
  Serial.println("mesinjalan");
  }


void loop()
{

 c = millis();
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    Serial.print("\tPressure = ");
    Serial.println(p.z);


    if (p.y > 41 && p.y < 72 && p.x > 16 && p.x < 94  && abc == true) {

    //  iskopi();
      //Serial.println(get);
      Serial.println("anda memilih kopi susu");
        campur();
      campur1 = true;

    }
    else if (p.y > 41 && p.y < 72 && p.x > 120 && p.x < 194  && abc == true )
    {
      Serial.println("anda memilih susu");
      susu();
      susu1 = true;

    }

    // tombolkopi
    else if (p.y > 41 && p.y < 72 && p.x > 217 && p.x < 288  && abc == true )
    {
      Serial.println("anda memilih kopi");
        iskopi();
     // campur();
      //campur1 = true;

    }



    // pilihan kopi
    else if (p.y > 41 && p.y < 72 && p.x > 16 && p.x < 94  && abc == false && abcde == true) {

     kopi("kopi sedang");
      ab = true;
      kopi1 = true;
      abcd = false;
    }
    else if (p.y > 41 && p.y < 72 && p.x > 120 && p.x < 194  && abc == false && abcde == true)
    {
           
         kopi("kopi pahit");
       ab = true;
      kopi1 = true;
      abcd = false;

    }

    else if (p.y > 41 && p.y < 72 && p.x > 217 && p.x < 288 && abc == false && abcde == true)
    {
   
      kopi("kopi manis");
       ab = true;
      kopi1 = true;
      abcd = false;
      //Serial.println(get);
    }

    ///tombol kembali
    if (p.y > 200 && p.y < 223 && p.x > 188 && p.x < 297  && abc == false) {
      Serial.println("ini adalah tombol kembali");
      if (kopi1 == true) {
        kopi1 = false;
      } else if (susu1 == true) {
        susu1 = false;
      } else if (campur1 == true) {
        campur1 = false;

      }
      home();
      menit = 1; //mengembalikan ke nilai default
      detik = 59; //mengembalikan ke nilai default
    }


  }


  ///hitung
  if (kopi1 == true) {
    Serial.println("bayarrrrrr");

    koiin();
    byrr(harga_kopi);
    koin_expired();
    if (harga_kopi == 0) {
      ab = false;
      //mesin jalan
    kirim("kopi");
    Wire.onRequest(requestEvent); 
      if (done == true) {
        tunggu();
          mesin_jalan();
      } if (done == false) {
        trimakasih();
//         kirim(" ");
//    Wire.onRequest(requestEvent);
      }
      home();
      done = true;


    }

  }
  if (susu1 == true) {
    byrr(harga_susu);
    koiin();
     koin_expired();
    if (harga_susu == 0) {
      ab = false;
          kirim("susu");
    Wire.onRequest(requestEvent);
       if (done == true) {
        tunggu();
        //mesin jalan
      } if (done == false) {
        trimakasih();
      }
      home();
      done = true;
      
    }

  }
  if (campur1 == true) {
    byrr(harga_campur);
    koiin();
    koin_expired();
    if (harga_campur == 0) {
      ab = false;
          kirim("campur");
    Wire.onRequest(requestEvent);
    if (done == true) {
        tunggu();
        //mesin jalan
   
      } if (done == false) {
        trimakasih();
      }
      home();
      done = true;
      
    }
  }

  ////    akhir hitung

}

void kirim(const char *f){
  i2c = f;
  }   
void requestEvent() {   
Wire.write(i2c);  
}
