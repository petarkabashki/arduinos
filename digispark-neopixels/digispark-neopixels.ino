// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

int delayval = 1000; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

int r = 5;
int g = 9;
int b = 0;

void clock() {
  pixels.clear();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(
      0,//(i < g ? 50: 0),
      (i <= r ? 50: 0),
      0//(i < b ? 50: 0)
      )); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(1000);
  pixels.clear();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(
      (i < g ? 50: 0),
      0,//(i < r ? 50: 0),
      0//(i < b ? 50: 0)
      )); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(1000);
  pixels.clear();
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(
      0,//(i < g ? 50: 0),
      0,//(i < r ? 50: 0),
      (i <= b ? 50: 0)
      )); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(1000);

//  delay(delayval);
  b++;
  b %= 12;
}

bool inRange(int st, int len, int i){
  return
    (i >= st) && (i < st + len)
    ||
    (i + NUMPIXELS >= st) && (i < st + len - NUMPIXELS);
}

int st = 0;
int len = 7;
//int color = ;
int cnt = 0;

void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  pixels.clear();
  st = cnt % 12;
  
  for(int i=0;i<NUMPIXELS;i++){
    bool inR = inRange(st, len, i);
    pixels.setPixelColor(i, pixels.Color(
      inR && (cnt < 24) ? 50 + (int)(150 * cnt / 24): 0,
      inR && (cnt >= 24 & cnt < 48) ? 50 + (int)(150 * (cnt % 24) / 24): 0,
      inR && (cnt >= 48 & cnt < 72) ? 50 +  (int)(150 * (cnt % 24) / 24): 0
      )); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(100);
  cnt++;
  cnt %= 72; 
}


