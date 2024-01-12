#include <bitset>
#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#include <iostream>
#include "Init.hpp"
//#include "Input/InputManager.hpp"

int main(int argc, char const *argv[])
{
    //tui::InputManager man;
    tui::init(argc, argv);


    while (true) {
        auto c = std::cin.get();
        std::cout << "0b" <<std::bitset<8>(c) << " : "  << std::dec <<   c << " : 0x" << std::hex << c  << " : " << (char) c << '\n';
        if(c == 1 || c == 4)
            break;
    }


    tui::deinit();
    return 0;
}
