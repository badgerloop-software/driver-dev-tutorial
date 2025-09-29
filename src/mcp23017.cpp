#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:


// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
    this->addr = addr;
}

uint8_t Mcp23017::get_dir(int pin) {
    
    //gets information from Mcp23017 register 0x00
    Wire.beginTransmission(addr);
    Wire.write(0x00);
    Wire.endTransmission();

    //requests 1 byte from register 0x00 in Mcp23017
    Wire.requestFrom(addr, 1);

    //reads from the register and shifts the bit position to the LSB, then ands with 1 to get a 1 or 0
    return (Wire.read() >> pin) & 1; 

}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {

    Wire.beginTransmission(addr);
    Wire.write(0x12);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);

    //reads from the register and shifts the bit position to the LSB, then ands with 1 to get a 1 or 0
    return (Wire.read() >> pin) & 1; 

    

}

// TODO: Write to directions register
// 1: input  0: output
int Mcp23017::set_dir(int pin, uint8_t dir) {
    // calls IODIRA for the read
    Wire.beginTransmission(addr); //addr << 1 makes addr  bit with LSB = 0
    Wire.write(0x00); // writes the register offset
    Wire.endTransmission();
    
    //reads the byte value from the register
    uint8_t number;
    Wire.requestFrom(addr, 1);
    number = Wire.read();

    // changes the byte from the register that will convert the correct pin to a 1 or 0
    if (dir == 1) {
        number = number | (1 << pin); // number is all 0s except a 1 in the input pin position
    } else {
        number = number & ~(1 << pin); // number is all 1s except a 0 in the input pin position
    }
    
    //writes the new register data including the changed pin back to the register
    Wire.beginTransmission(addr); //addr << 1 makes addr  bit with LSB = 0
    Wire.write(0x00); // writes the register offset
    Wire.write(number); // writes the new data
    Wire.endTransmission();

    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    // calls GPIO for the read
    Wire.beginTransmission(addr); //addr << 1 makes addr  bit with LSB = 0
    Wire.write(0x12); // writes the register offset
    Wire.endTransmission();
    
    //reads the byte value from the register
    uint8_t number;
    Wire.requestFrom(addr, 1);
    number = Wire.read();

    // changes the byte from the register that will convert the correct pin to a 1 or 0
    if (val == 1) {
        number = number | (1 << pin); // number is all 0s except a 1 in the input pin position
    } else {
        number = number & ~(1 << pin); // number is all 1s except a 0 in the input pin position
    }
    
    //writes the new register data including the changed pin back to the register
    Wire.beginTransmission(addr); //addr << 1 makes addr  bit with LSB = 0
    Wire.write(0x12); // writes the register offset
    Wire.write(number); // writes the new data
    Wire.endTransmission();

    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check
    Wire.beginTransmission(addr); //addr << 1 makes addr  bit with LSB = 0
    Wire.write(0x00); // writes the register offset
    Wire.endTransmission();
    
    // sets each bit in IODIRA according to the bits in directions
    Wire.requestFrom(addr, 1);
    uint8_t s = Wire.read();
    Serial.printf("%d, %d\n",s, addr);
    if (s == 0xFF) {          // if the read is all 1s then the default value is correct
        for (int i = 0; i < 8; i++) {
            this->set_dir(i, directions[i]);
        }
        return 0;
    } else {
        return 1;   // returns 1 if the default value is wrong
    }
    

    
}
