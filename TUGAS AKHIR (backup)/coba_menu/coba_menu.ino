#include "PinChangeInterrupt.h"
#include "gambar.h"
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <Fonts/Org_01.h>
#include <EEPROM.h>
#include <Wire.h> 
bool backsensed = false;
bool resetsensed = false;
#define YP A2
#define XM A1
#define YM 6
#define XP 7
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET 0
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define BLACK 0x0000
int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GREY tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
int currentpcolour;
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define DRAW_LOOP_INTERVAL 50
#define addr 0

int x, y, z;
bool abc = true;
bool abcd = true;
bool abcde = false;
bool done = true;
bool kopi1 = false;
bool susu1 = false;
bool campur1 = false;
int get;


int harga_kopi = 3000;
int harga_susu = 4000;
int harga_campur = 6000;

unsigned long c ;


///i2c komunikasi
const char *i2c= "";
/////

unsigned long b;
int menit = 1;
int detik = 59;
bool ab =true;
String av;
////untuk coin acceptor
volatile int pulse = 0;
int koin;
void coin_value() {
  pulse = pulse + 1;
}
//akhir untuk coin acceptor


void home()
{
    if (kopi1 == true) {
        kopi1 = false;
      } else if (susu1 == true) {
        susu1 = false;
      } else if (campur1 == true) {
        campur1 = false;

      }
   
      
  harga_kopi = 3000;
  harga_susu = 4000;
  harga_campur = 6000;
  abc = true;
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 10);
  tft.print("SILAHKAN PESAN!");

  // awal kopi
  tft.setTextSize(2);
  tft.fillRoundRect(20, 180, 80, 40, 8, RED);
  tft.drawRoundRect(20, 180, 80, 40, 8, WHITE);
  tft.setCursor(35, 190);
  tft.print("kopi");
  // akhir kopi

  // awal susu
  tft.setTextSize(2);
  tft.fillRoundRect(120, 180, 80, 40, 8, RED);
  tft.drawRoundRect(120, 180, 80, 40, 8, WHITE);
  tft.setCursor(140, 190);
  tft.print("susu");
  // akhir susu

  // awal campur
  tft.setTextSize(2);
  tft.fillRoundRect(220, 180, 80, 40, 8, RED);
  tft.drawRoundRect(220, 180, 80, 40, 8, WHITE);
  tft.setCursor(225, 190);
  tft.print("campur");
  // akhir campur
  tft.drawBitmap(105, 51, koi, 117, 117, BLACK, WHITE);

}

void hitung(String abc, int harga)
{
  tft.fillScreen(BLACK);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
  //  tft.fillRoundRect(60, 180, 200, 40, 8, RED);

  tft.fillRoundRect(0, 85, 147, 40, 8, WHITE);
  tft.drawRoundRect(0, 85, 147, 150, 8, WHITE);

  tft.fillRoundRect(148, 85, 169, 40, 8, GREEN);
  tft.drawRoundRect(148, 85, 169, 150, 8, WHITE);

  tft.drawRoundRect(0, 75, 320, 60, 8, CYAN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(2, 95);
  tft.print("Anda memesan");
  tft.setCursor(157, 100);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(abc);Wire.begin(8); 

  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(10, 150);
  tft.print("silahkan\n bayar\n sebesar");

  tft.setTextSize(5);
  tft.setTextColor(GREEN);
  tft.setCursor(135  , 163);
  tft.print("=");

  ////kembali
  tft.setTextSize(2);
  tft.fillRoundRect(10, 7, 110, 30, 8, RED);
  tft.drawRoundRect(10, 7, 110, 30, 8, WHITE);
  tft.setCursor(25, 15);
  tft.print("kembali");

}


void byrr(int byar) {
  if (abc == false and abcd == false) {
    //tft.fillScreen(YELLOW);
    tft.drawRect(186, 165, 110, 40, BLACK);
    tft.fillRect(186, 165, 110, 40, BLACK);
    tft.setTextSize(3);
    tft.setCursor(185, 170);
    tft.print("Rp ");
    tft.setCursor(225, 170);
    tft.println(byar);
  }

}
void kopi(String kop)
{
  abc = false;
  tft.fillScreen(BLACK);
  hitung(kop, harga_kopi);
}


void iskopi() {
  abc = false;
  abcd = true;
  abcde = true;
  tft.fillScreen(BLACK);
  ////kembali
  tft.setTextSize(2);
  tft.fillRoundRect(10, 7, 110, 30, 8, RED);
  tft.drawRoundRect(10, 7, 110, 30, 8, WHITE);
  tft.setCursor(25, 15);
  tft.print("kembali");
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 49);
  tft.print("KOPI  Seperti apa yang     anda inginkan ? ");

  //kopi manis
  tft.setTextSize(2);
  tft.fillRoundRect(20, 180, 80, 40, 8, RED);
  tft.drawRoundRect(20, 180, 80, 40, 8, WHITE);
  tft.setCursor(35, 180);
  tft.print("kopi \n   manis");


  //kopi pahit
  tft.setTextSize(2);
  tft.fillRoundRect(120, 180, 80, 40, 8, RED);
  tft.drawRoundRect(120, 180, 80, 40, 8, WHITE);
  tft.setCursor(140, 180);
  tft.print("kopi \n           pahit");

  //kopi sedang
  tft.setTextSize(2);
  tft.fillRoundRect(220, 180, 80, 40, 8, RED);
  tft.drawRoundRect(220, 180, 80, 40, 8, WHITE);
  tft.setCursor(225, 180);
  tft.print(" kopi \n                   sedang");


}


