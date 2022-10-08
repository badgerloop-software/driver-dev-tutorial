#include "mcp23017.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include <iostream>

#define DIR_REG 0x00
#define GPIO_REG 0x12

// TODO (optional): Define macros for useful register below:

// Calls parent constructor
Mcp23017::Mcp23017(int bus, int addr) : I2c(bus, addr) {}


// TODO: Read from direction register
uint8_t Mcp23017::get_dir(int pin) {

    uint8_t reg_val = read_from_reg(DIR_REG);
    // mask off non necessary pins
    return (reg_val >> pin) & 0x01;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    uint8_t reg_val = read_from_reg(GPIO_REG);
    // mask off non necessary pins
    return (reg_val >> pin) & 0x01;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {

    uint8_t reg_val = read_from_reg(DIR_REG);
    uint8_t pin_val = (reg_val >> pin) & 0x01;

    // on to off
    if (pin_val && !dir){
         return write_data(DIR_REG,(reg_val & ~(0x01 << pin)));
    }
    // off to on
    else if (!pin_val && dir){
        return write_data(DIR_REG, (reg_val | (0x01 << pin)));
    }
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {

    uint8_t reg_val = read_from_reg(GPIO_REG);
    uint8_t pin_val = (reg_val >> pin) & 0x01;

    // on to off
    if (pin_val && !val){
         return write_data(GPIO_REG,(reg_val & ~(0x01 << pin)));
    }
    // off to on
    else if (!pin_val && val){
        return write_data(GPIO_REG, (reg_val | (0x01 << pin)));
    }
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

    // TODO: Set pin directions

    return 0;
}
