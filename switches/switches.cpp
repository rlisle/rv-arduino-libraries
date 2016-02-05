/******************************************************************
 Switches control

 Features:
 - Read and debounce switch inputs
 - Very small code

 http://www.github.com/rlisle/rv-arduino-libraries

 Written by Ron Lisle, ron@lisles.net

 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.

 Datasheets:

 Changelog:
 2016-02-3: Initial version
 ******************************************************************/

#include "switches.h"

#define DebounceDelay  50    // 50 msec delay for switch to settle down

Switches::Switches(uint8_t numSwitches, uint8_t *pins)
{
    numPins      = numSwitches;
    switchPins   = pins;
    delegate     = NULL;
    lastLoopTime = 0;

    switchIsOn      = (bool *)malloc(numPins * sizeof(bool));
    switchChanged   = (bool *)malloc(numPins * sizeof(bool));
    lastSwitchTime  = (long *)malloc(numPins * sizeof(long));

    for( int i=0; i<numPins; i++) {
      switchIsOn[i]     = false;
      switchChanged[i]  = false;
      lastSwitchTime[i] = 0;
      pinMode(switchPins[i], INPUT_PULLUP);
    }
}

bool Switches::isSwitchOn(uint8_t switchNum) {
  if(switchNum >= numPins) {
    return false;                 //Guard against invalid switchNum
  }
  return switchIsOn[switchNum];
}

void Switches::setDelegate( void (*callersDelegate)(uint8_t,bool) ) {
    delegate = callersDelegate;
}

bool Switches::pollSwitches() {
  bool switchDidChange = false;
  long loopTime = millis();

  if(loopTime > lastLoopTime + DebounceDelay) {
    lastLoopTime = loopTime;
    for (uint8_t i=0; i<numPins; i++) {
      switchDidChange |= Switches::processSwitchState(i);
    }
  }
  return switchDidChange;
}

// Private Helper Methods

bool Switches::processSwitchState(uint8_t index) {
  bool switchDidChange = false;
  bool newState = (digitalRead(switchPins[index]) == 0);
  if (newState != switchIsOn[index]) {
      switchIsOn[index] = newState;
      switchDidChange = true;
      callDelegateIfSet(index,newState);
  }
  return switchDidChange;
}

void Switches::callDelegateIfSet(uint8_t index, bool newState) {
  if(delegate != NULL) {
    delegate(index,newState);
  }
}
