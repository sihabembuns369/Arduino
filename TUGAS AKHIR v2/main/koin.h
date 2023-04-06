
//#include "variabel_dan_defisi.h"


void koiin() {
  ////logika coin accepptor

  if (pulse > 0)
  {
    Serial.println("silahlkan bayarrrrrr");
//   av = Serial.readString();
//    int ab = av.toInt();

//    Serial.println(ab);
    delay (500);   // let the other pulses arrive

    if (pulse == 1) {
      Serial.println("500");
      harga_kopi -= 500;
      harga_susu -= 500;
      harga_campur -= 500;
      ab = 0;
    }
    if (pulse == 2  ) {
      Serial.println("1000");

      harga_kopi -= 500;
      harga_susu -= 500;
      harga_campur -= 500;
    }
    if (pulse == 4) {
      Serial.println("500");

      harga_kopi -= 1000;
      harga_susu -= 1000;
      harga_campur -= 1000;
      ab = 0;
    }

    pulse = 0;  // clear for next time

    /////akhir logika coin acceptor

  }
}
