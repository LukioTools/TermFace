#pragma once
#include <algorithm>
#include <string>
#include <vector>

#include "../Events/KeyboardInput.hpp"
#include "Element.hpp"
#include "ElementAbstract.hpp"

namespace NAMSP_NAME
{
    struct TextStr : public std::vector<KeyboardInputType>
    {
    public:
        //operator std::string() const {
        //    std::string out;
        //    for (size_t i = 0; i < size(); i++)
        //    {
        //        auto& e = this->operator[](i);
        //        out+= e;
        //    }
        //    return out;
        //}
        std::string str() const{
            std::string out;
            for (size_t i = 0; i < size(); i++)
            {
                auto& e = this->operator[](i);
                out+= e;
            }
            return out;
        }
        TextStr& operator+=(const KeyboardInputType k){
            push_back(k);
            return *this;
        }

        friend std::string& operator+=(std::string& str, const TextStr& t){
            str+=t;
            return str;
        }
    };
    
    class Text : public Element
    {
    protected:
        TextStr txt;
    public:
        TextPadding t;
        TextPadding b;
        TextPadding l;
        TextPadding r;
        TextAlingment text_alingment;
        TextBreak text_break;

        void text(const std::string& str) override{
            for (size_t i = 0; i < str.size(); i++)
            {
                if(str[i] & 0b10000000){
                    KeyboardInputType k = str[i];
                    int n_extra_bytes = 0;
                    int index = 1;
                    while (str[i] & (0b10000000 >> index++))
                        n_extra_bytes++;
                    for (size_t j = 0; j < std::min(n_extra_bytes, 3); j++)
                    {
                        k+=str[i];
                        i++;
                    }
                    txt+=k;
                }
                else
                    txt+=str[i];
            }
            
        }
        std::string text() const override{
            return txt.str();
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
                        KeyboardInputType ch = ' ';
                        if( !line_break && txt_index < txt.size()){
                            ch = txt[txt_index];
                            txt_index++;
                            if(ch == '\n'){
                                line_break = true;
                                ch = ' ';
                            }
                        }
                        e.p.a.clear();
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
