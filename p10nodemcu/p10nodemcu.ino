//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test P10
/*
 * Original source code : https://github.com/busel7/DMDESP/blob/master/examples/TeksDiamdanJalan/TeksDiamdanJalan.ino by  busel7
 * Links to download libraries : https://github.com/busel7/DMDESP
*/

//----------------------------------------Include Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Mono5x7.h>
#include <fonts/EMSans8x16.h>

//----------------------------------------
#include <ESP8266WiFi.h>
#include <time.h>
WiFiServer server(80);
//----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 3 //--> Panel Columns
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)


int timezone = 7*3600;
int dst = 0;
bool a;
int WD = 64;

int nw = 0; 
String nww,nwh,nws,mytime;

// =======================================================================
// CHANGE YOUR CONFIG HERE:
// =======================================================================
const char* ssid     = "O";     // SSID of local network
const char* password = "abcdefghij";   // Password on network

//========================================================================VOID SETUP()
void setup() {
  
  Serial.begin(115200);
  //----------------------------------------DMDESP Setup
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(50); //--> Brightness level
  Disp.setFont(Mono5x7); //--> Determine the font used
  //----------------------------------------

   
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password); 
   while (WiFi.status() != WL_CONNECTED) 
   {
    delay(100);
    Serial.print(".");
   }
      server.begin();
     Serial.println(WiFi.localIP());
     configTime(timezone,dst,"pool.ntp.org","time.nist.gov");
     time_t now = time(nullptr);
     struct tm* p_tm = localtime(&now);
     nw = now;
     a = false;

}    

//========================================================================VOID LOOP()

void loop() {

 
  if (a==true) 
   {  
    Scrolling_Text(0, 40);         //--> Show running text "Scrolling_Text(y position, speed);"
    a = false;
   }

    Disp.setBrightness(100); 
    Disp.loop(); 
    Disp.setFont(EMSans8x16);  

    Clock_itt();   // show time
 
}
//========================================================================

//========================================================================Subroutines for scrolling Text
static char *Text[] = {"Thaimean 0897233733"};

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
    Disp.drawText(width - x, y, Text[0]);
  }  
}
//========================================================================

void Clock_itt() {
  
     time_t now = time(nullptr);
     struct tm* p_tm = localtime(&now);
        
     nwh = p_tm->tm_hour;
     nww = p_tm->tm_min;
     nws = p_tm->tm_sec;

    int v = nws.toInt();
    int va = nww.toInt();
  
  if (va < 10) {
    nww = '0'+nww;
    }
   
   if (v<10) {
      nws = '0'+nws;
    }

     mytime = nwh+":"+nww+":"+nws;

  if (v < 30) {
    a = true; 

   if (v==0) {
     
     for (int s=0; s<WD;s++) 
      {
    
               for (int j=0;j<17;j++) 
                   {
                  Disp.setPixel(s,j,0);
                   }             
      }
    }
    
  }
  else 
  {
    if (v==30) 
     { 
      for (int s=0; s<WD;s++) 
      {

                  for (int j=0;j<17;j++) 
                   {
                  Disp.setPixel(s,j,0);
                   }  
       
      }
    }
      
    a = false;
  }

     
 if (a==false)                // big clock 
  {
    Disp.setBrightness(255); 
    Disp.loop(); 
    Disp.setFont(EMSans8x16);  
    Disp.drawText(0, 0, mytime);
  }
  else      // true                   // small clock  run
  {   
    Disp.setBrightness(100); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(7, 8, mytime);
  }
}
