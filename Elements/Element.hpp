#pragma once
#include "../NAMSP_NAME.hpp"
#include "ElementAbstract.hpp"

namespace NAMSP_NAME
{

    class Element : public ElementAbstract
    {
    protected:
        ElementAbstract* parent_ptr = nullptr;
        std::vector<std::unique_ptr<ElementAbstract>> children_vec;
        Position p; //pos {x, y}
        float w; // width
        float h; // height
        SizeType pxt = ABS; // pos x type
        SizeType pyt = ABS; // pos y type
        SizeType wt = ABS; // width type
        SizeType ht = ABS; // height type
        Color color_normal;
        size_t zi = 1; //z index
    public:
        void z_index(std::size_t z) override{
            zi = z;
        }
        std::size_t z_index() override{
            return zi;
        }
        ElementAbstract * parent() override{
            return parent_ptr;
        }
        void parent(ElementAbstract *e) override{
            parent_ptr = e;
        }
        void child(std::unique_ptr<ElementAbstract> e) override{
            e->parent(this);
            auto c = children();
            if(c)
                c->push_back(std::move(e));
        }
        std::vector<std::unique_ptr<ElementAbstract>>* children() override{
            return &children_vec;
        }

        double width() override{
            switch (wt)
            {
            case SizeType::REL:
                if(parent())
                    return (parent()->width()*w/100.);
            case SizeType::SCR:
                return (w/100.*WIDTH);
            case SizeType::ABS:
            default:
                return (w);
            }

        } 
        double height() override{
            switch (ht)
            {
            case SizeType::REL:
                if(parent())
                    return (parent()->height()*h/100.);
            case SizeType::SCR:
                return (h/100.*HEIGHT);
            case SizeType::ABS:
            default:
                return (h);
            }
        }
        double posx() override{
            switch (pxt)
            {
            case SizeType::REL:
                if(parent())
                    return (parent()->width()*p.x/100.);
            case SizeType::SCR:
                return (p.x/100.*WIDTH);
            case SizeType::ABS:
            default:
                return (p.x);
            }
        }
        double posy() override{
            switch (pyt)
            {
            case SizeType::REL:
                if(parent())
                    return (parent()->height()*p.y/100.);
            case SizeType::SCR:
                return ( p.y/100.*HEIGHT);
            case SizeType::ABS:
            default:
                return (p.y);
            }
        }

        void width(double wi) override{
            w = wi;
        }void height(double he) override{
            h = he;
        }void posx(double x) override{
            p.x = x;
        }void posy(double y) override{
            p.y = y;
        }

        double abs_width() override{
            return w;
        }double abs_height() override{
            return h;
        }double abs_posx() override{
            return p.x;
        }double abs_posy() override{
            return p.y;
        }

        void    st_width(SizeType t) override{
            wt = t;
        }void   st_height(SizeType t) override{
            ht = t;
        }void   st_posx(SizeType t) override{
            pxt = t;
        }void   st_posy(SizeType t) override{
            pyt = t;
        }

        SizeType    st_width() override{
            return wt;
        }SizeType   st_height() override{
            return ht;
        }SizeType   st_posx() override{
            return pxt;
        }SizeType   st_posy() override{
            return pyt;
        }

        Position wh() override{return {width(), height()};}
        Position pos() override{return {posx(), posy()};}
        void draw(ScreenBuffer& sb) override {
            double w = width();
            double h = height();
            double x = posx();
            double y = posy();

            if(clamp(sb, w, h, x, y)){
                for (size_t hi = 0; hi < h; hi++)
                {
                    for (size_t wi = 0; wi < w; wi++)
                    {
                        auto& e = sb.get(wi+x, hi+y);
                        if(e.z_index > z_index()){
                            continue;
                        }
                        e.p.ch = ' ';
                        e.p.c = color();
                    }
                }
            }
            auto c = children();
            if(c)
                for(auto& e : *c){
                    e->draw(sb);
                }
        }

        void colornormal(Color col) override {color_normal = col;}
        Color color() override {
            return color_normal;
        }


        Element(/* args */) {}
        ~Element() {}
    };

}
