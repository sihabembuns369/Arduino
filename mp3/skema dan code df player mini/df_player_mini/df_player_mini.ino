#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial serial(D4, D9);
//unsigned long a = 1UL;
void setup (){
  Serial.begin(115200);
  serial.begin (9600);  
  mp3_set_serial (serial);
  delay(1);
  mp3_reset();
  mp3_stop();
  delay(5); 
  mp3_set_volume (30);
  delay(1000);
}

void loop (){  
//  unsigned long b = 60000 * a;
// mp3_set_volume (15);
//  mp3_play(1);
//  delay(10);

  if(Serial.available()>0){
    String a = Serial.readStringUntil('\n');
    if(a.equals("1")){
      Serial.print("1");
      mp3_play(1);
      delay(10);
      } else if(a.equals("2")){
         Serial.print("2");
      mp3_play(2);
      delay(10);
      }else if(a.equals("3")){
         Serial.print("3");
      mp3_play(3);
      delay(10);
      }else if(a.equals("4")){
         Serial.print("4");
      mp3_play(5);
      delay(10);
      }
    
    }
   
//  mp3_prev();
//  delay(10000);
//  mp3_pause();
//  delay(10000);
//  mp3_play();
//  delay(10000);
//  mp3_stop();
//  delay(5000);
}
