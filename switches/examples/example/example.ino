/*
 * Example
 * 
 * This example shows how to read a switch connected 
 * between pin 8 and ground.
 * 
 * This example code is in the public domain.
 */
 
#include "switches.h"

#define NumSwitches 1
uint8_t  switchPins[] = { 8 };

Switches switches(NumSwitches, switchPins);

void setup()
{
  switches.setDelegate(switchDidChangeDelegate);
}

void loop()
{
  if(switches.pollSwitches()) {
    // You can choose to do something if any switch has changed.
    // It is easier though to use instead the delegate method.
    // if (switches.isSwitchOn(0)) {
    // }
    // Note: call switches.pollSwitches() in loop(), even if you
    //       are using the delegate and ignoring the return value.
  }
  
  /* Do whatever else you want in the loop
   *  but do not stop, wait, or delay.
   *  If you need to wait for something,
   *  then use millis() as shown
   */
}

void switchDidChangeDelegate(uint8_t switchIndex, bool switchIsOn) {
  // Since this example has only 1 switch, we can ignore switchIndex.
  // Otherwise, it would tell us which switch has changed.
  // switchIsOn tells us whether the switch has been turned on or off
  // This method will only be called once per switch change.
}

