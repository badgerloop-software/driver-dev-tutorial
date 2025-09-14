#include <Arduino.h>
#include "mcp23017.h"

// #define EXTERNAL_RESET_ENABLED

#ifdef EXTERNAL_RESET_ENABLED
#define RESET_PIN ______ //TODO: Add the pin thats doing the reset
#endif

// TODO: declare mcp23017 object

void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 

  #ifdef EXTERNAL_RESET_ENABLED
    //TODO: Configure the digital pin acting as a reset an output pin and reset the IOExpander registers to their default values.
    //Make sure to check if it is an Active-High or Active-Low reset
  #endif
  // TODO: initialize I2C and mcp23017 object
}

void loop() {
  // TODO: Write tests here
}