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

int x = tui::init(0, 0);
tui::InputManager man;
static termios newt, oldt;
int main(int argc, char const *argv[])
{
    {
        bool run = true;

        tui::KeyboardInputLambda kl = [&](tui::KeyboardInputType k){
            std::clog << "GOT: " << k << std::endl;
            if(k[0] == 1 && k[2] == 0){
                run = false;
            }
        };
        while (run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
        std::clog << "EXITTED FOR SOME REASON... run::" << (run ? "true" : "false") << std::endl;

    }
    
    tui::deinit();
    return 0;
}
