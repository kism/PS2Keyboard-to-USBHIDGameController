/* 
PS/2 To HID Gamepad
http://github.com/kism

Requirements: 
  My slightly modified Arduino PS2Keyboard library, avalible at https://github.com/kism/PS2Keyboard

Todo: HID Descriptions or whatever they are

*/

#include <PS2Keyboard.h>

const int DataPin = 4; //The data pin is Pin 1 of the MiniDin-6 (PS/2) connector
const int IRQpin =  3; //The clock pin is Pin 5 of the MiniDin-6 (PS/2) connector

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Debug serial output, will print out the scancodes for keys that are pressed but not mapped to a Joystick function");
  Joystick.hat(-1); //Ech
}

void loop() {
  int scn = getNextPS2Event();
  //Main key release events
  if (scn == 0xF0){
    scn = getNextPS2Event();
    if (scn == 0x1C) {        //A
      Joystick.button(1, 0);
    } else if (scn == 0x1B) { //S
      Joystick.button(2, 0);
    } else if (scn == 0x23) { //D
      Joystick.button(3, 0);
    } else if (scn == 0x2B) { //F
      Joystick.button(4, 0);
    } else if (scn == 0x1A) { //Z
      Joystick.button(5, 0);
    } else if (scn == 0x22) { //X
      Joystick.button(6, 0);
    } else if (scn == 0x21) { //C
      Joystick.button(7, 0);
    } else if (scn == 0x2A) { //V
      Joystick.button(8, 0);
    } else if (scn == 0x16) { //1
      Joystick.button(9, 0);
    } else if (scn == 0x2E) { //5
      Joystick.button(10, 0);
    } else {
      Serial.print("\nMisc button release: ");
      Serial.print(scn, HEX);
    }
  }
  //Arrow events
  else if (scn == 0xE0) {
    scn = getNextPS2Event();    
    //Arrow key release events
    if (scn == 0xF0) {
      scn = getNextPS2Event();
      if (scn == 0x75) {        //Up
        Joystick.button(11, 0);
      } else if (scn == 0x72) { //Down
  		  Joystick.button(12, 0);
      } else if (scn == 0x6B) { //Left
        Joystick.button(13, 0);
      } else if (scn == 0x74) { //Right
        Joystick.button(14, 0);
      } else {
        Serial.print("\nMisc 0xE0 button release: ");
        Serial.print(scn, HEX);
      }
    }
    //Arrow Key Events
    else if (scn == 0x75) {   //Up
      Joystick.button(11, 1);
    } else if (scn == 0x72) { //Down
      Joystick.button(12, 1);
    } else if (scn == 0x6B) { //Left
      Joystick.button(13, 1);
    } else if (scn == 0x74) { //Right
      Joystick.button(14, 1);
    } else {
      Serial.print("\nMisc 0xE0 button release: ");
      Serial.print(scn, HEX);
    }
  }
  //Regular key press events
  else if (scn == 0x1C) {   //A
    Joystick.button(1, 1);
  } else if (scn == 0x1B) { //S
    Joystick.button(2, 1);
  } else if (scn == 0x23) { //D
    Joystick.button(3, 1);
  } else if (scn == 0x2B) { //F
    Joystick.button(4, 1);
  } else if (scn == 0x1A) { //Z
    Joystick.button(5, 1);
  } else if (scn == 0x22) { //X
    Joystick.button(6, 1);
  } else if (scn == 0x21) { //C
    Joystick.button(7, 1);
  } else if (scn == 0x2A) { //V
    Joystick.button(8, 1);
  } else if (scn == 0x16) { //1
    Joystick.button(9, 1);
  } else if (scn == 0x2E) { //5
    Joystick.button(10, 1);
  } else {
  Serial.print("\nMisc button press: ");
  Serial.print(scn, HEX);
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