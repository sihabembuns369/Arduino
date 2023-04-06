#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN D3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

// Set these to run example.
#define FIREBASE_HOST "embuns369-3d076-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "2xQBiEuNWGZADEAzYhuoaD9yjxzH3pHl7vimWOQk"
#define WIFI_SSID "Unwaha Hotspot"
#define WIFI_PASSWORD ""

void setup() {
  Serial.begin(9600);
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {

  int r = Firebase.getInt("r");
   int g = Firebase.getInt("g");
    int b = Firebase.getInt("b");
     Serial.print("r = ");
  Serial.println(r);
  Serial.print("g = ");
  Serial.println(g);
  Serial.print("b = ");
  Serial.println(b);
  Serial.print("");
  leds[0] = CRGB(r, g, b);
  FastLED.show();
}
