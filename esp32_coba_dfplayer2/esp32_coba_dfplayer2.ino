/*
Sources:
https://www.youtube.com/watch?v=kq2RLz65_w0
https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299
https://github.com/pcbreflux/espressif/blob/master/esp32/arduino/sketchbook/ESP32_DFPlayer_full/ESP32_DFPlayer_full.ino
https://github.com/pcbreflux/espressif/blob/master/esp32/arduino/sketchbook/ESP32_DFPlayer_full/setup.png
https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
*/

#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"


HardwareSerial hwSerial(1);
DFRobotDFPlayerMini dfPlayer;
int volume = 20;



unsigned long timestamp = 0;


void setup()
{

  hwSerial.begin(9600, SERIAL_8N1, 18, 19);  // speed, type, TX, RX
  Serial.begin(115200);

  dfPlayer.begin(hwSerial);  //Use softwareSerial to communicate with mp3
  dfPlayer.setTimeOut(500); //Set serial communication time out 500ms
  dfPlayer.volume(volume);  //Set volume value (0~30).
  dfPlayer.EQ(DFPLAYER_EQ_NORMAL);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);
 
  timestamp = millis();
  dfPlayer.play(1);  //Play the first mp3

}

void loop() {
dfPlayer.play(2);  //Play the first mp3
}

String printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      return "Time Out!";
      break;
    case WrongStack:
      return "Stack Wrong!";
      break;
    case DFPlayerCardInserted:
      return "Card Inserted!";
      break;
    case DFPlayerCardRemoved:
      return "Card Removed!";
      break;
    case DFPlayerCardOnline:
      return "Card Online!";
      break;
    case DFPlayerPlayFinished:
      return "Play Finished!";
      break;
    case DFPlayerError:
      switch (value) {
        case Busy:
          return "Error: Card not found";
          break;
        case Sleeping:
          return "Error: Sleeping";
          break;
        case SerialWrongStack:
          return "Error: Get Wrong Stack";
          break;
        case CheckSumNotMatch:
          return "Error: Check Sum Not Match";
          break;
        case FileIndexOut:
          return "Error: File Index Out of Bound";
          break;
        case FileMismatch:
          return "Error: Cannot Find File";
          break;
        case Advertise:
          return "Error: In Advertise";
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
