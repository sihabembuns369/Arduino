int sensor = D1;
int relay = D2;
void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

}

void loop() {
  int nilai = digitalRead(sensor);

  if (nilai == 1) {

    digitalWrite(relay, LOW);
    Serial.println("nyala");


  } else {

    digitalWrite(relay, HIGH);
    Serial.println("mati");
  }
  Serial.print("nilai = ");

  Serial.println(nilai);
}
