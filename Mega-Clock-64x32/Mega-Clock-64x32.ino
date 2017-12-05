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

#include <DS3231.h>

#define CLK 11  
#define OE  9
#define LAT 10

#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define pw  3000
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

DS3231  rtc(SDA, SCL);

void setup() {
  matrix.begin();  
  rtc.begin();
  
//  rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
//  rtc.setTime(21, 58, 0);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(12, 5, 2017);   // Set the date to January 1st, 2014
}
int r = 0;
int g = 0;
int b = 7;

void loop() {
  
//  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(r, g, b));
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), 0);

//  matrix.updateDisplay();
    
//  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));

  matrix.setTextSize(2);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  uint8_t w = 0;
  
  char* timeStr = rtc.getTimeStr(FORMAT_SHORT); 
  for (int i = 0; i < 5; i++) {
    matrix.setCursor(3, 8);  // start at top left, with 3 pixel of spacing
    r = (r + 4) % 7;
    g = (g + 3) % 7;
    b = (b + 5) % 7 + 1;
    matrix.setTextColor(matrix.Color333(r, g, b));
    matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(r, 4, b));
    for (w=0; w< 5 - 1; w++) {
      matrix.print(timeStr[w]);
      delay(500);
    }
    matrix.fillRect(50, 8, 12, 15, 0);
    matrix.print(timeStr[4]);
    delay(2000);
  }
//  delay (5000);


} 


