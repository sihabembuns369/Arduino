#define USE_HELIX 
#define USE_A2DP
#define USE_SDFAT

#include "AudioTools.h"
#include "BluetoothA2DPSource.h"
#include "AudioCodecs/CodecMP3Helix.h"

using namespace audio_tools;  

const char *startFilePath="/";
const char* ext="mp3";
AudioSourceSdFat source(startFilePath, ext);
A2DPStream out = A2DPStream::instance();  // A2DP output - A2DPStream is a singleton!
MP3DecoderHelix decoder;
AudioPlayer player(source, out, decoder);


void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // setup output - We send the output via A2DP to a "LEXON MINO L" Bluetooth Speaker
//  auto cfg = out.defaultConfig(TX_MODE);
  cfg.name = "BT-SPEAKER";
  out.begin(cfg);

  // setup player
  player.setVolume(0.1);
  player.begin();

}

void loop() {
  player.copy();
}
