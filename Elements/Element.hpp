#include "../NAMSP_NAME.hpp"
#include "../Data/Color.hpp"
#include "../Data/Position.hpp"
#include "../Screen/ScreenBuffer.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace NAMSP_NAME
{

    enum SizeType : unsigned char{
        ABS,
        REL,
        SCR,
    };

    class ElementAbstract
    {
    protected:
            //returns if displayable
        bool clamp(const ScreenBuffer& sb, double& w, double& h, double& x, double& y){
            if(x >= sb.width() || y >= sb.height())
                return false;
            if(x+w < 0 || y+h < 0)
                return false;
            if(x+w >= sb.width()){
                w = sb.width()-x-1;
            }
            if(y+h >= sb.height()){
                h = sb.height()-y-1;
            }
            if(y < 0){
                y = 0;
            }
            if(x < 0){
                x = 0;
            }
            return true;
        }
    public:
        
        virtual ElementAbstract* parent(){return nullptr;}
        virtual void parent(ElementAbstract* e){}
                //will be made unique
        virtual void child(std::unique_ptr<ElementAbstract> e){
            auto c = children();
            if(c)
                c->push_back(std::move(e));
        }
        virtual std::vector<std::unique_ptr<ElementAbstract>>* children(){return nullptr;}

        virtual double width(){return 0;} 
        virtual double height(){return 0;} 
        virtual double posx(){return 0;} 
        virtual double posy(){return 0;} 
        virtual std::size_t z_index(){return 0;}
        virtual void z_index(std::size_t){}


        virtual Position wh(){return {width(), height()};}
        virtual Position pos(){return {posx(), posy()};}

        virtual void draw(ScreenBuffer& sb){
            auto c = children();
            if(c)
            for (auto& e : *c)
                e->draw(sb);
        }

        virtual void color(Color col){}
        virtual Color color(){return {};}

        virtual void text(const std::string&){}
        virtual std::string text() const{return "";}

        ElementAbstract(/* args */) {}
        virtual ~ElementAbstract() {}
    };
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
        void color(Color col) override {c = col;}
        Color color() override {return c;}

        void draw(ScreenBuffer &sb) override{
            for (size_t h = 0; h < sb.height(); h++)
            {
                for (size_t w = 0; w < sb.width(); w++)
                {
                    std::clog << "Get: " << w << " : " << h << std::endl;
                    auto& e = sb.get(w, h);
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
 
    class Element : public ElementAbstract
    {
    protected:
        ElementAbstract* parent_ptr = nullptr;
        std::vector<std::unique_ptr<ElementAbstract>> children_vec;
        Position p; //pos {x, y}
        float w; // width
        float h; // height
        SizeType pxt; // pos x type
        SizeType pyt; // pos y type
        SizeType wt; // width type
        SizeType ht; // height type
        Color c;
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
                    return parent()->width()*w/100.;
            case SizeType::SCR:
                return w/100.*WIDTH;
            case SizeType::ABS:
            default:
                return w;
            }

        } 
        double height() override{
            switch (ht)
            {
            case SizeType::REL:
                if(parent())
                    return parent()->height()*h/100.;
            case SizeType::SCR:
                return h/100.*HEIGHT;
            case SizeType::ABS:
            default:
                return h;
            }
        }
        double posx() override{
            switch (pxt)
            {
            case SizeType::REL:
                if(parent())
                    return parent()->width()*p.x/100.;
            case SizeType::SCR:
                return p.x/100.*WIDTH;
            case SizeType::ABS:
            default:
                return p.x;
            }
        }
        double posy() override{
            switch (pyt)
            {
            case SizeType::REL:
                if(parent())
                    return parent()->height()*p.y/100.;
            case SizeType::SCR:
                return p.y/100.*HEIGHT;
            case SizeType::ABS:
            default:
                return p.y;
            }
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
                        auto e = sb.get(wi, hi);
                        if(e.z_index < z_index())
                            continue;
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

        void color(Color col) override {c = col;}
        Color color() override {return c;}


        Element(/* args */) {}
        ~Element() {}
    };

}
