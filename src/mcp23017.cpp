#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
const int IODIRA_ADDR = 0x00;
const int GPIOA_ADDR = 0x12;

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
    this->addr = addr;
}

uint8_t Mcp23017::get_dir(int pin) {
    // Specify to the MCP that we want to read from the IODIRA register from by writing the correct register offset.
    Wire.beginTransmission(addr);
    Wire.write(IODIRA_ADDR);
    Wire.endTransmission();

    // Read ONE byte from the IODIRA register we just specified.
    Wire.requestFrom(addr, 1);
    uint8_t read_iodira;
    read_iodira = Wire.read();

    // Do bitwise arithmetic to figure out what part of the byte corresponds to the pin we are looking for.
    // Shift bit by pin bits
    uint8_t pinVal = read_iodira >> pin;

    //return value of pin
    return pinVal & 1;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    Wire.beginTransmission(addr);
    Wire.write(GPIOA_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);
    uint8_t read_gpioa;
    read_gpioa = Wire.read();

    uint8_t pinVal = read_gpioa >> pin;
    return pinVal & 1;
}

// TODO: Write to directions register
// 0 - pin is input, 1 - pin is output
int Mcp23017::set_dir(int pin, uint8_t dir) {
    //read iodira value
    Wire.beginTransmission(addr);
    Wire.write(IODIRA_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);
    uint8_t iodira_val;
    iodira_val = Wire.read();

    //set dir based on inputs
    if(dir == 0){
        // create mask (L shift 1 by pin # of bits, then negate all), then and with byte value
        uint8_t mask = ~(1 << pin);
        iodira_val = iodira_val & mask;
    }
    else if(dir == 1){
        //Lshift 1, then or with byte value
        uint8_t mask = 1 << pin;
        iodira_val = iodira_val | mask;
    }

    //write to IODIRA
    Wire.beginTransmission(addr);
    Wire.write(IODIRA_ADDR);
    Wire.write(iodira_val);
    Wire.endTransmission();

    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    // read gpioa value
    Wire.beginTransmission(addr);
    Wire.write(GPIOA_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);
    uint8_t gpioa_val;
    gpioa_val = Wire.read();

    // set dir based on inputs
    if (val == 0)
    {
        // create mask (L shift 1 by pin # of bits, then negate all), then and with byte value
        uint8_t mask = ~(1 << pin);
        gpioa_val = gpioa_val & mask;
    }
    else if (val == 1)
    {
        // Lshift 1, then or with byte value
        uint8_t mask = 1 << pin;
        gpioa_val = gpioa_val | mask;
    }

    // write to IODIRA
    Wire.beginTransmission(addr);
    Wire.write(GPIOA_ADDR);
    Wire.write(gpioa_val);
    Wire.endTransmission();

    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // default value of iodira register is 1111 1111
    Wire.beginTransmission(addr);
    Wire.write(IODIRA_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);
    uint8_t read_iodira;
    read_iodira = Wire.read();
    if(read_iodira != 0xFF){
        // IODIRA is not default value (error)
        return 1;
    }
    
    for(int i = 0; i < 8; i++){
        this->set_dir(i, directions[i]);
    }

    return 0;
}
