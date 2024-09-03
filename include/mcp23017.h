#ifndef __mcp__h__
#define __mcp__h__

#include "stdint.h"
#include <Wire.h>


class Mcp23017 {
 private:
  int set_dir(int pin, uint8_t dir);
  uint8_t get_dir(int pin);
  int addr;

 public:
  Mcp23017(int addr);
  int begin(uint8_t directions[8]);
  uint8_t get_state(int pin);
  int set_state(int pin, uint8_t val);
};
#endif
