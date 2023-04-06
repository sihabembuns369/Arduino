bool state = false;
const int pinsensor = D7;
int bacaSensor;
void setup() {
  Serial.begin(9600);
  pinMode(pinsensor, INPUT_PULLUP);
  pinMode(D3, OUTPUT);
}

void loop() {
  bacaSensor = digitalRead(pinsensor);
  Serial.println(bacaSensor);
  if (bacaSensor == HIGH && state == false) {
    Serial.println("Pintu ada yang buka!");
    //    digitalWrite(D3, HIGH);
    buzer();
    state = true;
  }
  else if (bacaSensor == LOW) {
    state = false;
    Serial.println("Pintu tertutup.");
    digitalWrite(D3, LOW);
  }
  delay(100);
}

void buzer() {
  while (digitalRead(pinsensor) == 1) {
    Serial.println("buzer nyala 1");
    digitalWrite(D3, HIGH);
    delay(60);
    Serial.println("buzer mati 0");
    digitalWrite(D3, LOW);
    delay(40);
  }
}
