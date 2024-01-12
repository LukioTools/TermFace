#pragma once
#include "../NAMSP_NAME.hpp"
#include "Color.hpp"


namespace NAMSP_NAME
{
    typedef unsigned int pixel_char_t;
    class Pixel //add the attribute, you can allocata 2 bytes to it
    {
    public:
        Color c;
        pixel_char_t ch;


        friend std::ostream& operator<<(std::ostream& os, const Pixel& p){
            os <<  p.c;


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

        Pixel(/* args */) {}
        ~Pixel() {}
    };
} // namespace NAMSP_NAME
