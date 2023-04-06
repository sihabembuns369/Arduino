
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <SmartMatrix3.h>

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 32;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 32 (untuk 1 baris), 64 (untuk 2 baris)
const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB12_16ROW_32COL_MOD4SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_HUB12_MODE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kIndexedLayerOptions = (SMARTMATRIX_OPTIONS_HUB12_MODE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);

const int defaultBrightness = (15*255)/100;        // full (100%) brightness
//const int defaultBrightness = (15*255)/100;       // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0, 0, 0};


RtcDateTime now;

void setup() {
  
  Serial.begin(115200);

  // setup matrix
  matrix.addLayer(&indexedLayer); 
  matrix.begin();

  matrix.setBrightness(defaultBrightness);
}

void loop() {


  // clear screen before writing new text
  indexedLayer.fillScreen(0);

  indexedLayer.setFont(font5x7);
  
  //Panel 1 Kiri atau Atas
//  indexedLayer.drawString(0, 1,  1, "I LOVE");
//  indexedLayer.drawString(0, 9, 1, "U NENG");

TeksJalan(8, 50);

  indexedLayer.swapBuffers();
  delay(1000);
  
}


static char *teks[] = {"Teks berjalan dengan DMDESP"};

void TeksJalan(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
//  int width = indexedLayer.width();

  indexedLayer.setFont(font5x7);
  int fullScroll =  teks[0] + 32;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
     indexedLayer.drawString(32 - x, y, teks);
  }  

}
