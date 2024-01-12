#pragma once
#include "NAMSP_NAME.hpp"
#include "def.hpp"
#include <iostream>
#include <unistd.h>
#include "Globals/Termios.hpp"


namespace NAMSP_NAME
{
    inline static int init(int argc, char const *argv[])
    {
        std::cout << enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        return 0;
    }

    inline static int deinit()
    {
        std::cout << disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 0;
    }
    

} // namespace NAMSP_NAME
