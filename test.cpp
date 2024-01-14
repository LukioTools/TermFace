#include "def.hpp"
#include <bitset>
#include <chrono>
#include <ios>
#include <iostream>

#include <thread>
#include <unistd.h>
#include <termios.h>
static termios newt, oldt;
int main(int argc, char const *argv[])
{
        //termios
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    
        std::cout << enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;
    while (true) {
        auto n = std::cin.get();
        std::cout << std::dec <<  n << "  0x" << std::hex << n << "  0b" << std::bitset<8>(n) << "  char: " << (char) n << std::endl;
        if(n == 1)
            break;
    }
        std::cout << disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;


        //termios
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
