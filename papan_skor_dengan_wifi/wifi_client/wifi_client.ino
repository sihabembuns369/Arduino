  #include "Wire.h"
  #include "ESP8266WiFi.h"
  #define       LED0      2         // WIFI Module LED
  #define       Tombol1    D5
  #define       Tombol2    D6 
  #define       Tombol3    D2
  #define       Tombol4    D1
  #define       Tombol5    D4 
  #define       TWI_FREQ  400000L   // I2C Frequency Setting To 400KHZ
//------------------------------------------------------------------------------------
// BUTTON Variables
//------------------------------------------------------------------------------------
  int           ButtonState;
  int           LastButtonState   = LOW;
  int           LastDebounceTime  = 0;
  int           DebounceDelay     = 50;
  const String  ButtonColor       = "BLU";
//------------------------------------------------------------------------------------
// LED Delay Variables
//------------------------------------------------------------------------------------
  int           LEDState          = LOW;
  unsigned long CurrMillis        = 0;
  unsigned long PrevMillis        = 0;
  unsigned long Interval          = 1000;
//------------------------------------------------------------------------------------
// Authentication Variables
//------------------------------------------------------------------------------------
  char*         TKDssid;
  char*         TKDpassword;
  IPAddress     TKDServer(192,168,4,1);
  WiFiClient    TKDClient;
//====================================================================================

  void setup() 
  {
    /* ----------------------------------------------------------------------
     * Setting The I2C Pins SDA, SCL
     * Because We Didnt Specify Any Pins The Defult
     * SDA = D4 , SCL = D5  For ESP8266 Dev Kit Node MCU v3
     --------------------------------------------------------------------- */
    Wire.begin();                   // Begginning The I2C
    
    // Setting Up The I2C Of The MPU9250 ------------------------------------
    Wire.setClock(TWI_FREQ);        // Setting The Frequency MPU9250 Require
        
    // Setting The Serial Port ----------------------------------------------
    Serial.begin(115200);           // Computer Communication
    
    // Setting The Mode Of Pins ---------------------------------------------
    pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
    pinMode(Tombol1, INPUT_PULLUP);
    pinMode(Tombol2, INPUT_PULLUP);
    pinMode(Tombol3, INPUT_PULLUP);
    pinMode(Tombol4, INPUT_PULLUP);
    pinMode(Tombol5, INPUT_PULLUP);
    
   
    digitalWrite(LED0, !LOW);       // Turn WiFi LED Off
    
    // Print Message Of I/O Setting Progress --------------------------------
    Serial.println("\nI/O Pins Modes Set .... Done");

    // Starting To Connect --------------------------------------------------
    WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
    WiFi.begin("TAKEONE");          // The SSID That We Want To Connect To

    // Printing Message For User That Connetion Is On Process ---------------
    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

    // WiFi Connectivity ----------------------------------------------------
    CheckConnectivity();            // Checking For Connection

    // Stop Blinking To Indicate Connected ----------------------------------
    digitalWrite(LED0, !HIGH);
    Serial.println("!-- Client Device Connected --!");

    // Printing IP Address --------------------------------------------------
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
    Serial.print  ("Server IP Address : ");
    Serial.println(TKDServer);
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
    
    // Conecting The Device As A Client -------------------------------------
    TKDRequest();
  }


  
  void loop()
  {

    ReadButton();
   
  }



  void ReadButton()
  {
    
    int Baca1 = digitalRead(Tombol1);
    int Baca2 = digitalRead(Tombol2);
    int Baca3 = digitalRead(Tombol3);
    int Baca4 = digitalRead(Tombol4);
    int Baca5 = digitalRead(Tombol5);
    
        
        if(Baca1 == LOW)
        {
          
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("a");
          TKDClient.flush();
          delay(400);
        }

        if(Baca2 == LOW)
        {
          
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("b");
          TKDClient.flush();
          delay(400);
  
        }

      if(Baca3 == LOW)
        {
          
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("c");
          TKDClient.flush();
          delay(400);
        }

        if(Baca4 == LOW)
        {
          
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("d");
          TKDClient.flush();
          delay(400);
        }
        if(Baca5 == LOW)
        {
          
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("e");
          TKDClient.flush();
          delay(400);
        }
  }



  void CheckConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        digitalWrite(LED0, !HIGH);
        delay(250);
        digitalWrite(LED0, !LOW);
        delay(250);
        Serial.print(".");
      }
      Serial.println("");
    }
  }



  void TKDRequest()
  {
    // First Make Sure You Got Disconnected
    TKDClient.stop();

    // If Sucessfully Connected Send Connection Message
    if(TKDClient.connect(TKDServer, 9001))
    {
      Serial.println    ("<" + ButtonColor + "-CONNECTED>");
      TKDClient.println ("<" + ButtonColor + "-CONNECTED>");
    }
  }
