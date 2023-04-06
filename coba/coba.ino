#include <ESP8266WiFi.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>

const int WIDTH = 1;
const uint8_t *FONT = Arial14; //jenis font yang digunakan

const char *MESSAGE = "ARDUCODING.COM";

SPIDMD dmd(WIDTH,1);  //SPIDMD pengaturan koneksi dengan nodemcu
DMD_TextBox box(dmd,0,2);  

void setup() {
  Serial.begin(9600);
  dmd.setBrightness(255);
  dmd.selectFont(FONT);
  dmd.begin();
}

void loop() {
  const char *next = MESSAGE;
  while(*next) {
    Serial.print(*next);
    box.print(*next);
    delay(300);
    next++;
  }
  delay(600);
  dmd.fillScreen(true);
  delay(500);
  dmd.clearScreen();
  delay(500);
  box.clear();
}
