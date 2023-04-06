//#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <MCUFRIEND_kbv.h>
//#include <stdint.h>
#include "TouchScreen.h"
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
int hasil =0;
String hasil2 = "Tawar" ;
int x, y, z;
int i = 0;
int j = 0;
int a = 0;
int b = 0;
int c = 0;
int Z = 0;
boolean Caps = false;
String symbol[3][10] = {
  { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P" },
  { "A", "S", "D", "F", "G", "H", "J", "K", "L", ";" },
  { "Caps", "Z", "X", "C", "V", "B", "N", "M", ".", "<" }
};
int X, Y;

void setup() {
  Serial.begin(9600); //Use serial monitor for debugging
  tft.reset(); //Always reset at start
  tft.begin(0x9341); // My LCD uses LIL9341 Interface driver IC
  tft.setRotation(1); // I just roated so that the power jack faces up - optional
  //  tft.invertDisplay(1);
  //  IntroScreen();
  //  draw_BoxNButtons();
  //  tft.setCursor(0,0);
  tft.fillScreen(BLACK);
  tft.fillRoundRect(20, 180, 250, 10, 8, RED);
  tft.fillRoundRect(20, 165, 20, 40, 8, GREEN);
  //  tft.drawRoundRect(120, 180, 80, 40, 8, WHITE);


}

void loop() {
  TSPoint p = ts.getPoint();
  tspoint(p);
  //coba();
  //Serial.write(100);
}

void tspoint(TSPoint p) {
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //   tft.drawRect(100, 160, 110, 40, BLACK);
  //   tft.fillRect(100, 160, 110, 40, BLACK);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
    X = p.y; Y = p.x; Z = p.z;
    //    tft.fillScreen(BLACK);
    if (Y > 261) {
      Y = 260;
    }
    tft.fillRect(1, 135, 340, 70, BLACK);


    hasil =  Y / 2.6;
    if (hasil > 0 && hasil < 30) {
      hasil2 = "Tawar";
    } else if (hasil > 45 && hasil < 60) {
      hasil2 = "Sedang";
    } else if (hasil > 60 && hasil < 70) {
      hasil2 = "Manis";
    } else if (hasil > 70 && hasil < 100) {
      hasil2 = "Manis Banget";
    }

if(hasil == 100){
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.setCursor(Y - 18, 155);
    tft.print(hasil);
     tft.setCursor(Y +22, 155);
    tft.print("%");
}else{
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.setCursor(Y, 155);
    tft.print(hasil);
     tft.setCursor(Y + 27, 155);
    tft.print("%");
   }
    //         tft.setTextSize(2);
    if (Y > 182) {
      tft.setTextColor(GREEN);
      tft.setCursor(Y - 100, 138);
      tft.print(hasil2);
    } else {
      tft.setTextColor(GREEN);
      tft.setCursor(Y, 138);
      tft.print(hasil2);
    }
    tft.fillRoundRect(20, 180, 260, 10, 8, RED);
    tft.fillRoundRect(Y, 174, 20, 20, 8, GREEN);

    Serial.print("X = ");
    Serial.print(X);   Serial.print(" ");
    Serial.print("y = ");
    Serial.print(Y);    Serial.print(" ");
    Serial.print("Z = ");
    Serial.println(Z);     // + " " + Y);

    //  Serial.write(X);
  }


}


void coba() {
  //  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.fillRoundRect(10, 7, 110, 30, 8, RED);
  tft.drawRoundRect(10, 7, 110, 30, 8, WHITE);
  tft.setCursor(25, 15);
  tft.print("kembali");
}
