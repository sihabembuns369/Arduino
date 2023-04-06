

#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

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
#define LCD_RESET 0
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define BLACK 0x0000
int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GREY tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
int currentpcolour;
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define DRAW_LOOP_INTERVAL 50
#define addr 0

int x, y, z;
bool abc = true;
bool abcd = true;
bool abcde = false;
bool done = true;
bool kopi1 = false;
bool susu1 = false;
bool campur1 = false;
int get;


int harga_kopi = 3000;
int harga_susu = 4000;
int harga_campur = 6000;

unsigned long c ;


///i2c komunikasi
const char *i2c= "";
/////

unsigned long b;
int menit = 1;
int detik = 59;
bool ab =true;
String av;
////untuk coin acceptor
volatile int pulse = 0;
int koin;
