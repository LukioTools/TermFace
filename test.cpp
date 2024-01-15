#include "Events/ArrowInput.hpp"
#include "Events/KeyboardInput.hpp"
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "def.hpp"
#include <bitset>
#include <chrono>
#include <ios>
#include <iostream>
#include "Input/Parsers/ArrowKey.hpp"
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <vector>



static termios newt, oldt;
int main(int argc, char const *argv[])
{
    tui::init(argc,argv);
    tui::InputManager im;

    
    //std::cout << enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;
    bool run = true;
    tui::ArrowInputLambda al =[&run](tui::ArrowInputType a){
        std::cout << "Parse" << std::endl;
        if(a.dir() == tui::Direction::LEFT && a.ctrl())
            run = false; 
    };
    tui::KeyboardInputLambda kl = [&run](tui::KeyboardInputType k){
        std::cout << "KEY: " << k << std::endl;
        if(k == 1)
            run = false;
    };
    while (run) {
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }


    //std::cout << disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;


        //termios
    //tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    tui::deinit();
    return 0;
}
