#ifndef __mcp__h__
#define __mcp__h__
#include "i2c.h"
#include "stdint.h"


class Mcp23017 : private I2c {
 private:
  int set_dir(int pin, uint8_t dir);
  uint8_t get_dir(int pin);

 public:
  Mcp23017(int bus, int addr);
  int begin(uint8_t directions[8]);
  uint8_t get_state(int pin);
  int set_state(int pin, uint8_t val);
};
#endif
