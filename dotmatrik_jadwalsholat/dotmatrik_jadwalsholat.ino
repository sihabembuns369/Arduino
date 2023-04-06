#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment tergantung tipe modul
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Penentuan pin serial
#define MAX_DEVICES 4
#define DATA_PIN D5
#define CS_PIN D6
#define CLK_PIN D7


// Membuat objek
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  // Memulai object
  myDisplay.begin();

  // Mengatur intensitas (0-15)
  myDisplay.setIntensity(15); //mengatur kecerahan

  // Membersihkan tampilan
  myDisplay.displayClear(); //membersihkan kecerahan
}

void loop() {
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print("Left");
  delay(2000);
  
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.print("Center");
  delay(2000);

  myDisplay.setTextAlignment(PA_RIGHT);
  myDisplay.print("Right");
  delay(2000);

  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setInvert(true);
  myDisplay.print("Invert");
  delay(2000);

  myDisplay.setInvert(false);
  myDisplay.print(1234);
  delay(2000);


  
}
