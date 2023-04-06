#include <Adafruit_GFX.h>   
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>   
#include <Fonts/Org_01.h>  
#include <EEPROM.h>    
bool backsensed = false;
bool resetsensed = false;
#define YP A2
#define XM A1 
#define YM 6 
#define XP 7 
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define BLACK   0x0000
int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY   tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
int currentpcolour;
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define DRAW_LOOP_INTERVAL 50 
#define addr 0
int currentpage;
int currentWing;      
int flX, flY, fallRate;
int pillarPos, gapPosition;
int score;           
int highScore = 0;    
bool running = false; 
bool crashed = false;  
bool scrPress = false;
long nextDrawLoopRunTime;
int redval;
int greenval;
int blueval;
int redpos = BAR_MINY + 12;
int greenpos = BAR_MINY + 12;
int bluepos = BAR_MINY + 12;
int oldrpos = redpos;
int oldgpos = greenpos;
int oldbpos = bluepos;
int x, y;



void drawHome()
{

  tft.fillScreen(BLACK);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);    
  tft.fillRoundRect(60, 180, 200, 40, 8, RED);
  tft.drawRoundRect(60, 180, 200, 40, 8, WHITE); 
  tft.fillRoundRect(60, 130, 200, 40, 8, RED);  
  tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);
  tft.fillRoundRect(60, 80, 200, 40, 8, RED);
  tft.drawRoundRect(60, 80, 200, 40, 8, WHITE); 
  tft.setCursor(60, 20);
  tft.setTextSize(2);
  tft.setFont();  
  tft.setTextColor(WHITE);
  tft.print("Select an example!");
  tft.setCursor(70, 50);
  tft.setTextSize(2);
  tft.setTextColor(LIME);
  tft.print("Minuka");
  tft.setTextColor(BLACK);
  tft.setCursor(65, 195);
  tft.print("   FlappyBird");
  tft.setCursor(105, 145);
  tft.print("RGB-Mixer");
  tft.setCursor(80, 95);
  tft.print("Oscilloscope");
}



void setup()
{
  tft.reset();
  tft.begin(0x9341);
  Serial.begin(9600);
  Serial.println();
  Serial.print("reading id...");
  delay(500);
  Serial.println(tft.readID(), HEX);
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  currentpage = 0;

  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(50, 140);
  tft.print("Loading...");

  tft.setTextColor(tft.color565(255, 255, 0));
  tft.setCursor(30, 70);
  tft.print("By:");

  tft.setCursor(30, 100);
  tft.print("Minuka");

  for (int i; i < 250; i++)
  {
    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, RED);
    delay(0.000000000000000000000000000000000000000000000000001);
  }

  tft.fillScreen(BLACK);

  drawHome();

}



