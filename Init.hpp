#pragma once
#include "NAMSP_NAME.hpp"
#include "def.hpp"
#include <cstdlib>
#include <fcntl.h>
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
        //store the old rdbuf
    static std::streambuf* buf_clog; 
    static std::streambuf* buf_cerr; 
    //static std::string l_path = "/dev/pts/4";
        //decl ostream as to prevent rdbuf destruction
    static std::ofstream os;
    inline static void deinit()
    {
            //set the old rdbuf
        std::clog.rdbuf(buf_clog);
        std::cerr.rdbuf(buf_cerr);
        std::cout << norm_buffer << cursor_visible <<disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;

            //fcntl
        //fcntl(STDIN_FILENO, F_SETFL, fcntl_flags);

            //termios
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    inline static int init(int argc, char const *argv[])
    {       //create the ofstream
        os = std::ofstream("/dev/pts/4");
            //swap the rdbuf (it returns the old one)
        buf_clog =  std::clog.rdbuf(os.rdbuf());
        buf_cerr =  std::cerr.rdbuf(os.rdbuf());
        std::cout <<  alt_buffer << cursor_invisible<<enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;

            //fcntl
        //fcntl_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        //fcntl(STDIN_FILENO, F_SETFL, fcntl_flags | O_NONBLOCK);

            //termios
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            //input parsers
        InputManager::parsers.push_back(Parsers::Mouse);
        InputManager::parsers.push_back(Parsers::ArrowKey);
        InputManager::parsers.push_back(Parsers::Characher);
        InputManager::parsers.push_back(Parsers::InputCap);
        return 0;
    }
    
    
    

} // namespace NAMSP_NAME
