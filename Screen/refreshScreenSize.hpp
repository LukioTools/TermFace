#pragma once
#include <sys/ioctl.h>
#include <unistd.h>
#include "../NAMSP_NAME.hpp"
#include "../Globals/ScreenSize.hpp"

namespace NAMSP_NAME
{
    inline void refresh_screen_size(int = 0){
        winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
        WIDTH = w.ws_col;
        HEIGHT = w.ws_row;
    }
}