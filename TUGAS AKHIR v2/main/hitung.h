

#include <Wire.h> 




void hitung(String abc, int harga)
{
  tft.fillScreen(BLACK);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
  //  tft.fillRoundRect(60, 180, 200, 40, 8, RED);

  tft.fillRoundRect(0, 85, 147, 40, 8, WHITE);
  tft.drawRoundRect(0, 85, 147, 150, 8, WHITE);

  tft.fillRoundRect(148, 85, 169, 40, 8, GREEN);
  tft.drawRoundRect(148, 85, 169, 150, 8, WHITE);

  tft.drawRoundRect(0, 75, 320, 60, 8, CYAN);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(2, 95);
  tft.print("Anda memesan");
  tft.setCursor(157, 100);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(abc);Wire.begin(8); 

  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(10, 150);
  tft.print("silahkan\n bayar\n sebesar");

  tft.setTextSize(5);
  tft.setTextColor(GREEN);
  tft.setCursor(135  , 163);
  tft.print("=");

  ////kembali
  tft.setTextSize(2);
  tft.fillRoundRect(10, 7, 110, 30, 8, RED);
  tft.drawRoundRect(10, 7, 110, 30, 8, WHITE);
  tft.setCursor(25, 15);
  tft.print("kembali");

}
