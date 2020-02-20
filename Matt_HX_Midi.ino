#include <MIDI.h>
#include "Controller.h"

/*************************************************************
  Matt HX Midi

  help from Notes and Volts
  www.notesandvolts.com

  Version 1.0 **Arduino UNO ONLY!**
 *************************************************************/

MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 4;
//************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC  3=Preset up/down**

Button BU1(4, 3, 49, 1, 5 ); // Preset Down
Button BU2(2, 3, 50, 1, 5 ); // Preset Up
Button BU3(5, 2, 52, 1, 5 ); // FS4
Button BU4(3, 2, 53, 1, 5 ); // FS5
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4};
Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4};
//*******************************************************************


void setup() {
  // Turn off the led on the board
  pinMode(13, OUTPUT);
  // Start the Midi up
  MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop() {
  updateButtons();
}


//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
        case 3: // Preset up/down
          MIDI.sendControlChange(71, 1, BUTTONS[i]->Bchannel);
          delay(100);
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          delay(100);
          MIDI.sendControlChange(71, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
