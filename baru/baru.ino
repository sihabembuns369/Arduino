#include <DMD32.h> 
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_Black_16_ISO_8859_1.h"
#include "fonts/Arial_black_16.h"
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
int x = 1;
int c = 1;
int v = 1;
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
const int defaultBrightness = (15*255)/100;   
   //Timer setup
  //create a hardware timer  of ESP32
  hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void setup(void)
{  Serial.begin(115200);
  SerialBT.begin("ESP32test"); 
  Serial.println("The device started, now you can pair it with bluetooth!");
// return the clock speed of the CPU
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  
  // Use 1st timer of 4 
  // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
  timer = timerBegin(0, cpuClock, true);
  // Attach triggerScan function to our timer 
  timerAttachInterrupt(timer, &triggerScan, true);
  // Set alarm to call triggerScan function  
  // Repeat the alarm (third parameter) 
  timerAlarmWrite(timer, 300, true);

  // Start an alarm 
  timerAlarmEnable(timer);

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
 //Bluetooth device name
  dmd.setBrightness(100); //1-255
}


void loop(void)
{
 dmd.clearScreen( true );
 dmd.selectFont(Arial_Black_16);
//      dmd.drawString( 35,  1, "369", 3,GRAPHICS_OR );   // clock colon overlay on
//   delay( 1000 );
//   dmd.drawString( 35,  1, "369", 3, GRAPHICS_NOR    );   // clock colon overlay off
//   delay( 1000 );
//   dmd.drawString( 35,  1, "369", 3,GRAPHICS_OR );   // clock colon overlay on
//   delay( 1000 );
//   dmd.drawString( 35,  1, "369", 3, GRAPHICS_NOR    );   // clock colon overlay off
//   delay( 1000 );

   dmd.drawString( 47,  1, "I", 1, GRAPHICS_OR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawString( 47,  1, "I", 1, GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   
    dmd.selectFont(SystemFont5x7);
    dmd.drawString( 36,  4, "LOVE", 4, GRAPHICS_OR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawString( 36,  4, "LOVE", 4, GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );

 dmd.selectFont(Arial_Black_16);
    dmd.drawString( 45,  1, "U", 1, GRAPHICS_OR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawString( 45,  1, "U", 1, GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   
   dmd.selectFont(SystemFont5x7);
    dmd.drawString( 37,  4, "NENG", 4, GRAPHICS_OR    );   // clock colon overlay off
   delay( 1000 );
   dmd.drawString( 37,  4, "NENG", 4, GRAPHICS_NOR    );   // clock colon overlay off
   delay( 1000 );
   
   dmd.clearScreen( true );
    dmd.selectFont(Arial_Black_16);
  dmd.drawMarquee("Eneng Aku Sayang Sama Kamu",26,(32*DISPLAYS_ACROSS)-1,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
     
   }



//    dmd.clearScreen( true );
//  dmd.drawMarquee("369",3,(32*DISPLAYS_ACROSS)-28,0);
//   long start1=millis();
//   long timer1=start1;
//   boolean ret1=false;
//   while(!ret1){
//     if ((timer1+70) < millis()) {
//       ret1=dmd.stepMarquee(0,-1);
//       timer1=millis();
//     }
//     
//   }
 

}
