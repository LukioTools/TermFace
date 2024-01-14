#pragma once
#include "Element.hpp"
#include "ElementAbstract.hpp"

namespace NAMSP_NAME
{
    class Text : public Element
    {
    protected:
        std::string txt; // maby implement 8 byte string
    public:
        TextPadding t;
        TextPadding b;
        TextPadding l;
        TextPadding r;
        TextAlingment text_alingment;
        TextBreak text_break;

        void text(const std::string& str) override{
            txt = str;
        }
        std::string text() const override{
            return txt;
        }
        void draw(ScreenBuffer& sb) override{
            double w = width();
            double h = height();
            double x = posx();
            double y = posy();
            long txt_index = 0;
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
        Text(/* args */) {}
        ~Text() {}
    };
} // namespace NAMSP_NAME