void loop()
{

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();     
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (currentpage == 0)
  {
    if (p.z > 10 && p.z < 1000)
    {
      if (p.x > 736 && p.x < 855 && p.y > 255 && p.y < 725  && p.z > MINPRESSURE && p.z < MAXPRESSURE)
      {
        Serial.println("FlappyBird");

        tft.fillRoundRect(60, 180, 200, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(60, 180, 200, 40, 8, RED);
        tft.drawRoundRect(60, 180, 200, 40, 8, WHITE);
        tft.setCursor(65, 195);

        tft.println("   FlappyBird");
        delay(70);

        currentpage = 1;

        nextDrawLoopRunTime = millis() + DRAW_LOOP_INTERVAL;
        crashed = false;
        running = false;
        scrPress = false;

        startGame();
      }

      else if (p.x > 563 && p.x < 683 && p.y > 275 && p.y < 750)
      {
        Serial.println("RGB-MIXER");

        tft.fillRoundRect(60, 130, 200, 40, 8, WHITE); 
        delay(70);

        tft.fillRoundRect(60, 130, 200, 40, 8, RED);
        tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);  
        tft.setCursor(105, 145);

        tft.print("RGB-Mixer");
        delay(70);

        currentpage = 2;
        x = 0;
        y = 0;
        p.z = 0;
        redpos = BAR_MINY + 12;
        greenpos = BAR_MINY + 12;
        bluepos = BAR_MINY + 12;
        oldrpos = redpos;
        oldgpos = greenpos;
        oldbpos = bluepos;

        drawrgb();
      }


      if (p.x > 403 && p.x < 525 && p.y > 271 && p.y < 725)
      {
        Serial.println("Oscilloscope");

        currentpage = 3;

        tft.fillRoundRect(60, 80, 200, 40, 8, WHITE);
        delay(70);

        tft.fillRoundRect(60, 80, 200, 40, 8, RED);
        tft.drawRoundRect(60, 80, 200, 40, 8, WHITE);

        tft.setCursor(80, 95);
        tft.print("Oscilloscope");
        delay(70);

        drawOSC();

      }
    }

  }

  if (currentpage == 1)
  {
    senseBack();
    if (millis() > nextDrawLoopRunTime && !crashed) {
      drawLoop();
      checkCollision();
      nextDrawLoopRunTime += DRAW_LOOP_INTERVAL;
    }
    if (backsensed)
    {
      currentpage = 0;
      drawHome();
    }


    sensereset();

    ResetScore();

  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE && !scrPress && !resetsensed && !backsensed) {     
      if (crashed) {
      
        startGame();
      }
      else if (!running) {
        // clear and restart
        tft.fillRect(0, 0, 320, 80, BLUE);
        running = true;
      }
      else
      {
        // Go up
        fallRate = -8;
        scrPress = true;
      }
    }
    else if (p.z == 0 && scrPress) {
      scrPress = false;
    }
  }

  if (currentpage == 2)
  {

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
      x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
      y = map(p.y, TS_MINY, TS_MAXY,  tft.height(), 0) + 30;

      tft.fillRoundRect(200, 5, 70, 40, 8, tft.color565(redval, greenval, blueval));

      if (y > 42 && y < 250)
      {
        if (x > 180 && x < 220)
        {

          redval = map(y, 42, 250, 0, 255);
          oldrpos = redpos;
          tft.fillRect(oldrpos, REDBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, BLACK);
          redpos = y;
          tft.fillRect(redpos, REDBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, RED);     
          tft.fillCircle(14, REDBAR_MINX + 15, 10, tft.color565(redval, 0, 0));


        }

        if (x > 115 && x < 150)
        {
          greenval = map(y, 42, 250, 0, 255);
          oldgpos = greenpos;
          tft.fillRect(oldgpos, GREENBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, BLACK);
          greenpos = y;
          tft.fillRect(greenpos, GREENBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, GREEN);     
          tft.fillCircle(14, GREENBAR_MINX + 15, 10, tft.color565(0, greenval, 0));


        }
        if (x > 40 && x < 80)
        {
          blueval = map(y, 42, 250, 0, 255);
          oldbpos = bluepos;
          tft.fillRect(oldbpos, BLUEBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, BLACK);
          bluepos = y;
          tft.fillRect(bluepos, BLUEBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, BLUE);
          tft.fillCircle(14, BLUEBAR_MINX + 15, 10, tft.color565(0, 0, blueval));


        }
      }

      if (p.y > 743 && p.x < 247 && p.x > 150 && p.y < 875)
      {
        tft.fillRoundRect(5, 5, 50, 30, 8, WHITE);
        delay(70);
        tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
        tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
        tft.setCursor(15, 15);
        tft.print("<-");
        delay(70);
        tft.fillRoundRect(5, 5, 50, 30, 8, BLACK);
        currentpage = 0;
        drawHome();
        p.x = 160;
        p.y = 760;
        redval = 0;
        blueval = 0;
        greenval = 0;
        redpos = BAR_MINY + 12;
        greenpos = BAR_MINY + 12;
        bluepos = BAR_MINY + 12;
        oldrpos = redpos;
        oldgpos = greenpos;
        oldbpos = bluepos;

      }
    }

  }

  if (currentpage == 3)
  {
    for (uint16_t j = 0; j <= tft.width() + 1; j++ )

    {
      float volt;
      float signalY = map(analogRead(A5),  0,  4095,  tft.height() - 1,  1   ) ;


      tft.drawFastVLine( j,  46, tft.height(), BLACK);
      tft.drawFastHLine(j, 180.00, 1, RED);
      tft.drawFastHLine(j, 195.00, 1, WHITE);

      tft.drawPixel(j, signalY, GOLD);


      if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
        if (p.y > 743 && p.x < 247 && p.x > 150 && p.y < 875)
        {
          tft.fillRoundRect(5, 5, 50, 30, 8, WHITE);
          delay(70);
          tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
          tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
          tft.setCursor(15, 15);
          tft.print("<-");
          delay(70);
          tft.fillRoundRect(5, 5, 50, 30, 8, BLACK);
          currentpage = 0;
          drawHome();
          p.x = 160;
          p.y = 760;
          return;
        }

    }
  }

}

