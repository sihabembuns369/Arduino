int sensorsuara = 2; //mendefinisikan pin sensor ada di pin D2 pada arduino nano
int lampu = 4; //mendefinisikan pin lampu ada di pin D4 pada arduino nano
int nilai; //tempat untuk menampung nilai untuk mentriger lampu . nilai awal bernilai 0/kosong
void setup() 
{
  Serial.begin(9600); //memulai serial dengan baudrate 9600
  pinMode (sensorsuara, INPUT); //membuat sesorsuara menjadi input
  pinMode (lampu, OUTPUT); //membuat lampu menjadi output

}

void loop() {
  int state=digitalRead(sensorsuara);  //membaca nilai sensor / jika digitalwrite maka yang dibaca 1 atau 0 / HIGH atau LOW

  if(digitalRead(sensorsuara) == 1){ //statment jika sensor suara bernilai high/1 maka:
    nilai++; //nilai akan  bertam satu
    if(nilai > 3){ //statment jika nilai leih dari 3 maka
      nilai = 0; //nilai akan kembali lagi  ke 0
      }
    }
  if(nilai==1) //statment ketika variabel nilai  bernilai 1 maka:
  {
    digitalWrite(lampu, HIGH); //lampu akan nyala
    Serial.println("nyala"); //menampilkan tulisan NYALA di serial monitor
    
  } else if(nilai == 3){ //statment jika variabel nilai 3 maka:
    digitalWrite(lampu, LOW); //lampu akan mati
    Serial.println("MATI"); //menammpilkan tulisan MATI di serial monitor
    }
    Serial.print("nilai ="); //menampilkan tulisan nilai= di serial monitor
    Serial.println(nilai); //menampilkan variabel nilai /isi dari variabel nilai ke serial monitor

}
