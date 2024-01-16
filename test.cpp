#define DEBUG

#include "Events/ArrowInput.hpp"
#include "Events/KeyboardInput.hpp"
#include "Events/MouseInput.hpp"
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "def.hpp"
#include <algorithm>
#include <bitset>
#include <chrono>
#include <cstring>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <vector>


//int x = tui::init(0, 0);
static termios newt, oldt;
int main(int argc, char const *argv[])
{
    tui::KeyboardInputType k;
    //k = 'a';
    //std::cout << k << std::endl;
    auto e = "€";   //11305698
    auto hex = 0xAC82E2;
    k = hex;
    std::cout << k << " is eq: " << e << ": " << (k == e? "ture" : "false") << std::endl;

    {
        /*
        tui::InputManager man;
        bool run = true;

        tui::KeyboardInputLambda kl = [&](tui::KeyboardInputType k){
            std::clog << "GOT: " << k << std::endl;
            if(k == 1){
                run = false;
            }
        };
        while (run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
        */
    }
    
    //tui::deinit();
    return 0;
}