void drawLoop() { //Flappy bird functions
  // clear moving items
  clearPillar(pillarPos, gapPosition); 
  clearFlappy(flX, flY);           

  // Move items
  if (running) {
    flY += fallRate;
    fallRate++;

    pillarPos -= 5;
    if (pillarPos == 0) {
      score++;
    }
    else if (pillarPos < -50) {
      pillarPos = 320;
      gapPosition = random(20, 120);  
    }
  }

  // draw moving items & animate
  drawPillar(pillarPos, gapPosition); 
  drawFlappy(flX, flY);            
  switch (currentWing) {   
    case 0: case 1: drawWing1(flX, flY); break;  //Wing down
    case 2: case 3: drawWing2(flX, flY); break;  //Wing middle
    case 4: case 5: drawWing3(flX, flY); break;  //Wing up

  }
  if (score == EEPROM.read(0) ) 
    currentpcolour = YELLOW;

  else
    currentpcolour = GREEN;

  currentWing++;   //flap the wing
  if (currentWing == 6  ) currentWing = 0; 

}

void checkCollision() {


  if (flY > 206) crashed = true;

 
  if (flX + 34 > pillarPos && flX < pillarPos + 50)
    if (flY < gapPosition || flY + 24 > gapPosition + 90)
      crashed = true;

  if (crashed) 
  {
    tft.setTextColor(RED);  
    tft.setTextSize(5);     
    tft.setCursor(20, 75);   
    tft.print("Game Over!"); 

    tft.setTextSize(4);      
    tft.setCursor(75, 125);  
    tft.print("Score:");     

    tft.setCursor(220, 125); 
    tft.setTextSize(5);      
    tft.setTextColor(WHITE);
    tft.print(score);        

    if (score > highScore) { 
    highScore = score;
      EEPROM.write(addr, highScore); 
      tft.setCursor(75, 175);        
      tft.setTextSize(4);             
      tft.setTextColor(YELLOW);
      tft.print("NEW HIGH!");         
    }

    running = false;    

    delay(1000);
  }
}

void drawPillar(int x, int gap) {  
  tft.fillRect(x + 2, 2, 46, gap - 4, currentpcolour);
  tft.fillRect(x + 2, gap + 92, 46, 136 - gap, currentpcolour);

  tft.drawRect(x, 0, 50, gap, BLACK);
  tft.drawRect(x + 1, 1, 48, gap - 2, BLACK);
  tft.drawRect(x, gap + 90, 50, 140 - gap, BLACK);
  tft.drawRect(x + 1, gap + 91 , 48, 138 - gap, BLACK);
}

void clearPillar(int x, int gap) {
  tft.fillRect(x + 45, 0, 5, gap, BLUE);
  tft.fillRect(x + 45, gap + 90, 5, 140 - gap, BLUE);
}

void clearFlappy(int x, int y) {  
  tft.fillRect(x, y, 34, 24, BLUE);
}

