#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp23017(0x20);


void setup() {
  // TODO: initialize i2c and mcp23017 object
  Wire.begin();
  //Start serial
  Serial.begin(9600);
  Serial.println("Starting process...");
}

void loop() {
  // TODO: Write tests here
  uint8_t directions[8] = {1, 1, 1, 1, 1, 1, 0};
  mcp23017.begin(directions);
  mcp23017.get_state(0);
  mcp23017.set_state(0, 1);
}