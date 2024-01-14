#pragma once
#include "Text.hpp"
#include "../Events/MouseInput.hpp"
#include <iostream>

namespace NAMSP_NAME
{

    class Button : public Text, public MouseInput  
    {
    protected:
        Color color_hover;
        Color color_active;
        BitMask<1> attr;
        enum ElementAttribute{
            HOVER,
            ACTIVE,
        };
            //maby virtual
        bool hover(){
            return attr.get(HOVER);
        }
            //maby virtual
        bool active(){
            return attr.get(ACTIVE);
        }
        virtual void onClick(MouseInputType m){}
        void event(MouseInputType m) override{
            bool insd = inside(m.x, m.y);
            auto l = wh();
            std::clog << "Inside: " << (insd ? "true" : "false") << std::endl;
            std::clog << l.x+posx() << '/' << l.y+posy() << std::endl;
            std::clog << m.x << '/' << m.y <<  std::endl;
            attr.set(HOVER, insd);
            
            switch (m.btn())
            {
            case MouseInputType::BLEFT:
                switch (m.act())
                {
                case MouseInputType::AUP:
                    attr.set(ACTIVE, insd);
                    if(insd)
                        onClick(m);
                    break;
                case MouseInputType::ADOWN:
                    attr.set(ACTIVE, insd);
                    break;
                case MouseInputType::AHILIGHT:
                    attr.set(ACTIVE, insd);
                    break;
                case MouseInputType::AHOVER:
                default:
                    break;
                }
                break;
            case MouseInputType::BCENTER:
            case MouseInputType::BRIGHT:
            case MouseInputType::BSCROLL:
            default:
                break;
            }
            
        };
    public:
            //maby virtual
        void colorhover(Color c) override{
            color_hover = c;
        }
        void coloractive(Color c) override{
            color_active = c;
        }
        Color color() override{ //order matters
            if(active())
                return color_active;
            if(hover())
                return color_hover;
            return color_normal;
        }

        ~Button() {}
    };

}