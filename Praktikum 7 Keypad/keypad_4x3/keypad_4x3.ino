#include <Keypad.h>
char tombol [4][3] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte pinBaris[] = {2,3,4,5};
byte pinKolom[] = {6,7,8,9};
Keypad keypad= Keypad(makeKeymap(tombol),pinBaris,pinKolom,4,3);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
char kode = keypad.getKey();
if(kode != NO_KEY)
Serial.println(kode);

if(kode == '1'){
  digitalWrite(LED_BUILTIN, HIGH);

  }
 else if(kode == '2'){
   digitalWrite(LED_BUILTIN, LOW);
  }
}
