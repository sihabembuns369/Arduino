
#include <ESP8266WiFi.h>
#include "DMDESP.h"
#include "fonts/EMSansSP8x16.h"
//#include "fonts/bmz10x16.h"
//#include <fonts/bmz5x7.h>
#include <EEPROM.h>
#include "Wire.h"
#define DISPLAYS_WIDE 2 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

int SkorKiri =0;
int SkorKanan=0;
char Buff1[10];
char Buff2[10];
int Buzz = D4;
//------------------------------------------------------------------------------------
 // Define I/O Pins
//  #define     LED0      2           // WIFI Module LED
//  #define     LED1      D0          // Connectivity With Client #1
//  #define     LED2      D2          // Connectivity With Client #2
  #define     BUTTON    D2          // Connectivity ReInitiate Button
//------------------------------------------------------------------------------------

  // Authentication Variables
  char*       TKDssid;              // SERVER WIFI NAME
  char*       TKDpassword;          // SERVER PASSWORD
//------------------------------------------------------------------------------------
  #define     MAXSC     100           // MAXIMUM NUMBER OF CLIENTS
  WiFiServer  TKDServer(9001);      // THE SERVER AND THE PORT NUMBER
  WiFiClient  TKDClient[MAXSC];     // THE SERVER CLIENTS


  void setup()
  {
    // Setting The Serial Port
    Serial.begin(115200);           // Computer Communication
    SkorKiri=EEPROM.read(0);
    SkorKanan=EEPROM.read(1);
    EEPROM.write(0,SkorKiri);
    EEPROM.write(1,SkorKanan);
    
    pinMode(Buzz, OUTPUT);          // WIFI OnBoard LED Light

    Serial.println();
    Serial.println("I/O Pins Modes Set .... Done");

    // Setting Up A Wifi Access Point
    SetWifi("TAKEONE", "");


    Disp.start(); // Jalankan library DMDESP
    Disp.setBrightness(100); // Tingkat kecerahan
 
  }

  
  void loop()
  {
    
    IsClients2();
    Disp.loop();
    if(SkorKiri >= 99){
      SkorKiri = 00;
    }
    if(SkorKiri <= 00){
      SkorKiri = 00;
    }

     if(SkorKanan >= 99){
      SkorKanan = 0;
    }
    if(SkorKanan <= 0){
      SkorKanan = 0;
    }
    Disp.setFont(EMSansSP8x16); 
    sprintf(Buff1,"%.2d",SkorKiri);
    sprintf(Buff2,"%.2d",SkorKanan);
 
     Disp.drawText(2,0,Buff1);
     Disp.drawText(41,0,Buff2);

     //VS
    Disp.setFont(EMSansSP8x16);
    Disp.drawText(26, 0, "V");
    Disp.drawText(33, 0, "S");

    //Panah Kiri
    Disp.drawLine(25,12,28,9,1);
    Disp.drawLine(25,12,28,15,1);
    Disp.drawLine(26,12,29,9,1);
    Disp.drawLine(26,12,29,15,1);

    //Pananh Kanan
    Disp.drawLine(35,9,38,12,1);
    Disp.drawLine(35,15,38,12,1);
    Disp.drawLine(34,9,37,12,1);
    Disp.drawLine(34,15,37,12,1);
  }


  
  void SetWifi(char* Name, char* Password)
  {
    // Stop Any Previous WIFI
    WiFi.disconnect();

    // Setting The Wifi Mode
    WiFi.mode(WIFI_AP_STA);
    Serial.println("WIFI Mode : AccessPoint Station");
    
    // Setting The Access Point
    TKDssid      = Name;
    TKDpassword  = Password;
    
    // Starting The Access Point
    WiFi.softAP(TKDssid, TKDpassword);
    Serial.println("WIFI < " + String(TKDssid) + " > ... Started");
    
    // Wait For Few Seconds
    delay(1000);
    
    // Getting Server IP
    IPAddress IP = WiFi.softAPIP();
    
    // Printing The Server IP Address
    Serial.print("AccessPoint IP : ");
    Serial.println(IP);

    // Starting Server
    TKDServer.begin();
    Serial.println("Server Started");
  }



  void IsClients()
  {
    if(TKDServer.hasClient())
    {
      WiFiClient TKDClient = TKDServer.available();
      
      if(digitalRead(Buzz) == HIGH) digitalWrite(Buzz, LOW);
      
   //   digitalWrite(LED1, HIGH);

      while(1)
      {

        //--[ Draft ] ---------------------------------------------------

        
              
        //---------------------------------------------------------------
        // If Clients Are Connected 
        //---------------------------------------------------------------
        
        if(TKDClient.available())
        {
          // Here We Read The Message
          String Message = TKDClient.readStringUntil('\r');
          // Here We Print The Message On The Screen
          Serial.println(Message);
          // Here We Reply To The Client With A Message
          TKDClient.print("\nWe Got Your Message");
          TKDClient.flush();
        }
        
        //---------------------------------------------------------------
        // If Clients Are Disconnected
        //---------------------------------------------------------------
        
        if(!TKDClient || !TKDClient.connected())
        {
          // Here We Turn Off The LED To Indicated The Its Disconnectted
       //   digitalWrite(LED1, LOW);
          // Here We Jump Out Of The While Loop
          break;
        }

     
        
      }
      
    }
    else
    {
      // This LED Blinks If No Clients Where Available
      digitalWrite(Buzz, LOW);
      delay(250);
      digitalWrite(Buzz, HIGH);
      delay(250);
    }
  }



  void IsClients2()
  {
    if (TKDServer.hasClient())
    {
      for(int i = 0; i < MAXSC; i++)
      {
        //find free/disconnected spot
        if (!TKDClient[i] || !TKDClient[i].connected())
        {
          if(TKDClient[i]) TKDClient[i].stop();
          TKDClient[i] = TKDServer.available();
          Serial.print("New Client : "); Serial.print(String(i+1) + " - ");
          continue;
        }
      }
      // no free / disconnected spot so reject
  //    digitalWrite(LED1, HIGH);
      WiFiClient TKDClient = TKDServer.available();
      TKDClient.stop();
    }

    //check clients for data -------------------------------------------------------
    
    for(int i = 0; i < MAXSC; i++)
    {
      if (TKDClient[i] && TKDClient[i].connected())
      {
        if(TKDClient[i].available())
        {
          // If Any Data Was Available We Read IT
          while(TKDClient[i].available()) 
          {
            // Read From Client
            //Serial.println(TKDClient[i].readStringUntil('\n'));
            // Reply To Client
            String masuk=TKDClient[i].readStringUntil('\n');
            Serial.println(masuk);
            
            if(masuk.indexOf("a")>=0){
              Serial.println("Hore");
              SkorKiri++;
              EEPROM.write(0,SkorKiri);
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }
            
            if(masuk.indexOf("b")>=0){
              Serial.println("Hore");
              SkorKiri--;
              EEPROM.write(0,SkorKiri);
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }
            
            if(masuk.indexOf("c")>=0){
              Serial.println("Hore");
              SkorKanan++;
              EEPROM.write(1,SkorKanan);
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }
            
            if(masuk.indexOf("d")>=0){
              Serial.println("Hore");
              SkorKanan--;
              EEPROM.write(1,SkorKanan);
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }

            if(masuk.indexOf("e")>=0){
              Serial.println("Hore");
              SkorKiri=0;
              SkorKanan=0;
              EEPROM.write(1,SkorKanan);
              EEPROM.write(0,SkorKiri);
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }
            
            if(masuk.indexOf("f")>=0){
              Serial.println("Hore");
              SkorKiri=0;
              SkorKanan=0;
              digitalWrite(Buzz, LOW);
              delay(100);
            }else{
              digitalWrite(Buzz, HIGH);
            }

            
            TKDClient[i].println("");
          }
        }
      }
    }
  }
