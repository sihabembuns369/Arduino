
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define relay 8
MFRC522  RFID(SS_PIN, RST_PIN);   // Create MFRC522 instance
//unsigned char  abc = "D5";
unsigned char abcd;
 String cc;
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  pinMode(relay, OUTPUT);
    digitalWrite(relay,HIGH);
  RFID.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:")); 
}

void loop()
{
 if ( ! RFID.PICC_IsNewCardPresent())
 {
 return;
 }
 if ( ! RFID.PICC_ReadCardSerial())
 {
 return;
 }

// menuliskan code RFID pada serial monitor
 Serial.print("ID :");
 String content = "";
 byte letter;

for (byte i = 0; i < RFID.uid.size; i++)
 {
// Serial.print(RFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
// Serial.print(RFID.uid.uidByte[i], HEX);
abcd = (RFID.uid.uidByte[0]);
// content.concat(String(RFID.uid.uidByte[0] < 0x10 ? " 0" : " "));
// content.concat(String(RFID.uid.uidByte[0], HEX));
// Serial.print(content);

 }
 cc =  String(abcd,HEX);
 Serial.println(cc);

 if(cc.equals("33")){
  Serial.println(" Pintu terbuka");
  digitalWrite(relay,LOW);
  }
 // menuliskan enter pada serial monitor
 Serial.println();
 // delay 2000 milidetik pembacaan data
 delay(1000);
}
