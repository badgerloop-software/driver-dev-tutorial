#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:

// from control register summary

// I/O direction register
// controls whether each pin in port A is an input / output
// 0 = output, 1 = input
#define IODIRA 0x00 

// general-purpose pull-up register 
// enables internal pull-up resistors for port A pins
// 1 = enable, 0 = disable
#define GPPUA 0x0C

// general-purpose I/O register
// stores current state of GPIO pins in port A
// when pin is configured as input, GPIO reads its state: 0 (LOW, 0V) or 1 (HIGH, VCC)
// when pin is configured as output, writing to GPIO controls its state
#define GPIOA_CLONE 0x12

// TODO: Initialize i2cBus member
// constructor
Mcp23017::Mcp23017(int addr) {
    // stores the i2c address in the current instance of the class
    this -> addr = addr; 
    // initializes the i2c communication bus
    // ensures the i2c hardware is ready to send and receive data
    Wire.begin();
}

// determines direction of a specified pin
uint8_t Mcp23017::get_dir(int pin) {
    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select IODRIA register 
    Wire.write(IODIRA);
    // end write operation to indicate we are done selecting the register
    Wire.endTransmission();
    // requst 1 byte of data from IODRIA register to determine port A pins I/O direction
    Wire.requestFrom(addr, 1); 
    // received byte, I/O direction
    uint8_t iodir;
    // check if MCP23017 has sent data back over i2c
    if (Wire.available()) 
    {
        // read received byte
        iodir = Wire.read();
    }
    // MCP23017 did not respond
    else
    {
        return 0xFF; // error (from stack overflow)
    }
    // extract bit corresponding to the pin by shifting right
    // apply bitmask to isolate bit
    return (iodir >> pin) & 0x01;
}

// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select GPIOA_CLONE register
    Wire.write(GPIOA_CLONE);
    // end write operation to indicate we are done selecting the register
    Wire.endTransmission();
    // request 1 byte of data from GPIOA_CLONE register to determine current state of port A pins
    Wire.requestFrom(addr, 1);
    // received byte, state of port A
    uint8_t gpio;
    // check if MCP23017 has sent data back over i2C
    if (Wire.available()) 
    {
        // read received byte
        gpio = Wire.read();
    }
    // MCP23017 did not respond
    else
    {
        return 0xFF; // error (from stack overflow)
    }
    // extract bit corresponding to the pin by shifting right
    // apply bitmask to isolate bit
    return (gpio >> pin) & 0x01;
}

// TODO: Write to directions register
// writes dir direction to specified pin on port A
int Mcp23017::set_dir(int pin, uint8_t dir) 
{
    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select IODIRA register
    Wire.write(IODIRA);
    // end write operation to indicate we are done selecting the register
    Wire.endTransmission();
    // request 1 byte of data from IODIRA register to determine current state of port A pins
    Wire.requestFrom(addr, 1);
    // received byte, state of port A
    uint8_t iodir;
    // check if MCP23017 has sent data back over i2c
    if (Wire.available()) 
    {
        // read received byte
        iodir = Wire.read();
    }
    // MCP23017 did not respond
    else
    {
        return -1;
    }
    // val == 1
    if (dir)
    {
        // sets bit to 1 
        iodir |= (1 << pin);
    }
    // val == 0
    else
    {
        // sets bit to 0
        iodir &= ~(1 << pin);
    }
    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select IODIRA register
    Wire.write(IODIRA);
    // select modified GPIOA_CLONE, new pin state
    Wire.write(iodir);
    // end the i2c transmission and sends data to MCP23017
    return Wire.endTransmission();
}

// TODO: Write to state register
// writes val state to specified pin on port A
int Mcp23017::set_state(int pin, uint8_t val) 
{
    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select GPIOA_CLONE register
    Wire.write(GPIOA_CLONE);
    // end write operation to indicate we are done selecting the register
    Wire.endTransmission();
    // request 1 byte of data from GPIOA_CLONE register to determine current state of port A pins
    Wire.requestFrom(addr, 1);
    // received byte, state of port A
    uint8_t gpio;
    // check if MCP23017 has sent data back over i2c
    if (Wire.available()) 
    {
        // read received byte
        gpio = Wire.read();
    }
    // MCP23017 did not respond
    else
    {
        return -1; // error
    }
    // val == 1
    if (val)
    {
        // sets bit to 1 
        gpio |= (1 << pin);
    }
    // val == 0
    else
    {
        // sets bit to 0
        gpio &= ~(1 << pin);
    }

    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select GPIOA_CLONE register
    Wire.write(GPIOA_CLONE);
    // select modified GPIOA_CLONE, new pin state
    Wire.write(gpio);
    // end the i2c transmission and sends data to MCP23017
    return Wire.endTransmission();
}
    
// Verifies that the device is accessible over i2c and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) 
{
    // TODO: Add device ID check

    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select IODIRA register
    Wire.write(IODIRA);
    // end write operation to indicate we are done selecting the register
    Wire.endTransmission();
    // request 1 byte of data from IODIRA register to determine current state of port A pins
    Wire.requestFrom(addr, 1);
    // received byte, state of port A
    uint8_t iodir_value;
    // check if MCP23017 has sent data back over i2c
    if (Wire.available()) 
    {
        // read received byte
        iodir_value = Wire.read();
    }
    // MCP23017 did not respond
    else
    {
        return -1; // error
    }

    uint8_t iodir = 0x00;
    for (int i = 0; i < 8; i++)
    {
        // check what direction pins should be 1
        if (directions[i])
        {
            // set direction pins to 1
            iodir |= (1 << i); 
        }
    }

    if (iodir != iodir_value) 
    {
        return -1;
    }

    // start i2c communication with MCP23017 at stored address
    Wire.beginTransmission(addr);
    // select IODIRA register
    Wire.write(IODIRA);
    // select modified GPIOA_CLONE, new pin state
    Wire.write(iodir);
    // end the i2c transmission and sends data to MCP23017
    return Wire.endTransmission();
}
