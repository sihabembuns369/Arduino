#include<IRremote.h>      //memasukan library
int sinyal = D4;        //pin D1 sebagai input sinyal remote
IRrecv irrecv(sinyal);  //menerjemahkan sinyal penerima IR remote
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); //mulai menerima sinyal

}

void loop() {
  if(irrecv.decode(&results)){          //jika menerima sinyal dari remote
    Serial.println(results.value,HEX);  //menampilkan sinyal remote dalam bentuk bilangan hexadesimal
    irrecv.resume();                    //nilai sinyal berikutnya
  }
}