void drawFlappy(int x, int y) { 
  tft.fillRect(x + 2, y + 8, 2, 10, BLACK);
  tft.fillRect(x + 4, y + 6, 2, 2, BLACK);
  tft.fillRect(x + 6, y + 4, 2, 2, BLACK);
  tft.fillRect(x + 8, y + 2, 4, 2, BLACK);
  tft.fillRect(x + 12, y, 12, 2, BLACK);
  tft.fillRect(x + 24, y + 2, 2, 2, BLACK);
  tft.fillRect(x + 26, y + 4, 2, 2, BLACK);
  tft.fillRect(x + 28, y + 6, 2, 6, BLACK);
  tft.fillRect(x + 10, y + 22, 10, 2, BLACK);
  tft.fillRect(x + 4, y + 18, 2, 2, BLACK);
  tft.fillRect(x + 6, y + 20, 4, 2, BLACK);
  tft.fillRect(x + 12, y + 2, 6, 2, YELLOW);
  tft.fillRect(x + 8, y + 4, 8, 2, YELLOW);
  tft.fillRect(x + 6, y + 6, 10, 2, YELLOW);
  tft.fillRect(x + 4, y + 8, 12, 2, YELLOW);
  tft.fillRect(x + 4, y + 10, 14, 2, YELLOW);
  tft.fillRect(x + 4, y + 12, 16, 2, YELLOW);
  tft.fillRect(x + 4, y + 14, 14, 2, YELLOW);
  tft.fillRect(x + 4, y + 16, 12, 2, YELLOW);
  tft.fillRect(x + 6, y + 18, 12, 2, YELLOW);
  tft.fillRect(x + 10, y + 20, 10, 2, YELLOW);
  tft.fillRect(x + 18, y + 2, 2, 2, BLACK);
  tft.fillRect(x + 16, y + 4, 2, 6, BLACK);
  tft.fillRect(x + 18, y + 10, 2, 2, BLACK);
  tft.fillRect(x + 18, y + 4, 2, 6, WHITE);
  tft.fillRect(x + 20, y + 2, 4, 10, WHITE);
  tft.fillRect(x + 24, y + 4, 2, 8, WHITE);
  tft.fillRect(x + 26, y + 6, 2, 6, WHITE);
  tft.fillRect(x + 24, y + 6, 2, 4, BLACK);
  tft.fillRect(x + 20, y + 12, 12, 2, BLACK);
  tft.fillRect(x + 18, y + 14, 2, 2, BLACK);
  tft.fillRect(x + 20, y + 14, 12, 2, RED);
  tft.fillRect(x + 32, y + 14, 2, 2, BLACK);
  tft.fillRect(x + 16, y + 16, 2, 2, BLACK);
  tft.fillRect(x + 18, y + 16, 2, 2, RED);
  tft.fillRect(x + 20, y + 16, 12, 2, BLACK);
  tft.fillRect(x + 18, y + 18, 2, 2, BLACK);
  tft.fillRect(x + 20, y + 18, 10, 2, RED);
  tft.fillRect(x + 30, y + 18, 2, 2, BLACK);
  tft.fillRect(x + 20, y + 20, 10, 2, BLACK);
}




void drawWing1(int x, int y) 
{
  tft.fillRect(x, y + 14, 2, 6, BLACK);
  tft.fillRect(x + 2, y + 20, 8, 2, BLACK);
  tft.fillRect(x + 2, y + 12, 10, 2, BLACK);
  tft.fillRect(x + 12, y + 14, 2, 2, BLACK);
  tft.fillRect(x + 10, y + 16, 2, 2, BLACK);
  tft.fillRect(x + 2, y + 14, 8, 6, WHITE);
  tft.fillRect(x + 8, y + 18, 2, 2, BLACK);
  tft.fillRect(x + 10, y + 14, 2, 2, WHITE);
}




void drawWing2(int x, int y) 
{
  tft.fillRect(x + 2, y + 10, 10, 2, BLACK);
  tft.fillRect(x + 2, y + 16, 10, 2, BLACK);
  tft.fillRect(x, y + 12, 2, 4, BLACK);
  tft.fillRect(x + 12, y + 12, 2, 4, BLACK);
  tft.fillRect(x + 2, y + 12, 10, 4, WHITE);
}




