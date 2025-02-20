#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp23017_obj(0x20);

// turn on an LED attached to pin 7 and read in the value from a switch from pin 5
void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 
  // TODO: initialize I2C and mcp23017 object
  //mcp23017_obj = Mcp23017(0x40);
  uint8_t directions[8] = {0, 0, 0, 0, 0, 1, 0, 0};
  mcp23017_obj.begin(directions);


}

void loop() {
  // TODO: Write tests here
  //turn on/off LED
  mcp23017_obj.set_state(7, 1); 
  delay(1000);
  mcp23017_obj.set_state(7, 0);
  //get switch state
  Serial.print("Switch State: ");
  Serial.println(mcp23017_obj.get_state(5));
  delay(1000);
}