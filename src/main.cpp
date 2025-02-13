#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20); // i2c address, 0x01000000 (A2-A0)
void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 
  // TODO: initialize I2C and mcp23017 object

  Wire.begin();

  uint8_t directions[8] = {0, 0, 0, 0, 0, 1, 0, 0};

  if (mcp.begin(directions) != 0) 
  {
    Serial.println("initialization failed");
  }
  else 
  {
    Serial.println("initialization success");
  }
}

void loop() {
  // TODO: Write tests here

  // 1) set pin 7 HIGH
  mcp.set_state(7, 1);
  delay(500);
  uint8_t state = mcp.get_state(0);
  if (state == 1)
  {
    Serial.println("test 1 passed");
  }
  else
  {
    Serial.println("test 1 failed");
  }
// set pin 7 low
  mcp.set_state(7, 0);
  delay(500);
  state = mcp.get_state(0);
  if (state == 1)
  {
    Serial.println("test 1 passed");
  }
  else
  {
    Serial.println("test 1 failed");
  }

  // 2) set pin 1 LOW

  state = mcp.get_state(5);

  Serial.println(state);
 

}

