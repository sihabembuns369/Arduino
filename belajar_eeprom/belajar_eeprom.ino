#include <EEPROM.h>//https://github.com/esp8266/Arduino/blob/master/libraries/EEPROM/EEPROM.h

//Constants
#define EEPROM_SIZE 255
 int address = 0;
void setup() {
  pinMode(D0,OUTPUT);
  //Init Serial USB
  Serial.begin(115200);
  Serial.println(F("Initialize System"));
  //Init EEPROM
  EEPROM.begin(EEPROM_SIZE);
//  String halo = "ccc";
//  //Write data into eeprom
//  EEPROM.put(address, halo);
//  EEPROM.commit();
//
//     String data;
//  EEPROM.get(address, data); //readParam=EEPROM.readFloat(address);
//  Serial.print("Read param = ");
//  Serial.println(data);
  

}

void loop() {
//  tone(D0,10);
//  delay(500);
  
  if(Serial.available()>0){
    String data = Serial.readString();
     Serial.print("data dari serial = ");
     Serial.println(data);
     
   //Write data into eeprom
//   static char *Text[255];
     EEPROM.put(address, data); //alamateeprom, data yang akan disimpan di eeprom
     EEPROM.commit(); //fungsi untuk menyimpan kedalam eeprom
     //Read data from eeprom
//    EEPROM.end();
    }
    
 String da;
  EEPROM.get(address, da); ///mendapatkan alamat eeprom dan data
  Serial.print("Read param = ");
  Serial.println(da);
  delay(600);
//
//  char *abc;
//  strcpy(abc, da.c_str()); 
//   Serial.print("data abc = ");
//  Serial.println(abc);
  

  
  }
