#include "variabel_dan_defisi.h"






void home()
{
    if (kopi1 == true) {
        kopi1 = false;
      } else if (susu1 == true) {
        susu1 = false;
      } else if (campur1 == true) {
        campur1 = false;

      }
   
      
  harga_kopi = 3000;
  harga_susu = 4000;
  harga_campur = 6000;
  abc = true;
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 10);
  tft.print("SILAHKAN PESAN!");

  // awal kopi
  tft.setTextSize(2);
  tft.fillRoundRect(20, 180, 80, 40, 8, RED);
  tft.drawRoundRect(20, 180, 80, 40, 8, WHITE);
  tft.setCursor(35, 190);
  tft.print("kopi");
  // akhir kopi

  // awal susu
  tft.setTextSize(2);
  tft.fillRoundRect(120, 180, 80, 40, 8, RED);
  tft.drawRoundRect(120, 180, 80, 40, 8, WHITE);
  tft.setCursor(140, 190);
  tft.print("susu");
  // akhir susu

  // awal campur
  tft.setTextSize(2);
  tft.fillRoundRect(220, 180, 80, 40, 8, RED);
  tft.drawRoundRect(220, 180, 80, 40, 8, WHITE);
  tft.setCursor(225, 190);
  tft.print("campur");
  // akhir campur
  tft.drawBitmap(105, 51, koi, 117, 117, BLACK, WHITE);

}