void susu()
{
  abc = false;
  abcd = false;
  abcde = false;
  tft.fillScreen(BLACK);
  hitung("susu", harga_susu);
  //    bayar();

}

void campur()
{
  abc = false;
  abcd = false;
  abcde = false;
  tft.fillScreen(BLACK);
  hitung("kopi susu", harga_campur);
}

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

void koiin() {
  ////logika coin accepptor

  if (pulse > 0)
  {
    Serial.println("silahlkan bayarrrrrr");
//   av = Serial.readString();
//    int ab = av.toInt();

//    Serial.println(ab);
    delay (500);   // let the other pulses arrive

    if (pulse == 1) {
      Serial.println("500");
      harga_kopi -= 500;
      harga_susu -= 500;
      harga_campur -= 500;
      ab = 0;
    }
    if (pulse == 2  ) {
      Serial.println("1000");

      harga_kopi -= 500;
      harga_susu -= 500;
      harga_campur -= 500;
    }
    if (pulse == 4) {
      Serial.println("500");

      harga_kopi -= 1000;
      harga_susu -= 1000;
      harga_campur -= 1000;
      ab = 0;
    }

    pulse = 0;  // clear for next time

    /////akhir logika coin acceptor

  }
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

  
  void koin_expired(){
    if(ab == true){
    ab = true;
  if ((c - b) >= 1000) {
    b = c;
    if (ab = true) {
      // a++;
      detik --;
    }
  }

  if (detik >= 0 && detik <= 60) {
    if (menit >= 0) {
     // Serial.print(menit);
      //Serial.println(detik);
      //Serial.print(" lagi");
      //sprintf(abc , "%02d:%02d", menit, detik);
      //PRINT("\nwaktu berjalan ", abc);
      tft.setTextSize(2);
    tft.setCursor(160, 3);
    tft.print("waktu tersisa");
    
  tft.drawRect(190, 30, 88, 40, BLACK);
    tft.fillRect(190, 30,88, 40,BLACK);
    
    tft.setTextSize(3);
    tft.setCursor(199, 40);
    tft.print(menit);
    tft.setTextSize(6);
    tft.setCursor(205, 29);
    tft.print(":");
    tft.setTextSize(3);
    tft.setCursor(229, 40);
    tft.println(detik);
    } else {
      ab = false;
      detik = 0;
      menit = 0;
      Serial.print(" waktu habis ");
      home();
     // sprintf(abc , "%02d:%02d", menit, detik);
     // PRINT("\nwaktu berjalan ", abc);
    }
  }

  if (detik == 0) {
    detik = 59;
    menit --;
  }

// tft.drawRect(186, 165, 110, 40, BLACK);
//    tft.fillRect(186, 165, 110, 40, BLACK);
//    tft.setTextSize(3);
//    tft.setCursor(185, 170);
//    tft.print("Rp ");
//    tft.setCursor(225, 170);
//    tft.println(byar);
     

    }
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
