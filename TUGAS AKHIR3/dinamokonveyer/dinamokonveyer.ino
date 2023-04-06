int motorPin1 =  5;
int motorPin2 =  6;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);

}

void loop() {
  
    //This code  will turn Motor A clockwise for 2 sec.
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    //analogWrite(motorPin3, 180);
    //analogWrite(motorPin4, 0);
    delay(5000); 
    //This code will turn Motor A counter-clockwise for 2 sec.
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
////    analogWrite(motorPin3, 0);
//    analogWrite(motorPin4, 180);
    delay(5000);
    
    //This code will turn Motor B clockwise for 2 sec.
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    //analogWrite(motorPin3, 180);
    //analogWrite(motorPin4, 0);
    delay(1000); 
    //This code will turn Motor B counter-clockwise for 2 sec.
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
   // analogWrite(motorPin3, 0);
    //analogWrite(motorPin4, 180);
    delay(1000);    
    
    //And this code will stop motors
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
   // analogWrite(motorPin3, 0);
   // analogWrite(motorPin4, 0);
}
