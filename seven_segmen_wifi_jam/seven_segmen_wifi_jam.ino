  #include <SoftwareSerial.h>

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
#include "TM1637.h"
#include <EEPROM.h>
RtcDS3231<TwoWire> Rtc(Wire);
#define CLK D7   
#define DIO D6
TM1637 tm1637(CLK, DIO);


//----------------------------------------
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <time.h>
const char *ssid = "arduino-er";
const char *password = "password";
void writeString(char add,String data);
String read_String(char add);
boolean state;
ESP8266WebServer server(80);
String LEDstate, webPage, notice, kecerahan, kecepatan, efek;
char *abc = "Salin alamat ip 192.168.4.1 ke web browser , @Copyright Riski sihab";
int alamatjam = 0;
int alamatmenit = 1;

String jam,menit;
int jame,menite;
 int jm,mn;
int b;
char jamtampil[16];
char menittampil[16];
char detiktampil[16];
char jamnya[20];
unsigned long waktulama;


const char htmlPage[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    body {font-family: Arial, Helvetica, sans-serif;}
    form {border: 3px solid #f1f1f1;}
    
  /* Full-width input fields */
input[type=text], input[type=password] {
  width: 100%;
  padding: 15px;
  margin: 5px 0 22px 0;
  display: inline-block;
  border: none;
  background: #f1f1f1;
}

/* Add a background color when the inputs get focus */
input[type=text]:focus, input[type=password]:focus {
  background-color: #ddd;
  outline: none;
}

    .inp {
      width: 100%;
      padding: 12px 20px;
      margin: 8px 0;
      display: inline-block;
      border: 1px solid #ccc;
      box-sizing: border-box;
    }
    h3{
      text-align: center;
      color: black;
    }
    
    button {
      background-color: #04AA6D;
      color: white;
      padding: 14px 20px;
      margin: 8px 0;
      border: none;
      cursor: pointer;
      width: 100%;
    }
    
    button:hover {
      opacity: 0.8;
    }
    
    .cancelbtn {
      width: auto;
      padding: 10px 18px;
      background-color: #f44336;
    }
    
    .imgcontainer {
      text-align: center;
      margin: 24px 0 12px 0;
    }
    
    img.avatar {
      width: 40%;
      border-radius: 50%;
    }
    
    .container {
      padding: 30px;
    }
    
    span.psw {
      float: right;
      padding-top: 16px;
    }

    .cancelbtn {
  padding: 14px 20px;
  background-color: #f44336;
}

/* Float cancel and signup buttons and add an equal width */
.cancelbtn, .signupbtn {
  float: left;
  width: 50%;
}

/* Add padding to container elements */
.container {
  padding: 16px;
}
.containermodal{
  padding: 16px;
  background-color: #04AA6D;

}

/* The Modal (background) */
.modal {
  display: none; /* Hidden by default */
  position: fixed; /* Stay in place */
  z-index: 1; /* Sit on top */
  left: 0;
  top: 0;
  width: 100%; /* Full width */
  height: 100%; /* Full height */
  overflow: auto; /* Enable scroll if needed */
  background-color: #474e5d;
  padding-top: 50px;
}

/* Modal Content/Box */
.modal-content {
  background-color: #fefefe;
  margin: 5% auto 15% auto; /* 5% from the top, 15% from the bottom and centered */
  border: 1px solid #888;
  width: 80%; /* Could be more or less, depending on screen size */
}

/* Style the horizontal ruler */
hr {
  border: 1px solid #f1f1f1;
  margin-bottom: 25px;
}
 
/* The Close Button (x) */
.close {
  position: absolute;
  right: 35px;
  top: 15px;
  font-size: 40px;
  font-weight: bold;
  color: #f1f1f1;
}

.close:hover,
.close:focus {
  color: #f44336;
  cursor: pointer;
}

/* Clear floats */
.clearfix::after {
  content: "";
  clear: both;
  display: table;
}
    
    /* Change styles for span and cancel button on extra small screens */
    @media screen and (max-width: 300px) {
      span.psw {
         display: block;
         float: none;
      }
      .cancelbtn {
         width: 100%;
      }
    }
    </style>
    </head>
 <body>
<h3>Pengaturan alarm </h3>

<form method="post">
<div class="imgcontainer">
atur jam <input type="number" name="jam" class="inp" ><br>
atur menit <input type="number" name="menit"  class="inp"></br>

<button name="klik" value="1" onclick="myFunction()"> TEKAN </button>
<h3>Aplikasi web server pengaturan Alarm V1.0 @Copyright Riski sihab</h3>
</div>

</form>


//set wifi
<form action="/setwifi">
<div class="imgcontainer">
atur jam <input type="text" name="ssid" class="inp" ><br>
atur menit <input type="text" name="psw"  class="inp"></br>

<button name="klik" value="1" onclick="rubahwifi()"> TEKAN </button>
</div>
//<p id="demo"></p>
</form>

<script>

//var x;
function myFunction() {
     x = document.getElementById("jam").value
     y = document.getElementById("menit").value 
     z = document.getElementById("klik").value 
   nocache = \"/&nocache=\" + Math.random() * 1000000;
   var request = new XMLHttpRequest();"
   request.open("GET", + x  + y + z ,nocache, false);
   request.send(null);" 
     
}

function rubahwifi() {
     ab = document.getElementById("ssid").value
     bc = document.getElementById("psw").value 
   nocache = \"/&nocache=\" + Math.random() * 1000000;
   var request = new XMLHttpRequest();"
   request.open("GET", + ab +  bc ,nocache, false);
   request.send(null);" 
     
}

</script>
</body>
</html>
)=====";
void(*ku_reset)(void)=0;

void handleRoot()
{
  
//  webPage=htmlPage;

 jam=server.arg("jam");
 menit=server.arg("menit");
 
 String click=server.arg("klik");
 
 String ssidName=server.arg("ssid"); 
 String passwordName=server.arg("psw");

  server.send(200, "text/html", htmlPage);

 int setjam = jam.toInt();
 int setmenit = menit.toInt();
 
   Serial.print(click);
  
  EEPROM.write(alamatjam,setjam);
   EEPROM.write(alamatmenit,setmenit);
    EEPROM.commit();
    
if(click == "1"){
digitalWrite(D0,HIGH);
delay(200);
digitalWrite(D0,LOW);

}
}

void handleForm() {
 String click=server.arg("klik");
 String ssidName=server.arg("ssid"); 
 String passwordName=server.arg("psw");
 writeString(3,ssidName);
 Serial.print("SSID : ");
 Serial.println(ssidName);
 delay(500);
 writeString(30,passwordName);
 Serial.print("Password : ");
 Serial.println(passwordName);
 
 if(click == "1"){
digitalWrite(D0,HIGH);
delay(200);
digitalWrite(D0,LOW);

}
// delay(1000);
// String s = "<a href='/'> Berhasil </a>";
// server.send(200, "text/html", s); //Send web page
 server.send(200, "text/html", htmlPage);
 delay(1000);
 ku_reset();
}

void setup() {
   pinMode(D0,OUTPUT);
   digitalWrite(D0,LOW);
   Serial.begin(9600);
    EEPROM.begin(512);
    String ssidString = read_String(3);
  String passString = read_String(30);
  const char *ssid = ssidString.c_str();
  const char *password = passString.c_str();

//    const char *ssid = ssidString.c_str();
//  const char *password = passString.c_str();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
     IPAddress apip = WiFi.softAPIP();

  Serial.println("");
  Serial.print("AP Name : ");
  Serial.println(ssidString);
  Serial.print("Password : ");
  Serial.println(passString);
    tm1637.init();
    tm1637.set(7);
    
   
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/setwifi", handleForm); 
    server.begin();
    
   Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    Rtc.Begin(D4,D9);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//    printDateTime(compiled);
    Serial.println();
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}


void loop() { 

   server.handleClient();
    RtcDateTime now = Rtc.GetDateTime(); 
  RtcTemperature temp = Rtc.GetTemperature();
  b = temp.AsFloatDegC();
//      Serial.println(b);
      
 jame = now.Hour();
 menite = now.Minute();

  tampil();
alarmnyala();
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[256]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

//void(*ku_reset)(void)=0;

void alarmnyala(){    
jm = EEPROM.read(alamatjam);
mn =  EEPROM.read(alamatmenit);
//   Serial.println(jm);
//    Serial.println(mn);
    
    if (jame == jm && menite == mn){
//      digitalWrite(D0,state);
     buzer();
//      Serial.println(state);
      }
      
//    }
  }

  void buzer(){
    for(int i = 1; i <=1; i++ ){
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,LOW);
      }
    }

    void tampil(){

   unsigned long waktu2;
   unsigned long waktu3;
//   if((millis() - waktu2) >= 3000){
//    waktu2 = millis();
//    Serial.println("waktu1");
  tm1637.display(0, jame / 10);  // hour
  tm1637.display(1, jame % 10);
  tm1637.display(2, menite / 10); // minutes
  tm1637.display(3, menite % 10); //

      if((millis() - waktulama)>=1000){
        waktulama = millis();
//         Serial.println("hidup");
        if(state == 0){
          state = 1;
        }else if(state == 1){ state = 0;}
      } 
//          Serial.println(state);
              if(state == 1){
                tm1637.point(POINT_ON);
              }else if(state == 0){tm1637.point(POINT_OFF);}          
      }
//
//      if((millis() - waktu3) >= 5000){
//        waktu3 = millis();
//        
//    Serial.println("waktu2");
////    tm1637.display(0, b); 
////    tm1637.display(1, b);
//    tm1637.display(2,18); // put degree
//    tm1637.display(3,12);  // put a C at the end
//    tm1637.DisplayClear();
//    
//        }
//   }
