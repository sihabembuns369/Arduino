/*
  Name:		    echoBot.ino
  Created:	    12/21/2017
  Author:	    Stefano Ledda <shurillu@tiscalinet.it>
  Description: a simple example that check for incoming messages
              and reply the sender with the received message
*/
#include "CTBot.h"
CTBot myBot;
CTBotInlineKeyboard myKbd;
String ssid  = "Salaf Putra"    ; // REPLACE mySSID WITH YOUR WIFI SSID
String pass  = "ngaji123"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "5819750626:AAERusPwqiryS2i5rAC7xo0xBAzSCGpZ4bI"   ; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

#define pin1  D5
#define pin2  D6
#define pin3  D7
#define pin4  D8
#define LIGHT_ON_CALLBACK  "lightON"
#define LIGHT_OFF_CALLBACK  "lightOFF"
void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
  pinMode(pin1, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin2, OUTPUT);
  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
//  myKbd.addButton("lampu nyala", LIGHT_ON_CALLBACK, CTBotKeyboardButtonQuery);
//  myKbd.addButton("lapu mati", LIGHT_OFF_CALLBACK, CTBotKeyboardButtonQuery);
//  myKbd.addRow();

}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    if (msg.messageType == CTBotMessageText) {
      if (msg.text == "/mulai") {
        myKbd.addButton("lampu nyala", LIGHT_ON_CALLBACK, CTBotKeyboardButtonQuery);
        // ...forward it to the sender
        myBot.sendMessage(msg.sender.id, "lampu di nyala", myKbd);
        Serial.println(msg.text);
        //		myBot.sendMessage(msg.sender.id, msg.text);
//        delay(500);
      }
    }
  } if (msg.messageType == CTBotMessageQuery) {
    if (msg.callbackQueryData.equals(LIGHT_ON_CALLBACK)) {
      Serial.println("tombol di tekan");
      digitalWrite(pin1, LOW); //nyala
      //      myBot.endQuery(msg.callbackQueryID, "Light on", true);

      myKbd.addButton("lapu mati", LIGHT_OFF_CALLBACK, CTBotKeyboardButtonQuery);
      myBot.sendMessage(msg.sender.id, "lampu di mati", myKbd);
    } else if (msg.callbackQueryData.equals(LIGHT_OFF_CALLBACK)) {
      myKbd.addButton("lampu nyala", LIGHT_ON_CALLBACK, CTBotKeyboardButtonQuery);
      myBot.sendMessage(msg.sender.id, "lampu di nyalakan", myKbd);
      digitalWrite(pin1, HIGH); //mati
    }
  }

  myKbd.addRow();
}
