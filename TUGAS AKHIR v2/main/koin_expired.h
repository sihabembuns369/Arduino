
//#include "variabel_dan_defisi.h"
  
  void koin_expired(){
    if(ab == true){
    ab = true;
  if ((c - b) >= 1000) {
    b = c;
    if (ab = true) {
      // a++;
      detik --;
    }
  }

  if (detik >= 0 && detik <= 60) {
    if (menit >= 0) {
     // Serial.print(menit);
      //Serial.println(detik);
      //Serial.print(" lagi");
      //sprintf(abc , "%02d:%02d", menit, detik);
      //PRINT("\nwaktu berjalan ", abc);
      tft.setTextSize(2);
    tft.setCursor(160, 3);
    tft.print("waktu tersisa");
    
  tft.drawRect(190, 30, 88, 40, BLACK);
    tft.fillRect(190, 30,88, 40,BLACK);
    
    tft.setTextSize(3);
    tft.setCursor(199, 40);
    tft.print(menit);
    tft.setTextSize(6);
    tft.setCursor(205, 29);
    tft.print(":");
    tft.setTextSize(3);
    tft.setCursor(229, 40);
    tft.println(detik);
    } else {
      ab = false;
      detik = 0;
      menit = 0;
      Serial.print(" waktu habis ");
      home();
     // sprintf(abc , "%02d:%02d", menit, detik);
     // PRINT("\nwaktu berjalan ", abc);
    }
  }

  if (detik == 0) {
    detik = 59;
    menit --;
  }

// tft.drawRect(186, 165, 110, 40, BLACK);
//    tft.fillRect(186, 165, 110, 40, BLACK);
//    tft.setTextSize(3);
//    tft.setCursor(185, 170);
//    tft.print("Rp ");
//    tft.setCursor(225, 170);
//    tft.println(byar);
     

    }
  }
    
