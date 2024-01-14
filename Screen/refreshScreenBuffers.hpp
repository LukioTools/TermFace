#pragma once
#include <sys/ioctl.h>
#include <unistd.h>
#include "../NAMSP_NAME.hpp"
#include "../Globals/ScreenBuffers.hpp"
#include "../Globals/ScreenSize.hpp"

namespace NAMSP_NAME
{
    inline void refresh_screen_buffers(int = 0){
        render_buffer.alloc(WIDTH, HEIGHT);
        display_buffer.alloc(WIDTH, HEIGHT);
    }
}