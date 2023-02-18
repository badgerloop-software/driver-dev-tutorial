#include "mcp23017.h"
#include <cstdint>
#include <errno.h>
#include <I2C.h>


// TODO (optional): Define macros for useful register below:
#define REGISTER_IODIRA 0x00
#define REGISTER_GPIOA 0x12

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr, I2C* i2cBus) {
    this->addr = addr;
    this->i2cBus = i2cBus;
}

uint8_t Mcp23017::get_dir(int pin) {
    char buf[256] = {REGISTER_IODIRA};
    
    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 2, false);

    uint16_t reg = 0;
    reg |= buf[0];
    reg <<= 8;
    reg |= buf[1];

    if ((reg && (1 >> pin)) > 0) {
        return 1;
    } else {
        return 0;
    }
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    char buf[256] = {REGISTER_GPIOA};
    
    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 2, false);

    uint16_t reg = 0;
    reg |= buf[0];
    reg <<= 8;
    reg |= buf[1];

    if ((reg && (1 >> pin)) > 0) {
        return 1;
    } else {
        return 0;
    }
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    char buf[256] = {REGISTER_IODIRA, dir};

    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 2, false);

    uint16_t reg = 0;
    reg |= buf[0];
    reg <<= 8;
    reg |= buf[1];

    char *data = 0;
    if ((reg && (1 >> pin)) > 0) {
        *data = 1;
    } else {
        *data = 0;
    }

    this->i2cBus->write(this->addr, data, 3, false);
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    char buf[256] = {REGISTER_GPIOA, val};

    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 2, false);

    uint16_t reg = 0;
    reg |= buf[0];
    reg <<= 8;
    reg |= buf[1];

    char *data = 0;
    if ((reg && (1 >> pin)) > 0) {
        *data = 1;
    } else {
        *data = 0;
    }

    this->i2cBus->write(this->addr, data, 3, false);
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check

    return 0;
}
