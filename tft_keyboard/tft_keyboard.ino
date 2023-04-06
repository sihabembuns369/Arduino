#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
//#include <stdint.h>
#include "TouchScreen.h"
MCUFRIEND_kbv tft;  
/*______End of Libraries_______*/

/*______Define LCD pins (I have asigned the default values)_______*/
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 7   // can be a digital pin
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
/*_______End of defanitions______*/

/*______Assign names to colors and pressure_______*/
#define BLACK   0x0000
#define BROWN   0x7980
#define RED     0xF800
#define ORANGE  0xFBE0
#define YELLOW  0xFFE0
#define GREEN   0x07E0
#define BLUE    0x001F
#define VIOLET  0xA81F
#define GREY    0x7BEF
#define WHITE   0xFFFF
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define LGREEN   0xAFE0


#define MINPRESSURE 10
#define MAXPRESSURE 1200
/*_______Assigned______*/

/*____Calibrate TFT LCD_____*/
#define TS_MINX 910  // left
#define TS_MINY 760  // t09
#define TS_MAXX 180  // RT
#define TS_MAXY 135  // Bot
/*______End of Calibration______*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 is the sensitivity
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); //Start communication with LCD
int i=0;
int j=0;
int a=0;
int b=0;
int c=0;
int Z=0;
boolean Caps=false;
String symbol[3][10] = {
  { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P" },
  { "A", "S", "D", "F", "G", "H", "J", "K", "L", ";" },
  { "Caps", "Z", "X", "C", "V", "B", "N", "M", ".", "<" }
};
 int X,Y;

void setup() {
  Serial.begin(9600); //Use serial monitor for debugging
  tft.reset(); //Always reset at start
  tft.begin(0x9341); // My LCD uses LIL9341 Interface driver IC
  tft.setRotation(1); // I just roated so that the power jack faces up - optional
  tft.invertDisplay(1);
  IntroScreen();
  draw_BoxNButtons(); 
  tft.setCursor(0,0);
  
  
}

void loop() {
TSPoint p = waitTouch();
tft.setCursor (a,b);
tft.setTextSize (2);
tft.setTextColor(WHITE);
DetectButtons();
delay(300);
}


TSPoint waitTouch() {
  
  TSPoint p;
  do {
    p = ts.getPoint(); 
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
  X = p.y; Y = p.x; Z=p.z;
  Serial.print(X); Serial.print(','); Serial.print(Y); Serial.print(','); Serial.println(Z);     // + " " + Y);
  return p;
}


void DetectButtons()
{

  if ( 20<X && X<45 && Y<32) //Detecting Buttons on Column 1
     { Caps = !Caps;
     Serial.print(Caps);
     a=a-12;
    if(Caps){
        tft.setCursor (275, 90);
        tft.setTextSize (1);
        tft.setTextColor(WHITE);
        tft.println("CAPS ON");
          }
    else 
      tft.fillRect (275,90,50,10,BLACK);
      delay(500);
     }
     
  else if ( 20<X && X<45 && 32<Y && Y<64)
          {       
            if (Caps)
             tft.print("Z");
            else
             tft.print("z"); 
          }
  else if ( 20<X && X<45 && 64<Y && Y<96)    
        {       
            if (Caps)
             tft.print("X");
            else
             tft.print("x"); 
          }

  else if ( 20<X && X<45 && 96<Y && Y<128)    
        {       
            if (Caps)
             tft.print("C");
            else
             tft.print("c"); 
          }

  else if ( 20<X && X<45 && 128<Y && Y<160)    
        {       
            if (Caps)
             tft.print("V");
            else
             tft.print("v"); 
          }

  else if ( 20<X && X<45 && 160<Y && Y<192)    
        {       
            if (Caps)
             tft.print("B");
            else
             tft.print("b"); 
          }
          
 else if ( 17<X && X<45 && 192<Y && Y<224)    
        {       
            if (Caps)
             tft.print("N");
            else
             tft.print("n"); 
          }

  else if ( 10<X && X<45 && 224<Y && Y<256)    
        {       
            if (Caps)
             tft.print("M");
            else
             tft.print("m"); 
          }
          
 else if ( 10<X && X<45 && 256<Y && Y<288)    
        {       
            if (Caps)
             tft.print(".");
            else
             tft.print("."); 
          }

  else if ( 3<X && X<40 && 288<Y && Y<320)    
        {       
           a=a-12;
           tft.fillRect(a,b,12,20,BLACK);
           a=a-12;
          Serial.print("a=");
          Serial.println(a);
          
          }

 else if ( 45<X && X<75 && 0<Y && Y<32)    
        {       
            if (Caps)
             tft.print("A");
            else
             tft.print("a"); 
          }
 else if ( 45<X && X<75 && 32<Y && Y<64)    
        {       
            if (Caps)
             tft.print("S");
            else
             tft.print("s"); 
          }
 else if ( 45<X && X<75 && 64<Y && Y<96)    
        {       
            if (Caps)
             tft.print("D");
            else
             tft.print("d"); 
          }
 else if ( 45<X && X<75 && 96<Y && Y<128)    
        {       
            if (Caps)
             tft.print("F");
            else
             tft.print("f"); 
          }
 else if ( 45<X && X<75 && 128<Y && Y<160)    
        {       
            if (Caps)
             tft.print("G");
            else
             tft.print("g"); 
          }
 else if ( 45<X && X<75 && 160<Y && Y<192)    
        {       
            if (Caps)
             tft.print("H");
            else
             tft.print("h"); 
          }
 else if ( 45<X && X<75 && 192<Y && Y<224)    
        {       
            if (Caps)
             tft.print("J");
            else
             tft.print("j"); 
          }
 else if ( 45<X && X<75 && 224<Y && Y<256)    
        {       
            if (Caps)
             tft.print("K");
            else
             tft.print("k"); 
          }
 else if ( 45<X && X<75 && 256<Y && Y<288)    
        {       
            if (Caps)
             tft.print("L");
            else
             tft.print("l"); 
          }
 else if ( 45<X && X<75 && 288<Y && Y<320)    
        {       
         a=-12;
         b=b+20;
          }


 else if ( 75<X && X<100 && 0<Y && Y<32)    
        {       
            if (Caps)
             tft.print("Q");
            else
             tft.print("q"); 
          }
 else if ( 75<X && X<100 && 32<Y && Y<64)    
        {       
            if (Caps)
             tft.print("W");
            else
             tft.print("w"); 
          }
 else if ( 75<X && X<100 && 64<Y && Y<96)    
        {       
            if (Caps)
             tft.print("E");
            else
             tft.print("e"); 
          }
 else if ( 75<X && X<100 && 96<Y && Y<128)    
        {       
            if (Caps)
             tft.print("R");
            else
             tft.print("r"); 
          }
 else if ( 75<X && X<100 && 128<Y && Y<160)    
        {       
            if (Caps)
             tft.print("T");
            else
             tft.print("t"); 
          }
 else if ( 75<X && X<100 && 160<Y && Y<192)    
        {       
            if (Caps)
             tft.print("Y");
            else
             tft.print("y"); 
          }
 else if ( 75<X && X<100 && 192<Y && Y<224)    
        {       
            if (Caps)
             tft.print("U");
            else
             tft.print("u"); 
          }
 else if ( 75<X && X<100 && 224<Y && Y<256)    
        {       
            if (Caps)
             tft.print("I");
            else
             tft.print("i"); 
          }
 else if ( 75<X && X<100 && 256<Y && Y<288)    
        {       
            if (Caps)
             tft.print("O");
            else
             tft.print("o"); 
          }
 else if ( 75<X && X<100 && 288<Y && Y<320)    
        {       
            if (Caps)
             tft.print("P");
            else
             tft.print("p"); 
          }
 else if ( X<8 && 224<Y && Y<320)    // Reset button
        {       
          tft.fillRect(0,0,320,100,BLACK);
          a=-12;
          b=0;
          }
          
  a=a+12;
  if(a>310)
  {b=b+20;
  a=0;
  }  


}





void IntroScreen()
{tft.fillScreen(BLACK);
  tft.setCursor (20, 30);
  tft.setTextSize (3);
  tft.setTextColor(RED);
  tft.println("ARDUINO Project");
  tft.setTextColor(YELLOW);
  tft.setCursor (30, 110);
   tft.setTextSize (2);
   tft.println("Laptop Keyboard Typing");
 tft.setTextSize (2);
  tft.setCursor (55, 180);
  tft.setTextColor(BLUE);
  tft.println("Teach Me Something");
  delay(4000);
  
}

void draw_BoxNButtons()
{     tft.fillScreen(BLACK);
     // tft.fillRect(0,135,320,105,WHITE);
      tft.setTextSize (3);
      tft.setTextColor(RED);
      for( j=0; j<3;j++)
      {
      for ( i=0; i<10; i++)
      {
      tft.fillRoundRect((i*32)+1, j*35+101, 31, 34, 3,YELLOW);
      tft.setCursor (i*32+9,j*35+107 );
      tft.print(symbol[j][i]);
      }
      }
      tft.fillRoundRect(1,171, 31, 34, 3,CYAN);
      tft.setTextColor(BLACK);
      tft.setTextSize (1);
      tft.setCursor (5,185 );
      tft.print("Caps");
      tft.fillRoundRect(289,171, 31, 34, 3,0Xfbef);
      tft.setTextColor(BLACK);
      tft.setTextSize (2);
      tft.setCursor (290,182 );
      tft.print("<-");

      tft.fillRoundRect(289,136, 31, 34, 3,CYAN);
      tft.setTextColor(RED);
      tft.setTextSize (1);
      tft.setCursor (290,150 );
      tft.print("Enter");
      
      tft.fillRoundRect(1,206, 223, 34, 3,VIOLET);
      tft.setTextColor(WHITE);
      tft.setTextSize (2);
      tft.setCursor (55,215 );
      tft.print("Space Bar");

         
      tft.fillRoundRect(225,206, 95, 34, 3,WHITE);
      tft.setTextColor(VIOLET);
      tft.setTextSize (2);
      tft.setCursor (247,217 );
      tft.print("RESET");

      while( c<5)
      {
        tft.setCursor(55,25);
        tft.setTextColor(WHITE);
        tft.setTextSize (2);   
        tft.print("Teach Me Something");
        tft.setCursor(100,60);
        tft.print("Type Here");
        delay(500);
        tft.fillRect(0,0,320,100,BLACK);
        delay(500);
        c++;
      }
   
}
