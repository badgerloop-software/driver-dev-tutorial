#include "mbed.h"
#include "mcp23017.h"
#include <cstdio>
#include "stdio.h"


// TODO: Write tests here
int main(int argc, char **argv)
{
    // construct necessary objects for testing
    I2C i2cBus(PF_0, PF_1);
    Mcp23017 mcp(0x20 << 1, &i2cBus);

    // test the begin method
    uint8_t directions[8];
    for (int i = 0; i < 8; i++) {
        *(directions + i) = 0;
    }
    *(directions + 7) = 1;
    mcp.begin(directions);
    mcp.set_state(0, 0);
    mcp.set_state(4, 0);

    while(1) {
        // test 1 (works)
        mcp.set_state(0, 1);
        mcp.set_state(4, 0);
        wait_us(1000000);
        mcp.set_state(0, 0);
        mcp.set_state(4, 1);
        wait_us(1000000);

        // test 2 with switch (possibly works, don't have switch to test)
        // if(mcp.get_state(7)) {
        //     mcp.set_state(0, 1);
        //     mcp.set_state(4, 1);
        // } else {
        //     mcp.set_state(0, 0);
        //     mcp.set_state(4, 0);
        // }
    }   
    
    return 0;
}
// wait_us