
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
void setup () 
{
    Serial.begin(57600);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    Rtc.Begin(D4,D3);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//    printDateTime(compiled);
    Serial.println();
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 
}

void loop () 
{

    RtcDateTime now = Rtc.GetDateTime();
//    printDateTime(now);
    Serial.println();
    Serial.print("jam ");
    Serial.println(now.Hour());
}
//
//#define countof(a) (sizeof(a) / sizeof(a[0]))
//
//void printDateTime(const RtcDateTime& dt)
//{
//    char datestring[20];
//
//    snprintf_P(datestring, 
//            countof(datestring),
//            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
//            dt.Month(),
//            dt.Day(),
//            dt.Year(),
//            dt.Hour(),
//            dt.Minute(),
//            dt.Second() );
//    Serial.print(datestring);
//}
