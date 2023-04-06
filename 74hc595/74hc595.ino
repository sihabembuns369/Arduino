int datapin = D3;
int latchpin = D2;
int clockpin = D1;
String a;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
}

// 00000011 //0
// 10011111 //1
// 00100101 //2
// 00001101  //3
// 10011001  //4
// 01001001 //5
// 01000001 //6
// 00011111 //7
// 00000001//8
// 00001001 //9

 int number[] = {
 B00000011, //0
 B01011111 ,//1
 B00100101, //2
 B00001101,  //3
 B01011001,  //4
 B10001001, //5
 B10000001, //6
 B00011111, //7
 B00000001,//8
 B00001001, //9
};

void loop() {
  if(Serial.available()>0){
   a = Serial.readString();
    
    }
 int b = a.toInt();
 Serial.println(b);
   for(int i = 0; i<10; i++){
  // put your main code here, to run repeatedly:
  digitalWrite(latchpin,LOW);
  shiftOut(datapin,clockpin,LSBFIRST,number[i]);
  digitalWrite(latchpin,HIGH);
  delay(300);
}
}
