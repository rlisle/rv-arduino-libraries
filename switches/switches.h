/******************************************************************
 switches control

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

#ifndef switches_h
#define switches_h

#include <stdio.h>

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

class Switches
{
public:
    Switches(uint8_t numSwitches, uint8_t *pins);

    bool isSwitchOn(uint8_t switchNum);
    void setDelegate( void (*delegate)(uint8_t switchIndex,bool isOn) );
    bool pollSwitches();

private:
    void       (*delegate)(uint8_t,bool);
    long       lastLoopTime;
    uint8_t    numPins;
    uint8_t    *switchPins;
    bool       *switchIsOn;
    bool       *switchChanged;
    long       *lastSwitchTime;

    bool processSwitchState(uint8_t index);
    void callDelegateIfSet(uint8_t index, bool newState);

};

#endif /* switches_h */
