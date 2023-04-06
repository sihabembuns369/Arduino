/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * to control GPIO (on-board LED)
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Penentuan pin serial
#define MAX_DEVICES 4
#define DATA_PIN D1
#define CS_PIN D0
#define CLK_PIN D5

//#define DATA_PIN D5
//#define CS_PIN D6
//#define CLK_PIN D7
// Membuat objek
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);



const char *ssid = "Tex running";
const char *password = "12345678";
int stateLED = LOW;

ESP8266WebServer server(80);
String LEDstate, webPage,notice,kecerahan,kecepatan,efek;
int efekled;
int kecepatanled;
 char *abc = "Salin alamat ip 192.168.4.1 ke web browser , @Copyright Riski sihab";

const char htmlPage[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Pengatran text running</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    body {font-family: Arial, Helvetica, sans-serif;}
    form {border: 3px solid #f1f1f1;}
    .option{
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
    input[type=text], input[type=password],input[type=number] {
      width: 100%;
      padding: 12px 20px;
      margin: 8px 0;
      display: inline-block;
      border: 1px solid #ccc;
      box-sizing: border-box;
    }
    
    button {
      background-color: #04AA6D;
      color: white;
      padding: 20px 20px;
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
      padding: 66px;
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
<body>

<h3>Pengaturan Text running</h3>

<form id="txt_form" name="frmText" method="post">
  <div class="container">
maskan text<input type="text" name="myText" ><br>
atur kecerahan 1-15<input type="number" name="kecerahan" ><br>
pilih kecepatan 1-100 <input type="number" name="kecepatan" ></br>
pilih efek
<select name="efek" id="efk" class="option">
  <option value="1">PA_NO_EFFECT </option>
  <option value="2">PA_PRINT </option>
  <option value="3">PA_SCROLL_UP </option>
  <option value="4">PA_SCROLL_LEFT  </option>
  <option value="5">PA_SCROLL_RIGHT  </option>
  <option value="6">PA_SPRITE  </option>
  <option value="7">PA_SLICE  </option>
  <option value="8">PA_MESH </option>
  <option value="9">PA_FADE </option>
  <option value="10">PA_DISSOLVE  </option>
  <option value="11">PA_BLINDS  </option>
  <option value="12">PA_RANDOM </option>
  <option value="13">PA_WIPE  </option>
  <option value="14">PA_WIPE_CURSOR  </option>
</select>

<form>

<button onclick="myFunction()"> Tekan </button>
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
     z = document.getElementById("kecerahan").value 
     
   nocache = \"/&nocache=\" + Math.random() * 1000000;
   var request = new XMLHttpRequest();"
   request.open("GET",+ p + x + y + z + a + nocache, false);
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
 
 Serial.println(notice);
  Serial.println("Argument Received");
  server.send(200, "text/html", htmlPage);

  delay(2000);
 
  strcpy(abc, notice.c_str()); // mengkonversi string ke char*
  int kecerahanled = kecerahan.toInt(); //mengkonversi string ke int
   efekled = efek.toInt();
   Serial.println(efekled);
  myDisplay.setIntensity(kecerahanled); //mengatr int
  kecepatanled = kecepatan.toInt();
textEffect_t efeke;
  switch(efekled){
    case 1:
    efeke = PA_NO_EFFECT;
    break;
    case 2:
    efeke = PA_PRINT;
    break;
    case 3:
    efeke = PA_SCROLL_UP;
    break;
    case 4:
    efeke = PA_SCROLL_LEFT;
    break;
    case 5:
    efeke = PA_SCROLL_RIGHT;
    break;
    case 6:
    efeke = PA_SPRITE;
    break;
    case 7:
    efeke = PA_SLICE;
    break;
    case 8:
    efeke = PA_MESH ;
    break;
     case 9:
    efeke = PA_FADE ;
    break;
     case 10:
    efeke = PA_DISSOLVE ;
    break;
     case 11:
    efeke = PA_BLINDS ;
    break;
     case 12:
    efeke = PA_RANDOM ;
    break;
     case 13:
    efeke = PA_WIPE ;
    break;
     case 14:
    efeke = PA_WIPE_CURSOR ;
    break;
    
    }
    
  myDisplay.displayText(abc, PA_CENTER, kecepatanled, 0, efeke, efeke);
 
}

//-------------------------------------------------------------------------------------------------

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();
    
// ======================md parola/dot matrix============
// Memulai object
  myDisplay.begin();
  // Mengatur intensitas (0-15)
  myDisplay.setIntensity(15); //mengatur kecerahan

  // Membersihkan tampilan
  myDisplay.displayClear(); //membersihkan kecerahan

  //---------------------------------
    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
//    server.on("/&MSG=", handleLedOn);
//    server.on("/LEDOn", handleLedOn);
//    server.on("/LEDOff", handleLedOff);
    server.begin();
    Serial.println("HTTP server beginned");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, stateLED);
     myDisplay.displayText(" KAYIM SEWARU WETAN ", PA_CENTER, 70, 0, PA_SCROLL_LEFT,PA_SCROLL_LEFT);
}

void loop() {
    server.handleClient();
     if (myDisplay.displayAnimate()) {

    myDisplay.displayReset();

  }

}
