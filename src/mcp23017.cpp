#include "mcp23017.h"

// Define macros for useful register below:
#define IODIRA 0x00
#define GPIOA  0x12

// Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
    // Record the device address. This will be used in the I2C reads and writes of other functions.
    addr = addr;
}

uint8_t Mcp23017::get_dir(int pin) {
    // Specify to the MCP that we want to read from the IODIRA register from by 
    // writing the correct register offset.
    Wire.beginTransmission(addr);
    Wire.write(IODIRA); 
    Wire.endTransmission();
    
    // Read ONE byte from the IODIRA register we just specified.
    Wire.requestFrom(addr, (uint8_t)1);
    uint8_t iodir_val = Wire.read();

    // Do bitwise arithmetic to figure out what part of the byte corresponds 
    // to the pin we are looking for.
    uint8_t pin_value = (iodir_val >> pin) & 0x01;

    // Return the value of the pin.
    return pin_value;
}

// Read from state register
uint8_t Mcp23017::get_state(int pin) {
    // This function should do the same thing as get_dir(), except it reads from the 
    // GPIO register instead of the direction register.

    // Specify to the MCP that we want to read from the GPIOA register by 
    // writing the correct register offset.
    Wire.beginTransmission(addr);
    Wire.write(GPIOA); 
    Wire.endTransmission();
    
    // Read ONE byte from the GPIOA register we just specified.
    Wire.requestFrom(addr, (uint8_t)1);
    uint8_t gpio_val = Wire.read();

    // Do bitwise arithmetic to figure out what part of the byte corresponds 
    // to the pin we are looking for.
    uint8_t pin_value = (gpio_val >> pin) & 0x01;

    // Return the value of the pin.
    return pin_value;
}

// Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.endTransmission();

    Wire.requestFrom(addr, (uint8_t)1);
    uint8_t iodir_val = Wire.read();

// Read get all 8 bits, then bit mask

    // Find out which value (0 or 1) means "input" and which value means "output".  
    // --> 0 represents output, 1 represents input.
    
    // Remember that all I2C communication is done with bytes, so we can't write to specific bit 
    // in the register to change its value. Think about what we need to do to preserve the values 
    // of the other bits of the register.
   
    // We will need to use bitwise operations to set a certain bit position to a 0 or a 1.
    if (dir == 1) {
        // Set the pin to be an input (1)
        iodir_val |= (1 << pin);
    } else {
        // Set the pin to be an output (0)
        iodir_val &= ~(1 << pin);
    }
    
    // Write updated value back to IODIRA
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.write(iodir_val);
    return Wire.endTransmission();
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.beginTransmission(addr);
    Wire.write(GPIOA);
    Wire.endTransmission();

    Wire.requestFrom(addr, (uint8_t)1);
    uint8_t gpio_val = Wire.read();

    if (val == 1) {
        // Set the pin to be HIGH (1)
        gpio_val |= (1 << pin); 
    } else {
        // Set the pin to be LOW (0)
        gpio_val &= ~(1 << pin);
    }
    
    // Write updated value back to GPIOA
    Wire.beginTransmission(addr);
    Wire.write(GPIOA);
    Wire.write(gpio_val);
    return Wire.endTransmission();
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    // read and verify the default value of the IODIRA register to confirm 
    // I2C communication between the microcontroller and the MCP23017
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(addr, (uint8_t)1);
    
    // return a 0 if the initialization is a success 
    // (default value of IODIRA is read correctly), 1 otherwise.
    uint8_t iodira_confirm = Wire.read();
    if (iodira_confirm != 0xFF) {
        // If the value read from IODIRA is not 0xFF, something went wrong.
        return 1;
    }

    // set the direction of each pin on the MCP23017
    for (int i = 0; i < 8; i++) {
        set_dir(i, directions[i]);
    }
    
    return 0;
}
