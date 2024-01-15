#pragma once
#include "../NAMSP_NAME.hpp"
#include "ElementAttribute.hpp"
#include "Text.hpp"
#include "../Events/KeyboardInput.hpp"
#include "../Events/MouseInput.hpp"
#include "../Events/ArrowInput.hpp"
#include "../Data/BitMask.hpp"
namespace NAMSP_NAME
{
    class TextField : public Text, public MouseInput, public KeyboardInput, public ArrowInput, public ElementAttribute
    {
    protected:
        Color color_hover;
        Color color_active;
        unsigned int cursor;
        BitMask<1> attr;
    public:
        bool active() override{
            return attr.get(ACTIVE);
        }
        bool hover() override{
            return attr.get(HOVER);
        }
        void event(ArrowInputType d) override{
            if(!active())
                return;
            switch (d.dir())
            {
            case Direction::LEFT:
                if(cursor > 0)
                    cursor--;
                break;
            case Direction::RIGHT:
                if(cursor < txt.size())
                    cursor++;
                break;
            case Direction::UP:
            case Direction::DOWN:
            default:
                break;
            }
        }
        void event(KeyboardInputType c) override{
            if(active()){
                auto it = txt.begin()+cursor;
                if(c == 127) {
                    if(!txt.empty() && cursor > 0){
                        txt.erase(it-1);
                        cursor--;
                    }
                }
                else{
                    txt.insert(it, c);
                    cursor++;

                }
            }
        }
        void event(MouseInputType m) override{
            auto insd = inside(m.x, m.y);
            attr.set(HOVER, insd);
            
            switch (m.btn())
            {
            case MouseInputType::BLEFT:
                switch (m.act())
                {
                case MouseInputType::AUP:
                    attr.set(ACTIVE, insd);
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
        }
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

        void draw(ScreenBuffer& sb) override{
            double w = width();
            double h = height();
            double x = posx();
            double y = posy();
            long txt_index = 0;
            bool cursor_printed = false;
            if(clamp(sb, w, h, x, y)){
                bool line_break = false;
                for (size_t hi = 0; hi < h; hi++)
                {
                    line_break = false;
                    for (size_t wi = 0; wi < w; wi++)
                    {
                        auto& e = sb.get(wi+x, hi+y);
                        if(e.z_index > z_index()){
                            continue;
                        }
                        auto ch = ' ';
                        if((txt_index == cursor && !line_break && !cursor_printed)){
                            e.p.a.set(Attribute::UNDERLINE, true);
                            cursor_printed = true;
                        }
                        else 
                            e.p.a.set(Attribute::UNDERLINE, false);

                        if( !line_break && txt_index < txt.size()){
                            ch = txt[txt_index];
                            txt_index++;
                            if(ch == '\n'){
                                line_break = true;
                                ch = ' ';
                            }
                        }
                        e.p.ch = ch;
                        e.p.c = color();
                        e.z_index = z_index();
                    }
                }
            }
            auto c = children();
            if(c)
                for(auto& e : *c){
                    e->draw(sb);
                }
        };

        TextField(/* args */) {}
        ~TextField() {}
    };
} // namespace NAMSP_NAME
