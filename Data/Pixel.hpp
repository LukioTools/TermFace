#pragma once
#include "../NAMSP_NAME.hpp"
#include "Attribute.hpp"
#include "Color.hpp"


namespace NAMSP_NAME
{
    typedef unsigned int pixel_char_t;
    struct Pixel //add the attribute, you can allocata 2 bytes to it
    {
    public:
        Color c= {{200, 200, 200}, {0, 0, 0}};
        pixel_char_t ch = ' ';
        Attribute a;


        friend std::ostream& operator<<(std::ostream& os, const Pixel& p){
            os <<  p.c << p.a;
                //print the shitss
            auto ptr = reinterpret_cast<const char*>(&p.ch);
            for (size_t i = 0; i < sizeof(pixel_char_t); i++)
            {
                auto c = ptr[i]; 
                if(c == 0)
                    break;
                os << c;
            }
            
            return os;
        }

        bool operator!=(const Pixel& p)const {
            return c != p.c || ch != p.ch || a != p.a;
        }
    };
} // namespace NAMSP_NAME
