#include<IRremote.h>      //memasukan library
#define tombol_1 0xFFA25D
#define tombol_2 0xFF629D
//int sinyal = D4;        //pin D1 sebagai input sinyal remote
int lampu = D8;
uint32_t Previous;
IRrecv irrecv(D0);  //menerjemahkan sinyal penerima IR remote
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); //mulai menerima sinyal
  pinMode(D1, OUTPUT);
//  pinMode(D1,LOW);
}

void loop() {
  if(irrecv.decode(&results)){          //jika menerima sinyal dari remote  
    if(results.value==0xFFFFFFFF){
      results.value=Previous;
    }
    switch (results.value){
      case tombol_1: digitalWrite(D1, LOW); Serial.println("lampunyala"); break;
      case tombol_2: digitalWrite(D1, HIGH);  Serial.println("lampumati");  break;
    }
    Serial.println(results.value,HEX);  //menampilkan sinyal remote dalam bentuk bilangan hexadesimal
    irrecv.resume();                    //nilai sinyal berikutnya
  }

    
}