void drawWing3(int x, int y) 
{
  tft.fillRect(x + 2, y + 6, 8, 2, BLACK);
  tft.fillRect(x, y + 8, 2, 6, BLACK);
  tft.fillRect(x + 10, y + 8, 2, 2, BLACK);
  tft.fillRect(x + 12, y + 10, 2, 4, BLACK);
  tft.fillRect(x + 10, y + 14, 2, 2, BLACK);
  tft.fillRect(x + 2, y + 14, 2, 2, BLACK);
  tft.fillRect(x + 4, y + 16, 6, 2, BLACK);
  tft.fillRect(x + 2, y + 8, 8, 6, WHITE);
  tft.fillRect(x + 4, y + 14, 6, 2, WHITE);
  tft.fillRect(x + 10, y + 10, 2, 4, WHITE);
}



void ResetScore()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint(); 
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { 

  }
  if (p.x < 199 && p.y < 293 && running == false) 
  {
    EEPROM.write(addr, 0); 
    startGame(); 
  }
}



void sensereset()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();    
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.x < 199 && p.y < 293 && !running)
    resetsensed = true;

  else
    resetsensed = false;
}


void startGame() 
{
 
  flX = 50;
  flY = 125;
  fallRate = 1;
  pillarPos = 320; 
  gapPosition = 60;
  crashed = false;  
  score = 0;     
  highScore = EEPROM.read(addr);
  tft.setFont(&Org_01);            
  tft.fillScreen(BLUE);             
  tft.setTextColor(YELLOW);         
  tft.setTextSize(3);               
  tft.setCursor(5, 20);           
  tft.println("Flappy Bird");
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println(" Tap to begin!!");
  tft.setTextColor(GREEN);
  tft.setCursor(60, 60);
  tft.print("Top Score : ");
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.print(highScore);
  tft.setTextSize(2);
  tft.fillRoundRect(240, 5, 250, 15, 8, WHITE);
  tft.drawRoundRect(240, 5, 250, 15, 8, RED);
  tft.setCursor(250, 15);
  tft.println("RESET");
  tft.fillRoundRect(240, 30, 250, 15, 8, WHITE);
  tft.drawRoundRect(240, 30, 250, 15, 8, RED);
  tft.setCursor(250, 40);
  tft.print("BACK");



  int ty = 230; int tx = 0;
  for ( tx = 0; tx <= 300; tx += 20)
  {
    tft.fillTriangle(tx, ty, tx + 10, ty, tx, ty + 10, GREEN);
    tft.fillTriangle(tx + 10, ty + 10, tx + 10, ty, tx, ty + 10, YELLOW);
    tft.fillTriangle(tx + 10, ty, tx + 20, ty, tx + 10, ty + 10, YELLOW);
    tft.fillTriangle(tx + 20, ty + 10, tx + 20, ty, tx + 10, ty + 10, GREEN);
  }

  nextDrawLoopRunTime = millis() + DRAW_LOOP_INTERVAL;
}



void senseBack()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.y < 305 && p.x < 285 && p.x > 239 && !running)
  {
    backsensed = true;

  }
  else
    backsensed = false;
}



void drawrgb()  
{
  tft.fillScreen(BLACK);
  tft.setCursor(90, 20);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("COLOUR : ");

  tft.drawRect(BAR_MINY, BLUEBAR_MINX, BAR_HEIGHT, BAR_WIDTH, WHITE); 

  tft.drawRect(BAR_MINY, GREENBAR_MINX, BAR_HEIGHT, BAR_WIDTH, WHITE);  

  tft.drawRect(BAR_MINY, REDBAR_MINX, BAR_HEIGHT, BAR_WIDTH, WHITE);

  tft.fillRect(BAR_MINY + 12, REDBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, RED);

  tft.fillRect(BAR_MINY + 12, GREENBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, GREEN);

  tft.fillRect(BAR_MINY + 12, BLUEBAR_MINX + 3, BAR_WIDTH - 10, BAR_WIDTH - 5, BLUE);


  tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
  tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
  tft.setCursor(15, 15);
  tft.setTextColor(BLACK);
  tft.print("<-");
  delay(300);



}



void drawOSC() 
{
  tft.fillScreen(BLACK);
  tft.fillRoundRect(5, 5, 50, 30, 8, BLUE);
  tft.drawRoundRect(5, 5, 50, 30, 8, WHITE);
  tft.setCursor(15, 15);
  tft.print("<-");
}
