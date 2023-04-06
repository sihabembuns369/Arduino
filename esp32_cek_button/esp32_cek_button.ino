
#define buttonA  34
#define buttonB 32

#define buttonC 25
#define buttonD 27


#define buttonE 14
#define buttonF 12

void setup() {
  Serial.begin(9600);

  pinMode(buttonA,INPUT_PULLUP);
  pinMode(buttonB,INPUT_PULLUP);
  pinMode(buttonC,INPUT_PULLUP);
  pinMode(buttonD,INPUT_PULLUP);
  pinMode(buttonE,INPUT_PULLUP);
  pinMode(buttonF,INPUT_PULLUP);
  // put your setup code here, to run once:

}

void loop() {

  if(digitalRead(buttonA) == HIGH){
    Serial.println("button A ok");
    }else  if(digitalRead(buttonB) == HIGH){
    Serial.println("button B ok");
    }
    else  if(digitalRead(buttonC) == HIGH){
    Serial.println("button C ok");
    }else  if(digitalRead(buttonD) == HIGH){
    Serial.println("button D ok");
    }
    
    
    else  if(digitalRead(buttonE) == HIGH){
    Serial.println("button E ok");
    }else  if(digitalRead(buttonF) == HIGH){
    Serial.println("button F ok");
    }

}
