#include <iostream>
#include "mcp23017.h"


// TODO: Write tests here
int main(int argc, char **argv)
{
    static uint8_t arr[]={0,1,1,1,0,1,1,1,};
    std::cout << "Hello world!" << std::endl;
    Mcp23017 m(2,0x20);
    m.begin(arr);
    bool state = 0;
    m.set_state(4,0);
    while(1){
	    usleep(1000);
	    m.set_state(0,m.get_state(7));
    }
    return 0;
}
