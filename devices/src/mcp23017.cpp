#include "mcp23017.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include <iostream>


// TODO (optional): Define macros for useful register below:

#define	REGISTER_IODIR	0x0
#define	REGISTER_GPIOA	0x12

#define get_pin(reg,pin) ((read_from_reg(reg)&(1<<pin))>0)
#define set_pin(reg,pin,val) (val?(write_data<uint8_t>(reg,read_from_reg(reg)|(1<<pin))):(write_data<uint8_t>(reg,read_from_reg(reg)&(~(1<<pin)))))
			

// Calls parent constructor
Mcp23017::Mcp23017(int bus, int addr) : I2c(bus, addr) {}


// TODO: Read from direction register
uint8_t Mcp23017::get_dir(int pin) {
    return get_pin(REGISTER_IODIR,pin);
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    return get_pin(REGISTER_GPIOA,pin);
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    set_pin(REGISTER_IODIR,pin,dir);
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    set_pin(REGISTER_GPIOA,pin,val);
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // Make sure we can access the i2c bus
    if (!this->is_open()) {
        rc = this->open_i2c();
        if (rc) return rc;
    }

    // TODO: Add device ID check
    // TODO: Wontfix
    for(uint8_t i = 0; i < 8; ++i)
	    set_dir(i,directions[i]);

    return 0;
}
