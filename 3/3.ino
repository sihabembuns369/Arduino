#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char mainPage[] = R"=====(
<!DOCTYPE html>
<html lang="en">
 
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Elemetris IoT </title>
  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.0/css/bootstrap.min.css" />
  <style>
  .content {
    width: 100%;
    padding: 20px;
    min-height: calc(100vh - 60px);
    padding-bottom: 100px;
  }
 
  .footer {
    width: 100%;
    min-height: 60px;
    /* Height of the footer */
    max-height: 60px;
    background: var(--teal);
    padding-top: 10px;
    padding-bottom: 10px;
  }
 
  .footer a {
    color: white;
  }
 
  .jumbotron {
    background-color: var(--teal);
  }
 
  .devicebox {
    border: solid 2px var(--green);
    margin-top: 10px;
    border-radius: 10px;
    padding: 3px;
    min-height: 50px;
  }
 
  .switch {
    position: absolute;
    right: 30px;
    bottom: -13px;
    display: inline-block;
    width: 60px;
    height: 34px;
  }
 
  .switch input {
    opacity: 0;
    width: 0;
    height: 0;
  }
 
  .slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #ccc;
    -webkit-transition: .4s;
    transition: .4s;
  }
 
  .slider:before {
    position: absolute;
    content: "";
    height: 26px;
    width: 26px;
    left: 4px;
    bottom: 4px;
    background-color: white;
    -webkit-transition: .4s;
    transition: .4s;
  }
 
  input:checked+.slider {
    background-color: var(--green);
  }
 
  input:focus+.slider {
    box-shadow: 0 0 1px var(--green);
  }
 
  input:checked+.slider:before {
    -webkit-transform: translateX(26px);
    -ms-transform: translateX(26px);
    transform: translateX(26px);
  }
 
  .slider.round {
    border-radius: 34px;
  }
 
  .slider.round:before {
    border-radius: 50%;
  }
 
  .icon {
    font-size: 1.5rem;
    margin-left: 10px;
    margin-right: 10px;
    position: relative;
    bottom: -3px;
  }
 
  h5 {
    position: relative;
    bottom: -5px;
  }
  </style>
</head>
 
<body>
  <div class="wrapper">
    <div class="container-fluid">
      <div class="content">
        <div class="jumbotron">
          <h1>Elemetris </h1>
          <h5>ESP8266 Web Server dengan output LED </h3>
        </div>
        <div class="container-fluid">
          <div class="row">
            <div class="col-lg-6">
              <div class="devicebox">
                <div class="row">
                  <div class="col-12 d-inline-flex align-items-center"> <i class="fas fa-lightbulb icon"> </i>
                    <h5>LED 1 </h5>
                    <label class="switch">
                      <input type="checkbox" id="led1" onclick="ledUpdate(this.id,this.checked)">
                      <span class="slider round"> </span>
                    </label>
                  </div>
                </div>
              </div>
            </div>
            <div class="col-lg-6">
              <div class="devicebox">
                <div class="row">
                  <div class="col-12 d-inline-flex align-items-center"> <i class="fas fa-lightbulb icon"> </i>
                    <h5>LED 2 </h5>
                    <label class="switch">
                      <input type="checkbox" id="led2" onclick="ledUpdate(this.id,this.checked)">
                      <span class="slider round">
                      </span>
                    </label>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <div class="row">
            <div class="col-lg-6">
              <div class="devicebox">
                <div class="row">
                  <div class="col-12 d-inline-flex align-items-center"> <i class="fas fa-lightbulb icon"> </i>
                    <h5>LED 3 </h5>
                    <label class="switch">
                      <input type="checkbox" id="led3" onclick="ledUpdate(this.id,this.checked)">
                      <span class="slider round">
                      </span>
                    </label>
                  </div>
                </div>
              </div>
            </div>
            <div class="col-lg-6">
              <div class="devicebox">
                <div class="row">
                  <div class="col-12 d-inline-flex align-items-center"> <i class="fas fa-lightbulb icon"> </i>
                    <h5>LED 4 </h5>
                    <label class="switch">
                      <input type="checkbox" id="led4" onclick="ledUpdate(this.id,this.checked)">
                      <span class="slider round">
                      </span>
                    </label>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="container-fluid footer justify-content-center align-items-center">
        <div class="row d-flex justify-content-center">
          <div class="col-12 text-center">
            <span>© 2020 </span>
            <a href="#0">Eldi4/Lanove/Elemetris </a>
            <span>All rights reserved </span>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.0/umd/popper.min.js"> </script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.0/js/bootstrap.min.js"> </script>
<script defer src="https://use.fontawesome.com/releases/v5.0.13/js/solid.js"> </script>
<script defer src="https://use.fontawesome.com/releases/v5.0.13/js/fontawesome.js"> </script>
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"> </script>
<script>
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      var obj = JSON.parse(this.response);
      for(var key in obj) {
        $("#" + key).prop("checked", (obj[key] === 'true'));
      }
    }
  };
  xhttp.open("GET", "getData", true);
  xhttp.send();
}
 
function ledUpdate(number, led) {
  var xhttp = new XMLHttpRequest();
  xhttp.open("POST", "ledUpdate");
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("LEDstate=" + led + "&LEDnumber=" + number);
}
$(function() {
    getData();
});
</script>
 
</html>
)=====";
//SSID sama Password WiFi kalian
const char* ssid = "namawifikalian";
const char* password = "passwordwifikalian";
  
ESP8266WebServer server(80);
 
int pinLed[4]= {14,12,13,15}; // pin yang mau kalian pake buat output
bool ledState[4]; // dipake buat nyimpen keadaan si LED, apakah nyala ato mati
 
void handleRoot() {
 String s = mainPage;
 server.send(200, "text/html", s);
}
 
void handleStatus() {
  String buffer = "{";
  String state;
  for(int i = 0; i<4; i++){
    if(ledState[i])
      state = "true";
    else
      state = "false";
    buffer += "\"led" + String(i+1) +"\"" + ":" + "\"" + state + "\"";
    if(i!=3){
      buffer += ",";
    }
  }
  buffer += "}";
  server.send(200, "application/json", buffer);
}
  
void handleUpdate() {
 String arg_state = server.arg("LEDstate");
 String arg_number = server.arg("LEDnumber");
 Serial.println(arg_number + ":" + arg_state);
 bool state;
 int number;
 if(arg_state == "true")
  state = true;
 else if(arg_state == "false")
  state = false;
 if(arg_number == "led1"){
  number = pinLed[0];
  ledState[0] = state;
 }else if(arg_number == "led2"){
  number = pinLed[1];
  ledState[1] = state;
 }else if(arg_number == "led3"){
  number = pinLed[2];
  ledState[2] = state;
 }else if(arg_number == "led4"){
  number = pinLed[3];
  ledState[3] = state;
 }
 digitalWrite(number,state);
}
 
void setup(void){
  Serial.begin(115200);
   
  WiFi.begin(ssid, password);
  Serial.println("");
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Konek ke ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.on("/ledUpdate", handleUpdate);
  server.on("/getData", handleStatus);
  
  server.begin();
  Serial.println("Web Server Ashyiap!");
  for(int i = 0; i<4; i++){
    pinMode(pinLed[i],OUTPUT); 
  }
}
 
void loop(void){
  server.handleClient();
}
