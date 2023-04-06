#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini mp3;
void printDetail(uint8_t type, int value);

void setup()
{
  Serial2.begin(9600);
  Serial.begin(9600);
  delay(100);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!mp3.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  mp3.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  mp3.volume(20);  //Set volume value (0~30).
  mp3.volumeUp(); //Volume Up
  mp3.volumeDown(); //Volume Down
  
  //----Set different EQ----
  mp3.EQ(DFPLAYER_EQ_NORMAL);
//  mp3.EQ(DFPLAYER_EQ_POP);
//  mp3.EQ(DFPLAYER_EQ_ROCK);
//  mp3.EQ(DFPLAYER_EQ_JAZZ);
//  mp3.EQ(DFPLAYER_EQ_CLASSIC);
//  mp3.EQ(DFPLAYER_EQ_BASS);
  
  //----Set device we use SD as default----
//  mp3.outputDevice(DFPLAYER_DEVICE_U_DISK);
  mp3.outputDevice(DFPLAYER_DEVICE_SD);
//  mp3.outputDevice(DFPLAYER_DEVICE_AUX);
//  mp3.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  mp3.outputDevice(DFPLAYER_DEVICE_FLASH);
  
  //----Mp3 control----
//  mp3.sleep();     //sleep
//  mp3.reset();     //Reset the module
//  mp3.enableDAC();  //Enable On-chip DAC
//  mp3.disableDAC();  //Disable On-chip DAC
//  mp3.outputSetting(true, 15); //output setting, enable the output and set the gain to 15
  
//  //----Mp3 play----
//  mp3.next();  //Play next mp3
//  delay(1000);
//  mp3.previous();  //Play previous mp3
//  delay(1000);
//  mp3.play(1);  //Play the first mp3
//  delay(1000);
//  mp3.loop(1);  //Loop the first mp3
//  delay(1000);
//  mp3.pause();  //pause the mp3
//  delay(1000);
//  mp3.start();  //start the mp3 from the pause
//  delay(1000);
//  mp3.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
//  delay(1000);
//  mp3.enableLoopAll(); //loop all mp3 files.
//  delay(1000);
//  mp3.disableLoopAll(); //stop loop all mp3 files.
//  delay(1000);
//  mp3.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
//  delay(1000);
//  mp3.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
//  delay(1000);
//  mp3.stopAdvertise(); //stop advertise
//  delay(1000);
//  mp3.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
//  delay(1000);
//  mp3.loopFolder(5); //loop all mp3 files in folder SD:/05.
//  delay(1000);
//  mp3.randomAll(); //Random play all the mp3.
//  delay(1000);
//  mp3.enableLoop(); //enable loop.
//  delay(1000);
//  mp3.disableLoop(); //disable loop.
//  delay(1000);
//
//  //----Read imformation----
//  Serial.println(mp3.readState()); //read mp3 state
//  Serial.println(mp3.readVolume()); //read current volume
//  Serial.println(mp3.readEQ()); //read EQ setting
//  Serial.println(mp3.readFileCounts()); //read all file counts in SD card
//  Serial.println(mp3.readCurrentFileNumber()); //read current play file number
//  Serial.println(mp3.readFileCountsInFolder(3)); //read fill counts in folder SD:/03
}

void loop()
{
  static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    mp3.next();  //Play next mp3 every 3 second.
  }
  
  if (mp3.available()) {
    printDetail(mp3.readType(), mp3.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
