
int pinSensor = A0;
const int pinRelay = 4;
int nilai;
int nilaiSensor = 0;

void setup() {
  Serial.begin (9600);
  pinMode (pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH);
}

void loop() {
    nilaiSensor = analogRead(pinSensor);
  Serial.print ("Sensor = ");
  Serial.println(nilaiSensor);
  if (nilaiSensor > 350) {
    delay(150);
 nilai++;
    while (true) {
//      digitalWrite(pinRelay, HIGH);
     
      nilaiSensor = analogRead(pinSensor);
      if (nilaiSensor > 351) {
         Serial.println("halo");
         
        break;
       
      }
    }
    delay(150);
  }

  delay(300);
  if(nilai == 4){
    nilai = 0;
    }
    if(nilai == 1){
      digitalWrite(pinRelay,LOW);
      } else if(nilai == 3){
        digitalWrite(pinRelay,HIGH);
        }

        Serial.println(nilai);
}
