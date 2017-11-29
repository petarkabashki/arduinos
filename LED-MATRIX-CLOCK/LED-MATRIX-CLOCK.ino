// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950

#include <avr/pgmspace.h>
#include <LedControl.h>
#include "MaxMat.h";
#include <virtuabotixRTC.h>

const int numDevices = 4;      // number of MAX7219s used
const long scrollDelay = 5;   // adjust scrolling speed

#define uchar unsigned char
#define ulong unsigned long

ulong bufferLong [14] = {0}; 


// Creation of the Real Time Clock Object
//SCLK -> 6, I/O -> 7, CE -> 8
virtuabotixRTC myRTC(2,3,4);


LedControl lc=LedControl(12,11,10,numDevices);

//const uchar scrollText[7] PROGMEM ={
////    "  THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG 1234567890 the quick brown fox jumped over the lazy dog   \0"
//    "00000\0"
//    };

void clearDisplay(){
  bufferLong[0] = 0;
  for(int i = 0; i< numDevices; i++){
    lc.clearDisplay(i);  
  }  
}

void setup(){
//  void setDS1302Time(uint8_t seconds, uint8_t minutes,       // This function sets the time on the     //|
//                       uint8_t hours, uint8_t dayofweek,       // DS1302                                 //|
//                       uint8_t dayofmonth, uint8_t month,                                                //|
//                       int year);      
//                       
//  myRTC.setDS1302Time(0, 10,       // This function sets the time on the     //|
//                       2, 6,       // DS1302                                 //|
//                       12, 2,                                                //|
//                       2017);      
                       
    Serial.begin(9600);
    for (int x=0; x<numDevices; x++){
        lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
        lc.setIntensity(x,8);       // Set the brightness to default value
        lc.clearDisplay(x);         // and clear the display
    }
}

void loop(){ 
    myRTC.updateTime();
//    Serial.print("Current Date / Time: ");
//    Serial.print(myRTC.dayofmonth);
//    Serial.print("/");
//    Serial.print(myRTC.month);
//    Serial.print("/");
//    Serial.print(myRTC.year);
//    Serial.print(" ");
//    Serial.print(myRTC.hours);
//    Serial.print(":");
//    Serial.print(myRTC.minutes);
//    Serial.print(":");
//    Serial.println(myRTC.seconds);
    clearDisplay();
    unsigned char text[] = { "          \0"};
    String timeStr = (myRTC.hours < 10 ? "0" : "") + String(myRTC.hours) + ":" + myRTC.minutes;
    uchar utimeStr[6];
    timeStr.getBytes(utimeStr, 5);
    for(int j = 0; j < 8; j++)
    { 
      loadBufferLong(' ');
    }
    for(int i = 0; i < 5; i++)
    {
      loadBufferLong(timeStr.charAt(i));
    }
    loadBufferLong('~' + 2);
    delay(3000);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scrollFont() {
    for (int counter=0x20;counter<0x80;counter++){
        loadBufferLong(counter);
        delay(500);
    }
}

// Scroll Message
void scrollMessage(uchar * messageString) {
    int counter = 0;
    int myChar=0;
    do {
        // read back a char 
        myChar =  pgm_read_byte_near(messageString + counter); 
        if (myChar != 0){
            loadBufferLong(myChar);
        }
        counter++;
    } 
    while (myChar != 0);
}
// Load character into scroll buffer
void loadBufferLong(int ascii){
    if (ascii >= 0x20 && ascii <=0x80){
        for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data
            unsigned long x = bufferLong [a*2];     // Load current scroll buffer
            x = x | c;                              // OR the new character onto end of current
            bufferLong [a*2] = x;                   // Store in buffer
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);     // Index into character table for kerning data
        for (byte x=0; x<count;x++){
            rotateBufferLong();
            printBufferLong();
            delay(scrollDelay);
        }
    }
}
// Rotate the buffer
void rotateBufferLong(){
    for (int a=0;a<7;a++){                      // Loop 7 times for a 5x7 font
        unsigned long x = bufferLong [a*2];     // Get low buffer entry
        byte b = bitRead(x,31);                 // Copy high order bit that gets lost in rotation
        x = x<<1;                               // Rotate left one bit
        bufferLong [a*2] = x;                   // Store new low buffer
        x = bufferLong [a*2+1];                 // Get high buffer entry
        x = x<<1;                               // Rotate left one bit
        bitWrite(x,0,b);                        // Store saved bit
        bufferLong [a*2+1] = x;                 // Store new high buffer
    }
}  
// Display Buffer on LED matrix
void printBufferLong(){
  for (int a=0;a<7;a++){                    // Loop 7 times for a 5x7 font
    unsigned long x = bufferLong [a*2+1];   // Get high buffer entry
    byte y = x;                             // Mask off first character
    lc.setRow(3,a,y);                       // Send row to relevent MAX7219 chip
    x = bufferLong [a*2];                   // Get low buffer entry
    y = (x>>24);                            // Mask off second character
    lc.setRow(2,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>16);                            // Mask off third character
    lc.setRow(1,a,y);                       // Send row to relevent MAX7219 chip
    y = (x>>8);                             // Mask off forth character
    lc.setRow(0,a,y);                       // Send row to relevent MAX7219 chip
  }
}
