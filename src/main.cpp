al#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp23017(0x20);


void setup() {
  // TODO: initialize i2c and mcp23017 object
  Wire.begin();
  uint8_t directions[8] = {1, 1, 1, 1, 1, 1, 1, 0};
  mcp23017.begin(directions);
  //Start serial
  Serial.begin(9600);
  Serial.println("Starting process...");
}

void loop() {
  // TODO: Write tests here
  
  //Toggles the state of the first pin and prints it
  Serial.println(mcp23017.get_state(0));
  mcp23017.set_state(0, 1);
  delay(1000); //delay so we can see the pin state change
  Serial.println(mcp23017.get_state(0));
  mcp23017.set_state(0, 0);
  delay(1000); //delay so it doesn't loop so quickly
}
