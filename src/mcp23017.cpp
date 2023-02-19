#include "mcp23017.h"
#include <errno.h>
#include <stdint.h>
#include <I2C.h>

// 0001000011111111
// 0000000011111111
void write_data(I2C *bus, int address, uint8_t reg, uint8_t data){
    static char buffer[2];
    buffer[0] = reg;
    buffer[1] = data;
    bus->write(address, buffer, 2);
}

uint8_t read_data(I2C *bus, int address, uint8_t reg){
    static char buffer[1] = {reg};
    bus->write(address, buffer, 1);
    bus->read(address, buffer, 1);
    return buffer[0];
}

// TODO (optional): Define macros for useful register below:


// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr, I2C* i2cBus) {
    this->addr = addr;
    this->i2cBus = i2cBus;
}

uint8_t Mcp23017::get_dir(int pin) {
    return (read_data(this->i2cBus, this->addr, IODIRA) & (1 << pin)) > 0;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    return (read_data(this->i2cBus, this->addr, GPIO_A) | (1 << pin)) > 0;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    
    uint8_t data = read_data(this->i2cBus, this->addr, IODIRA);
    
    if (dir){
        data = data | (1 << pin);
    } else {
        data = data & ~(1 << pin);
    }

    write_data(this->i2cBus, this->addr, IODIRA, data);
     return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {

    uint8_t data = read_data(this->i2cBus, this->addr, GPIO_A);

    if (val){
        data = data | (1 << pin);
    } else {
        data = data & ~(1 << pin);
    }

    write_data(this->i2cBus, this->addr, GPIO_A, data);
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;
    uint8_t data = read_data(this->i2cBus, this->addr, IODIRA);
    // TODO: Add device ID check
    if (data != 0xff){
        return 1;
    }

    for (int i = 0; i < 8; i++){
        set_dir(i, directions[i]);
    }

    return 0;
}
