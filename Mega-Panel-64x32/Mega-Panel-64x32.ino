/***************************************************
* 
*NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!
*
***************************************************
* 64x32 RGB LED Matrix - 4mm pitch
* ****************************************************
* testshapes demo for RGBmatrixPanel library.
* Demonstrates the drawing abilities of the RGBmatrixPanel library.
* For 32x64 RGB LED matrix.
 
* @author lg.gang(lg.gang@qq.com)
* @version  V1.0
* @date  2016-9-6
  
* GNU Lesser General Public License.
* See <http://www.gnu.org/licenses/> for details.
* All above must be included in any redistribution
* ****************************************************/ 
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11  
#define OE  9
#define LAT 10

#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define pw  3000
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {
  delay(1000);
  matrix.begin();
  
}

void loop() {

  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
  delay(pw);

  // fix the screen with green
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));
  delay(pw);
  
  // fix the screen with white
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 7, 7));
  delay(pw);
  
  // fix the screen with red
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 0, 0));
  delay(pw);
  
  // fix the screen with blue
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 0, 7));
  delay(pw);
 // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  
  // draw a box in yellow
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(7, 7, 0));
  delay(pw);
  
  // draw a box in fuchsia
  matrix.drawRect(5, 5, 53, 23, matrix.Color333(7, 0, 7));
  delay(pw);
  
  // draw a box in yellow
  matrix.drawRect(10, 10, 43, 13, matrix.Color333(7, 1, 3));
  delay(pw);
  
  // draw an 'X' in red
  matrix.drawLine(0, 0, matrix.width()-1, matrix.height()-1, matrix.Color333(7, 0, 0));
  matrix.drawLine(matrix.width()-1, 0, 0, matrix.height()-1, matrix.Color333(7, 0, 0));
  delay(pw);
  
  // draw a blue circle
  matrix.drawCircle(10, 10, 10, matrix.Color333(0, 0, 7));
  delay(pw);
  
  // fill a violet circle
  matrix.fillCircle(40, 21, 10, matrix.Color333(7, 0, 7));
  delay(pw);
  
   // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  
  // draw some text!
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setCursor(3, 0);  // start at top left, with 3 pixel of spacing
  uint8_t w = 0;
  char *str = "Welcome to";
  for (w=0; w<10; w++) {
    matrix.setTextColor(Wheel(w));
    matrix.print(str[w]);
  }

//  matrix.setCursor(13, 8);    // next line
//  for (w=10; w<17; w++) {
//    matrix.setTextColor(Wheel(w));
//    matrix.print(str[w]);
//  }

//  matrix.println();
  matrix.setTextSize(2);
  matrix.setCursor(12, 14);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('M');
  matrix.setCursor(27, 14);
  matrix.setTextColor(matrix.Color333(7,4,0));
  matrix.print('T');
  matrix.setCursor(42, 14);
  matrix.setTextColor(matrix.Color333(4,7,7));
  matrix.print('P');

//  matrix.println();
//  matrix.setCursor(2, 16);
//  matrix.setTextColor(matrix.Color333(7,7,7));
//  matrix.println("I'm always");
//  
//  // print each letter with a rainbow color
//  matrix.setCursor(3, 24);
//  matrix.setTextColor(matrix.Color333(7,0,0));
//  matrix.print('B');
//  matrix.setTextColor(matrix.Color333(7,4,0)); 
//  matrix.print('y');
//  matrix.setTextColor(matrix.Color333(7,7,0));
//  matrix.print(' ');
//  matrix.setTextColor(matrix.Color333(4,7,0)); 
//  matrix.print('U');
//  matrix.setTextColor(matrix.Color333(0,7,0));  
//  matrix.print(' ');
//  matrix.setTextColor(matrix.Color333(0,7,7)); 
//  matrix.print("S");
//  matrix.setTextColor(matrix.Color333(0,4,7)); 
//  matrix.print('i');
//  matrix.setTextColor(matrix.Color333(0,0,7));
//  matrix.print('d');
//  matrix.setTextColor(matrix.Color333(4,0,7)); 
//  matrix.print("e");
//  matrix.setTextColor(matrix.Color333(7,0,4)); 
//  matrix.println("!");
  delay(10000);


} 


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if(WheelPos < 8) {
   return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if(WheelPos < 16) {
   WheelPos -= 8;
   return matrix.Color333(0, 7-WheelPos, WheelPos);
  } else {
   WheelPos -= 16;
   return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}
