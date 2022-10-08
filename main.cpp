#include <iostream>
#include "mcp23017.h"
#include "i2c.h"


// TODO: Write tests here
int main(int argc, char **argv)
{
    std::cout << "Hello world!" << std::endl;
    Mcp23017 mcp23017 = Mcp23017(1,0x20);
    uint8_t directions [8] = {1,0,0,0,0,0,0,0};
    mcp23017.begin(directions);

    if (mcp23017.get_state(7)){
        mcp23017.set_state(0, 1);
        mcp23017.set_state(4, 0);
    } else {
        mcp23017.set_state(0, 0);
        mcp23017.set_state(4, 1);
    }

    return 0;
}