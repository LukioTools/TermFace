#pragma once
#include "../NAMSP_NAME.hpp"
#include "ElementAbstract.hpp"

namespace NAMSP_NAME
{

    

    class Body : public ElementAbstract
    {
    protected:
        std::vector<std::unique_ptr<ElementAbstract>> children_vec;
        Color c;
        std::size_t zi = 0; 
    public:
        void z_index(std::size_t z) override{
            zi =z;
        }
        std::size_t z_index() override{
            return zi;
        }
        std::vector<std::unique_ptr<ElementAbstract>> * children() override{
            return &children_vec;
        }
        void child(std::unique_ptr<ElementAbstract> e) override{
            e->parent(this);
            auto c = children();
            if(c)
                c->push_back(std::move(e));
        }
        void colornormal(Color col) override {c = col;}
        Color color() override {return c;}

        void draw(ScreenBuffer &sb) override{
            for (size_t h = 0; h < sb.height(); h++)
            {
                for (size_t w = 0; w < sb.width(); w++)
                {
                    auto& e = sb.get(w, h);
                    e.p.a.clear();//clear();
                    e.z_index = z_index();
                    e.p.c = color();
                    e.p.ch = ' ';
                }
            }

            auto c = children();
            if(c)
            for (auto& e : *c)
                e->draw(sb);
        }


        double height() override{
            return HEIGHT;
        }
        double width() override{
            return WIDTH;
        }
        double posx() override{
            return 0;
        }
        double posy() override{
            return 0;
        }


        Position pos() override{
            return {0,0};
        }
        ElementAbstract* parent() override{
            return nullptr;
        }
        void parent(ElementAbstract *e) override{}
        Position wh() override{
            return {static_cast<double>(WIDTH), static_cast<double>(HEIGHT)};
        }

        Body(/* args */) {}
        ~Body() {}
    };
    static Body body;

}