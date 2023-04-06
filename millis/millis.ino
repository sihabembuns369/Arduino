int a = 0;
unsigned long b;
unsigned long d;
int menit = 1;
int detik = 59;
char abc[30];
bool ab = true;
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }
void setup() {
  Serial.begin(9600);
  Serial.print("halo");
}

void loop() {
  unsigned long c = millis();
  //Serial.println(millis()/1000);
  ab = true;
  if ((c - b) >= 1000) {
    b = c;
    if (ab = true) {
      // a++;
      detik --;
    }
  }

  if (detik >= 0 && detik <= 60) {
    if (menit >= 0) {
      Serial.print(" lagi");
      sprintf(abc , "%02d:%02d", menit, detik);
      PRINT("\nwaktu berjalan ", abc);
    } else {
      ab = false;
      detik = 0;
      menit = 0;
      Serial.print(" waktu habis ");
      sprintf(abc , "%02d:%02d", menit, detik);
      PRINT("\nwaktu berjalan ", abc);
    }
  }

  if (detik == 0) {
    detik = 59;
    menit --;
  }

  //    if((c-d)>= 7000){
  //       d = c;
  //       Serial.println("tes kedua");
  //        Serial.println(c);
  //
  //       Serial.println(" ");
  //      }
  // put your main code here, to run repeatedly:
  //Serial.println(" ");
}
