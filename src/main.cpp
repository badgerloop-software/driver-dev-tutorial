#include <Arduino.h>
#include "mcp23017.h"

//Ignore the compiler instruction related code (the ones that start with #) if you are not attempting the optional section


//Uncomment the statement below this line to work on the optional section
// #define EXTERNAL_RESET_ENABLED

#ifdef EXTERNAL_RESET_ENABLED
#define RESET_PIN ______ //TODO: Add the pin thats doing the reset
#endif

// TODO: declare mcp23017 object
Mcp23017 obj1(0x20);
void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 

  #ifdef EXTERNAL_RESET_ENABLED
    //TODO: Configure the digital pin acting as a reset an output pin and reset the IOExpander registers to their default values.
    //Make sure to check if it is an Active-High or Active-Low reset
  #endif
  // TODO: initialize I2C and mcp23017 object
  Wire.begin();
  uint8_t numbers[8] = {0, 0, 0, 0, 0, 1, 0, 0};
  obj1.begin(numbers);
}

void loop() {
  // TODO: Write tests here
  obj1.set_state(7, 1);
  Serial.println(obj1.get_state(5));
  delay(1000);
  obj1.set_state(7, 0);
  delay(1000);
  Serial.println(obj1.get_state(5));
}