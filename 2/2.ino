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
void setup() {
  // put your setup code here, to run once:
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(50); //--> Brightness level
  Disp.setFont(Arial_Black_16_ISO_8859_1); //--> Determine the font used
}


void loop() { 
    Disp.loop(); 
      Disp.setBrightness(255); 
    Disp.setFont(Arial_Black_16_ISO_8859_1);  
//    Disp.drawText(7, 8, mytime);
     
     Scrolling_Text(0, 50);
 
}

static char *Text[] = {"HANYA UJI COBA SAJA"};

void Scrolling_Text(int y, uint8_t scrolling_speed) {
  static uint32_t pM;
  static uint32_t x;  int width = Disp.width();
  Disp.setFont(Arial_Black_16_ISO_8859_1);
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
    Disp.drawText(width - x, y, Text[0]);
  }  
}
