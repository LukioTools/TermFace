#pragma once
#include "../NAMSP_NAME.hpp"
#include "../def.hpp"
#include <ostream>

namespace NAMSP_NAME
{
    struct RGB
    {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
    };

    struct BGColor : RGB
    {
        friend std::ostream& operator<<(std::ostream& os, const BGColor& c){
            os << color_bg_rgb(c);
            return os;
        }
    };
    struct FGColor : RGB
    {
        friend std::ostream& operator<<(std::ostream& os, const FGColor& c){
            os << color_fg_rgb(c);
            return os;
        }
    };

    struct Color
    {
        BGColor bg;
        FGColor fg;

        friend std::ostream& operator<<(std::ostream& os, const Color& c){
            os << c.fg << c.bg;
            return os;
        }
    };
    
} // namespace NAMSP_NAME
