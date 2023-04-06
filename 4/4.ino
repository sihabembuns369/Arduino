  #include <SoftwareSerial.h>

#include <Wire.h> // must be included here so that Arduino library object file references work
//#include <RtcDS3231.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Mono5x7.h>
#include <fonts/EMSans8x16.h> //bold/tebal
#include <Arial_Black_16_ISO_8859_1.h>

//RtcDS3231<TwoWire> Rtc(Wire);

//----------------------------------------
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <time.h>

const char *ssid = "esp8266p10";
const char *password = "12345678";

ESP8266WebServer server(80);
String LEDstate, webPage, notice, kecerahan, kecepatan, efek;
char *abc = "Salin alamat ip 192.168.4.1 ke web browser , @Copyright Riski sihab";
int kecepatanled = 50;
int efekled;

char jamtampil[16];
char menittampil[16];
char detiktampil[16];
char jamnya[20];

#define DISPLAYS_WIDE 1 //--> jumlah panel
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);
SoftwareSerial serial(D1, D2); //dfplayer




const char htmlPage[]PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    body {font-family: Arial, Helvetica, sans-serif;}
    form {border: 3px solid #f1f1f1;}
    
    input[type=text], input[type=password] {
      width: 100%;
      padding: 12px 20px;
      margin: 8px 0;
      display: inline-block;
      border: 1px solid #ccc;
      box-sizing: border-box;
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
<h3>Pengaturan text running </h3>

<form id="txt_form" name="frmText" method="post">
<div class="imgcontainer">
maskan text<input type="text" name="myText" ><br>
atur kecerahan 1-255<input type="number" name="kecerahan" class="inp" ><br>
atur kecepatan <input type="number" name="kecepatan"  class="inp"></br>
pilih efek
<select name="efek" id="efk"  class="inp">
  <option value="1">tebal </option>
  <option value="2">tipis</option>
  <option value="3">text elektrik</option>
</select>


<form>
<button onclick="myFunction()"> TEKAN </button>
<h3>Aplikasi web server pengaturan text running V1.0 @Copyright Riski sihab</h3>
</div>
<p id="demo"></p>

<script>
var x;
function myFunction() {
     var eID = document.getElementById("efk");
     p = eID.options[eID.selectedIndex].value;
     x = document.getElementById("myText").value
     y = document.getElementById("kecerahan").value 
     z = document.getElementById("kecepatan").value 
//     a = document.getElementById("efek").value 
     
   nocache = \"/&nocache=\" + Math.random() * 1000000;
   var request = new XMLHttpRequest();"
   request.open("GET", + p + x + y + z  + nocache, false);
   request.send(null);" 
     
}

</script>
</body>
</html>
)=====";

void handleRoot()
{
  
//  webPage=htmlPage;
 notice=server.arg("myText"); //menerima data dari web
 kecerahan=server.arg("kecerahan");
 kecepatan=server.arg("kecepatan");
 efek=server.arg("efek");

 Serial.println(efek);
  Serial.print("Argument Received");
  server.send(200, "text/html", htmlPage);

  delay(2000);
  strcpy(abc, notice.c_str()); // mengkonversi string ke char*
  int kecerahanled = kecerahan.toInt(); //mengkonversi string ke int
  kecepatanled = kecepatan.toInt();
   efekled = efek.toInt();
   Disp.clear();
//  myDisplay.displayText(abc, PA_CENTER, kecepatanled, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  Disp.setBrightness(kecerahanled); //0-255
    Disp.setFont(Mono5x7); 
 Disp.drawText(0, 7, abc);
 Serial.println(abc);
 Disp.clear();

}

void setup() {
   
   Serial.begin(9600);
    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.begin();
   
  Disp.start(); //--> Run the DMDESP library
  Disp.clear();
  Disp.setBrightness(50); //--> Brightness level
  Disp.setFont(Mono5x7); //--> Determine the font used

 Serial.print("compiled: ");
//    Serial.print(__DATE__);
//    Serial.println(__TIME__);
//    Rtc.Begin(D2,D1);
//    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
//    printDateTime(compiled);
    Serial.println();
//    Rtc.Enable32kHzPin(false);
//    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}


void loop() { 
//jam();
   server.handleClient();
    Disp.loop(); 
//    Disp.setFont(ElektronMart6x8);  
     Scrolling_Text(0, kecepatanled);
  RtcDateTime now = Rtc.GetDateTime();
int jam = now.Hour();
int menit = now.Minute();
int detik = now.Second();
int tanggal = now.Day();
int tahun = now.Year();
int bulan = now.Month();

  sprintf(jamnya, "%02d:%02d:%02d",now.Hour(),now.Minute(),now.Second());
  Serial.println(jamnya);
//  Serial.println(now.DayOfWeek());
////jam
String jame = String(jam);
jame.toCharArray(jamtampil,16);

////menit
String menite = String(menit);
menite.toCharArray(menittampil,16);


////detike
String detike = String(detik);
detike.toCharArray(detiktampil,16);

// jam
//     Serial.println(now.Hour());
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(1, 0, jamtampil);

// menit
//     Serial.println(now.Hour());/
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(19, 0, menittampil);


//detik
//     Serial.println(now.Hour());
      Disp.setBrightness(255); 
    Disp.setFont(Mono5x7);  
    Disp.drawText(32, 0, detiktampil);
   
  }

void Scrolling_Text(int y, uint8_t scrolling_speed) {
  
  void handleRoot();
  static uint32_t pM;
  static uint32_t x;  int width = Disp.width();
//  Disp.setFont(efek);
switch (efekled)
{
case 1:
Disp.setFont(Arial_Black_16_ISO_8859_1);
break;
case 2:
Disp.setFont(Mono5x7);
break;
case 3:
Disp.setFont(EMSans8x16);
break;
}
  
  int fullScroll = Disp.textWidth(abc) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, 8, abc);
  }  
}
