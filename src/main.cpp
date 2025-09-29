#include <Arduino.h>
#include "mcp23017.h"
#include <Wire.h>

//Ignore the compiler instruction related code (the ones that start with #) if you are not attempting the optional section


//Uncomment the statement below this line to work on the optional section
//#define EXTERNAL_RESET_ENABLED

#ifdef EXTERNAL_RESET_ENABLED
#define RESET_PIN ______ //TODO: Add the pin thats doing the reset
#endif

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20); // Example declaration, modify as needed

void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 


  #ifdef EXTERNAL_RESET_ENABLED
    //TODO: Configure the digital pin acting as a reset an output pin and reset the IOExpander registers to their default values.
    //Make sure to check if it is an Active-High or Active-Low reset
  #endif
  // TODO: initialize I2C and mcp23017 object
  Wire.begin(); // Initialize I2C
  // Initialize MCP23017
 uint8_t directions[8] = {
    1, // pin 0 = input
    1, // pin 1 = input (switch)
    1,
    1,
    1,
    1, // pin 5 = input
    1,
    0  // pin 7 = output (LED)
  };  
  mcp.begin(directions); // Set pin directions
}


void loop() {
  mcp.set_state(7, HIGH); 
  Serial.println("LED ON");
  delay(1000);

  mcp.set_state(7, LOW);  
  Serial.println("LED OFF");
  delay(1000);

  // Read switch on pin 1
  int switchState = mcp.get_state(5);
  Serial.print("Switch state: ");
  Serial.println(switchState);

  delay(500);
}

  

