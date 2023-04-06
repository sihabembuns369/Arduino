#include <DMD32.h>        //
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_black_16.h"

#include<Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc (Wire);

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
int menit,detik;
String menite,detike;
const char  *print_detik = "0";
const char *print_menit = "0";
hw_timer_t * timer = NULL;
void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void setup(void) {
  uint8_t cpuClock = ESP.getCpuFreqMHz();
timer = timerBegin(0, cpuClock, true);
 timerAttachInterrupt(timer, &triggerScan, true);
   timerAlarmWrite(timer, 300, true);
    timerAlarmEnable(timer);
       dmd.clearScreen( true );

        Serial.begin(57600);
  Rtc.Begin(25,26);
  RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__);
  Rtc.SetDateTime(compiled);
}

void loop(void) {
//   RtcDateTime now = Rtc.GetDateTime();
//  menit = now.Minute();
// detik = now.Second();
// menite = String(menit);
// detike = String(detik);
// print_menit = menite.c_str();
// print_detik = detike.c_str();
//     Serial.print(menite);
//     Serial.print(" ");
//     Serial.println(detike);
  dmd.clearScreen( true );
  dmd.selectFont(Arial_Black_16);

 dmd.drawString( 0,  1, print_menit, 2, GRAPHICS_NORMAL    );
  dmd.drawString( 17,  1,print_detik, 2, GRAPHICS_NORMAL    );  

}
