/*
PS/2 To Brook Fighting Board
For the Teensy, only tested on the Teensy-LC
Make sure you get the latest git version of PS2keyboard
https://github.com/PaulStoffregen/PS2Keyboard
*/

#include <PS2Keyboard.h>
//#include <digitalWriteFast.h>

const int DataPin = 4; //The data pin is Pin 1 of the MiniDin-6 (PS/2) connector
const int IRQpin = 3; //The clock pin is Pin 5 of the MiniDin-6 (PS/2) connector

PS2Keyboard keyboard;

const int dpadup = 6;
const int dpaddown = 7;
const int dpadleft = 8;
const int dpadright = 9;

const int sel = 10;
const int star = 11;
const int psbutton = 12;

const int squar = 14;
const int triangle = 15;
const int r1 = 16;
const int l1 = 17;

const int cross = 18;
const int circle = 19;
const int r2 = 20;
const int l2 = 21;

void setup() {
  keyboard.begin(DataPin, IRQpin);
  //Serial.begin(9600);
  pinMode(dpadup, OUTPUT);
  pinMode(dpaddown, OUTPUT);
  pinMode(dpadleft, OUTPUT);
  pinMode(dpadright, OUTPUT);

  pinMode(sel, OUTPUT);
  pinMode(star, OUTPUT);
  pinMode(psbutton, OUTPUT);

  pinMode(squar, OUTPUT);
  pinMode(triangle, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(l1, OUTPUT);

  pinMode(cross, OUTPUT);
  pinMode(circle, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(l2, OUTPUT);
}

void loop() {
  int scn = getNextPS2Event();
  switch (scn) {  
  case 0xF0: //Regular Key release events
    scn = getNextPS2Event();
    switch (scn) {
    case 0x1C: //A
      digitalWriteFast(squar, LOW);
      break;
    case 0x1B: //S
      digitalWriteFast(triangle, LOW);
      break;
    case 0x23: //D
      digitalWriteFast(r1, LOW);
      break;
    case 0x2B: //F
      digitalWriteFast(l1, LOW);
      break;
    case 0x1A: //Z
      digitalWriteFast(cross, LOW);
      break;
    case 0x22: //X
      digitalWriteFast(circle, LOW);
      break;
    case 0x21: //C
      digitalWriteFast(r2, LOW);
      break;
    case 0x2A: //V
      digitalWriteFast(l2, LOW);
      break;
    case 0x16: //1
      digitalWriteFast(star, LOW);
      break;
    case 0x2E: //5
      digitalWriteFast(sel, LOW);
      break;
    case 0x46: //5
      digitalWriteFast(psbutton, LOW);
      break;
    default:
      break;
    }
    break;

    
  case 0xE0: //Arrow events
    scn = getNextPS2Event();
    switch (scn) { 
    case 0xF0: //Arrow key release events
      scn = getNextPS2Event();
      switch (scn) {
      case 0x75://Up
        digitalWriteFast(dpadup, LOW);
        break;
      case 0x72: //Down
        digitalWriteFast(dpaddown, LOW);
        break;
      case 0x6B: //Left
        digitalWriteFast(dpadleft, LOW);
        break;
      case 0x74: //Right
        digitalWriteFast(dpadright, LOW);
        break;
      default:
        break;
      }
      break;

      //Arrow Key press events
    case 0x75: //Up
      digitalWriteFast(dpadup, HIGH);
      break;
    case 0x72: //Down
      digitalWriteFast(dpaddown, HIGH);
      break;
    case 0x6B: //Left
      digitalWriteFast(dpadleft, HIGH);
      break;
    case 0x74: //Right
      digitalWriteFast(dpadright, HIGH);
      break;
    default:
      break;
    }
    break;

    // Regular key press events
  case 0x1C: //A
    digitalWriteFast(squar, HIGH);
    break;
  case 0x1B: //S
    digitalWriteFast(triangle, HIGH);
    break;
  case 0x23: //D
    digitalWriteFast(r1, HIGH);
    break;
  case 0x2B: //F
    digitalWriteFast(l1, HIGH);
    break;
  case 0x1A: //Z
    digitalWriteFast(cross, HIGH);
    break;
  case 0x22: //X
    digitalWriteFast(circle, HIGH);
    break;
  case 0x21: //C
    digitalWriteFast(r2, HIGH);
    break;
  case 0x2A: //V
    digitalWriteFast(l2, HIGH);
    break;
  case 0x16: //1
    digitalWriteFast(star, HIGH);
    break;
  case 0x2E: //5
    digitalWriteFast(sel, HIGH);
    break;
  case 0x46: //5
    digitalWriteFast(psbutton, HIGH);
    break;
  default:
    break;
  }
}

int getNextPS2Event() {
  int evn = 0;
  do {
    if (keyboard.available()) {
      evn = keyboard.readScanCode();
    }
  } while (evn == 0);
  return evn;
}
