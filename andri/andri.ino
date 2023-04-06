int trig_pin = 6;
int echo_pin = 7;
int kipas = 8;
int duration = 0;
int distance = 0;
void setup() {
   Serial.begin(9600);
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);  
  pinMode(kipas,OUTPUT);

}

void loop() {

 digitalWrite(trig_pin, HIGH);
delayMicroseconds(1000);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin , HIGH);
  distance = (duration/2) / 29.1 ;
  Serial.print(distance);
  Serial.println(" cm");

  if(distance >= 5 and distance <= 100){
    digitalWrite(kipas,LOW);
    Serial.println("nyala");
    }else if(distance > 100){
       Serial.println("mati");
      digitalWrite(kipas,HIGH);
      }

}
