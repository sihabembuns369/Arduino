int detik = 1;
int menit = 0;
int jam = 0;
unsigned long kembali;

void setup() {
 Serial.begin(9600);

}

void loop() {
 unsigned long waktu = millis();

 //detik
 if((waktu-kembali)>= 1000){
  kembali = waktu;
  detik++;
//  Serial.println(detik);
  if(detik > 59){
    detik = 1;
    menit++;
  }
  if(menit > 59){
    menit = 0;
    jam++;
    }
   if(jam > 24){
      jam = 0;
      }
}
char jame[20];
 sprintf(jame, "%02d:%02d:%02d",jam, menit, jam);
 
  Serial.print("jam = ");
 Serial.println(jame);  
}
