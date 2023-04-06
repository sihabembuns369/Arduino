
const int buzzer = D6;
const int sensor = D4;
void setup() {
  Serial.begin(9600);
pinMode(sensor,INPUT);
pinMode(buzzer,OUTPUT);

}

void loop() {
 int hasil = digitalRead(sensor);

 if(hasil == HIGH){
  digitalWrite(buzzer,HIGH);
  Serial.println("oke");
  
  }else if(hasil == LOW){
      digitalWrite(buzzer,LOW);
       Serial.println("halo");
    }
    Serial.println(hasil);
}
