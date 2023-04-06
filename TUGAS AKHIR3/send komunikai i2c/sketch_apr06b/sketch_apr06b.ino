
//pengirim
#include <Wire.h>  
const char *abc= "";
void setup() {   
                   
//Wire.onRequest(requestEvent);  

}   
void loop() {  
  Wire.begin(7); 
delay(100); 

c("halobro");
Wire.onRequest(requestEvent); 
}  
void c(const char *a){
  abc = a;
  }   
void requestEvent() {   
Wire.write(abc);  
}
