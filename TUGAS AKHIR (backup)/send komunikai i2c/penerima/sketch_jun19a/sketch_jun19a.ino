String data = "";
#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
 Wire.begin();
  Serial.begin(115200);
//  Wire.onRequest(requestEvent);  
}

void loop() {
  // put your main code here, to run repeatedly:
 Wire.requestFrom(8, 4);
  while (Wire.available() > 0)
  {
    char c = Wire.read();

    data += c;
    
  } 
    Serial.println(data);
//Serial.println(data.length());
  if(data == "halobro"){
    Serial.println("horeee");
    }
     data = "";
}
