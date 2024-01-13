#pragma once
#include "NAMSP_NAME.hpp"
#include "def.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <unistd.h>
#include "Globals/Termios.hpp"
#include "Input/InputManager.hpp"
#include "Input/Parsers/InputCap.hpp"
#include "Input/Parsers/Charachter.hpp"
#include "Input/Parsers/ArrowKey.hpp"
#include "Input/Parsers/Mouse.hpp"

namespace NAMSP_NAME
{
    static std::streambuf* buf_clog; 
    //static std::string l_path = "/dev/pts/4";
    static std::ofstream os;
    inline static void deinit()
    {
        std::clog.rdbuf(std::cin.rdbuf());
        std::cout << disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    inline static int init(int argc, char const *argv[])
    {
        os = std::ofstream("/dev/pts/4");
        buf_clog =  std::clog.rdbuf(os.rdbuf());
        std::cout << enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        InputManager::parsers.push_back(Parsers::Mouse);
        InputManager::parsers.push_back(Parsers::ArrowKey);
        InputManager::parsers.push_back(Parsers::Characher);
        InputManager::parsers.push_back(Parsers::InputCap);
        return 0;
    }
    
    
    

} // namespace NAMSP_NAME
