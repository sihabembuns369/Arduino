
///#include "variabel_dan_defisi.h"




void kopi(String kop)
{
  abc = false;
  tft.fillScreen(BLACK);
  hitung(kop, harga_kopi);
}


void iskopi() {
  abc = false;
  abcd = true;
  abcde = true;
  tft.fillScreen(BLACK);
  ////kembali
  tft.setTextSize(2);
  tft.fillRoundRect(10, 7, 110, 30, 8, RED);
  tft.drawRoundRect(10, 7, 110, 30, 8, WHITE);
  tft.setCursor(25, 15);
  tft.print("kembali");
  tft.setTextSize(2);
  tft.setTextColor(GREEN);
  tft.setCursor(30, 49);
  tft.print("KOPI  Seperti apa yang     anda inginkan ? ");

  //kopi manis
  tft.setTextSize(2);
  tft.fillRoundRect(20, 180, 80, 40, 8, RED);
  tft.drawRoundRect(20, 180, 80, 40, 8, WHITE);
  tft.setCursor(35, 180);
  tft.print("kopi \n   manis");


  //kopi pahit
  tft.setTextSize(2);
  tft.fillRoundRect(120, 180, 80, 40, 8, RED);
  tft.drawRoundRect(120, 180, 80, 40, 8, WHITE);
  tft.setCursor(140, 180);
  tft.print("kopi \n           pahit");

  //kopi sedang
  tft.setTextSize(2);
  tft.fillRoundRect(220, 180, 80, 40, 8, RED);
  tft.drawRoundRect(220, 180, 80, 40, 8, WHITE);
  tft.setCursor(225, 180);
  tft.print(" kopi \n                   sedang");


}


void susu()
{
  abc = false;
  abcd = false;
  abcde = false;
  tft.fillScreen(BLACK);
  hitung("susu", harga_susu);
  //    bayar();

}

void campur()
{
  abc = false;
  abcd = false;
  abcde = false;
  tft.fillScreen(BLACK);
  hitung("kopi susu", harga_campur);
}
