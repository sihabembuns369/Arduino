#include <FastLED.h>
//#include "RTClib.h"
#define NUM_LEDS 7
# define DATA_PIN D4
CRGB LEDs[NUM_LEDS];
CRGB alternateColor = CRGB::Black;
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
unsigned long jam;
unsigned long lalu;
int detik;
int cerah;
bool bol = true;
static byte heat[NUM_LEDS];
#define COOLING  55
#define SPARKING 120

CRGB warna[] = {
  CRGB(255, 0, 0),
  CRGB(0, 255, 0),
  CRGB(255, 0, 0),
  CRGB(255, 255, 0),
  CRGB(0, 255, 255),
  CRGB(255, 0, 255),
  CRGB(0, 128, 0),
  CRGB(128, 0, 128),
  CRGB(0, 128, 128),
  CRGB(0, 0, 128),
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  FastLED.delay(3000);
  FastLED.setBrightness(255);
  FastLED.addLeds < WS2812B, DATA_PIN, GRB > (LEDs, NUM_LEDS);


}

void loop() {
  jam = millis();
FastLED.setBrightness(cerah);
  if ((jam - lalu) > 1000) {
    lalu = jam;
    detik++;

    if (cerah <= 255 && bol == true) {
      cerah++;
      if (cerah == 255) {
        bol = false;
      }
    } else if (bol == false) {
      Serial.println("oke");
      cerah--;
      if (cerah == 0) {
        bol = true;
      }
    }

  }
  if (detik > 9) {
    detik = 0;
  }


  //    for( int i = 0; i < NUM_LEDS; i++) {
  //      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  //    }
  //
  //   if( random8() < SPARKING ) {
  //      int y = random8(7);
  //      heat[y] = qadd8( heat[y], random8(160,255) );
  //    }
  //          CRGB color;
  //    for( int j = 0; j < NUM_LEDS; j++) {
  //color = HeatColor( heat[j]);
  //
  //      }


//  Serial.println(millis());
  // put your main code here, to run repeatedly:
  displayTime(0, detik,  warna[detik]);
  FastLED.show();
  delay(1000);
  // Turn the LED on, then pause

}

void displayTime(int startindex, int number, CRGB color) {

  //angka di jam sesuai urutan array
  int numbers[] = {
    //    0b0000111111111111111111, //0
    //    0b0000000000000111111000, //1
    //    0b0111000111111000111111, //2
    //    0b0111000000111111111111, //3
    //    0b0111111000000111111000, //4
    //    0b0111111000111111000111, //5
    //    0b0111111111111111000111, //6
    //    0b0000000000000111111111, //7
    //    0b0111111111111111111111, //8
    //    0b0111111000111111111111, //9


    //0b1111110,
    //0b0110000,
    //0b1101101,
    //0b1111001,
    //0b0110011,
    //0b1011011,
    //0b1011111,
    //0b1110000,
    //0b1111111,
    //0b1111011,

    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9

  };

  for (int i = 0; i < 7; i++) {
    LEDs[i + startindex] = ((numbers[number] & 1 << i) == 1 << i) ? color : alternateColor;
  }



}
