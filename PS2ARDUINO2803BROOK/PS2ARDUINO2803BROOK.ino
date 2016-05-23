/* 
PS/2 To Brook Fighting Board
For the Teensy, only tested on the Teensy-LC
Make sure you get the latest git version of PS2keyboard
*/


#include <PS2Keyboard.h>
#include <digitalWriteFast.h>

const int DataPin = 4; //The data pin is Pin 1 of the MiniDin-6 (PS/2) connector
const int IRQpin =  3; //The clock pin is Pin 5 of the MiniDin-6 (PS/2) connector

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
  Serial.begin(9600);
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
  //Main key release events
  if (scn == 0xF0){
    scn = getNextPS2Event();
    if (scn == 0x1C) {   //A
      digitalWriteFast(squar, LOW);
    } else if (scn == 0x1B) { //S
      digitalWriteFast(triangle, LOW);
    } else if (scn == 0x23) { //D
      digitalWriteFast(r1, LOW);
    } else if (scn == 0x2B) { //F
      digitalWriteFast(l1, LOW);
    } else if (scn == 0x1A) { //Z
      digitalWriteFast(cross, LOW);
    } else if (scn == 0x22) { //X
      digitalWriteFast(circle, LOW);
    } else if (scn == 0x21) { //C
      digitalWriteFast(r2, LOW);
    } else if (scn == 0x2A) { //V
      digitalWriteFast(l2, LOW);
    } else if (scn == 0x16) { //1
      digitalWriteFast(star, LOW);
    } else if (scn == 0x2E) { //5
      digitalWriteFast(sel, LOW);
    } else if (scn == 0x46) { //5
      digitalWriteFast(psbutton, LOW);
    }
  }
  //Arrow events
  else if (scn == 0xE0) {
    scn = getNextPS2Event();    
    //Arrow key release events
    if (scn == 0xF0) {
      scn = getNextPS2Event();
      if (scn == 0x75) {   //Up
        digitalWriteFast(dpadup, LOW);
      } else if (scn == 0x72) { //Down
        digitalWriteFast(dpaddown, LOW);
      } else if (scn == 0x6B) { //Left
        digitalWriteFast(dpadleft, LOW);
      } else if (scn == 0x74) { //Right
        digitalWriteFast(dpadright, LOW);
      }
    }
    //Arrow Key Events
    else if (scn == 0x75) {   //Up
      digitalWriteFast(dpadup, HIGH);
    } else if (scn == 0x72) { //Down
      digitalWriteFast(dpaddown, HIGH);
    } else if (scn == 0x6B) { //Left
      digitalWriteFast(dpadleft, HIGH);
    } else if (scn == 0x74) { //Right
      digitalWriteFast(dpadright, HIGH);
    }
  }
  //Regular key press events
  else if (scn == 0x1C) {   //A
    digitalWriteFast(squar, HIGH);
  } else if (scn == 0x1B) { //S
    digitalWriteFast(triangle, HIGH);
  } else if (scn == 0x23) { //D
    digitalWriteFast(r1, HIGH);
  } else if (scn == 0x2B) { //F
    digitalWriteFast(l1, HIGH);
  } else if (scn == 0x1A) { //Z
    digitalWriteFast(cross, HIGH);
  } else if (scn == 0x22) { //X
    digitalWriteFast(circle, HIGH);
  } else if (scn == 0x21) { //C
    digitalWriteFast(r2, HIGH);
  } else if (scn == 0x2A) { //V
    digitalWriteFast(l2, HIGH);
  } else if (scn == 0x16) { //1
    digitalWriteFast(star, HIGH);
  } else if (scn == 0x2E) { //5
    digitalWriteFast(sel, HIGH);
  } else if (scn == 0x46) { //5
    digitalWriteFast(psbutton, HIGH);
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
