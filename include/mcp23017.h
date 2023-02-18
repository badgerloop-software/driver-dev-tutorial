    #ifndef __mcp__h__
#define __mcp__h__

#include "mbed.h"
#include "stdint.h"
#include <I2C.h>


class Mcp23017 {
 private:
  int set_dir(int pin, uint8_t dir);
  uint8_t get_dir(int pin);
  int addr;
  I2C* i2cBus;

 public:
  Mcp23017(int addr, I2C* i2cBus);
  int begin(uint8_t directions[8]);
  uint8_t get_state(int pin);
  int set_state(int pin, uint8_t val);
};
#endif
