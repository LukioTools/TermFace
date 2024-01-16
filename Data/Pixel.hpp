#pragma once
#include "../NAMSP_NAME.hpp"
#include "Attribute.hpp"
#include "Color.hpp"
#include "../Events/KeyboardInput.hpp"

namespace NAMSP_NAME
{
    struct Pixel //add the attribute, you can allocata 2 bytes to it
    {
    public:
        Color c= {{200, 200, 200}, {0, 0, 0}};
        KeyboardInputType ch = ' ';
        Attribute a;


        friend std::ostream& operator<<(std::ostream& os, const Pixel& p){
            os <<  p.c << p.a << p.ch;
            return os;
        }

        bool operator!=(const Pixel& p)const {
            return c != p.c || ch != p.ch || a != p.a;
        }
    };
} // namespace NAMSP_NAME
