#include <Arduino.h>
#include "mcp23017.h"

//Ignore the compiler instruction related code (the ones that start with #) if you are not attempting the optional section


//Uncomment the statement below this line to work on the optional section
// #define EXTERNAL_RESET_ENABLED

#ifdef EXTERNAL_RESET_ENABLED
#define RESET_PIN ______ //TODO: Add the pin thats doing the reset
#endif

// TODO: declare mcp23017 object
Mcp23017 controller(0x20);

void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 
  Wire.begin();

 


  #ifdef EXTERNAL_RESET_ENABLED
    //TODO: Configure the digital pin acting as a reset an output pin and reset the IOExpander registers to their default values.
    //Make sure to check if it is an Active-High or Active-Low reset
  #endif
  // TODO: initialize I2C and mcp23017 object
  uint8_t setup[8] = {1, 1, 1, 1, 1, 1, 1, 0};
  int status = controller.begin(setup);
  if (status) {
    Serial.println("kys");
  }
  else
    Serial.println("chat we cookin?");
}

void loop() {
  // TODO: Write tests here
  int switchVal = controller.get_state(5);
  controller.set_state(7, 1);
  delay(500);
  controller.set_state(7, 0);
  Serial.printf("Switch value : %d \n", switchVal);
  delay(500);
}