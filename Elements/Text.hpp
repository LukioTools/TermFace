#pragma once
#include "Element.hpp"

namespace NAMSP_NAME
{
    class Text : public Element
    {
        std::string txt;
    public:
        void text(const std::string& str) override{
            txt = str;
        }
        std::string text() const override{
            return txt;
        }
        void draw(ScreenBuffer& sb) override{
            
        };
        Text(/* args */) {}
        ~Text() {}
    };
} // namespace NAMSP_NAME
