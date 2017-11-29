#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

const byte IR_STAR = 11;
const byte IR_SHARP = 12;
const byte IR_UP = 13;
const byte IR_DOWN = 14;
const byte IR_LEFT = 15;
const byte IR_RIGHT = 16;
const byte IR_OK = 17;

#include <TM1638.h>

// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);
int c = 0;
boolean running = false;
boolean encoding = true;
//ir module arduino
byte translateIR(int code) {
  switch(code)
  {
    case 0xFFA25D:
      return 1;
      break;
    case 0xFF629D:
      return 2;
      break;
    case 0xFFE21D:
      return 3;
      break;
    case 0xFF22DD:
      return 4;
      break;
    case 0xFF02FD:
      return 5;
      break;
    case 0xFFC23D:
      return 6;
      break;
    case 0xFFE01F:
      return 7;
      break;
    case 0xFFA857:
      return 8;
      break;
    case 0xFF906F:
      return 9;
      break;
    case 0xFF9867:
      return 0;
      break;
    case 0xFF6897:
      return IR_STAR;
      break;
    case 0xFFB04F:
      return IR_SHARP;
      break;
    case 0xFF18E7:
      return IR_UP;
      break;
    case 0xFF4AB5:
      return IR_DOWN;
      break;
    case 0xFF10EF:
      return IR_LEFT;
      break;
    case 0xFF5AA5:
      return IR_RIGHT;
      break;
    case 0xFF38C7:
      return IR_OK;
      break;
      
  }  
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

  byte keys = module.getButtons();
//
//  module.setDisplayToDecNumber(c, 0);
//
  if(keys & 0b00000001) {
    running = !running;
  }
//  if(running){
//    c++;
//  }
//  if(keys & 0b00000010) {
//    c = 0;
//  }
//  delay(200);
//  module.setLEDs(keys);
  if (!running){
    if(irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      byte res = translateIR(results.value);
      switch(res)
      {
        case IR_SHARP:
          encoding = !encoding;
          break;
        case IR_OK:
          running = !running;
          break;
        case IR_UP:
          c *= 10;
          break;
        case IR_DOWN:
          c /= 10;
          break;
        case IR_LEFT:
          c--;
          break;
        case IR_RIGHT:
          c++;
          break;
         
        default:
          c = c / 10 * 10 + res;
          break;
      };
    }
    if(running){
//      irrecv.disableIRIn(); // Start the receiver
      c++;
    } else {
//      irrecv.enableIRIn(); // Start the receiver
      irrecv.resume(); // Receive the next value

    }

//    module.setLED(c);
    module.setDisplayToDecNumber(c, 0, false);
    delay(500);
  }

}

