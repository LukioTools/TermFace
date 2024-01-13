#include "../NAMSP_NAME.hpp"
#include "../Data/Color.hpp"
#include "../Data/Position.hpp"
#include "../Screen/ScreenBuffer.hpp"
#include <algorithm>
#include <cmath>
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
                w = sb.width()-x;
            }
            if(y+h >= sb.height()){
                h = sb.height()-y;
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

        virtual void width(double){} 
        virtual void height(double){} 
        virtual void posx(double){} 
        virtual void posy(double){}

        virtual SizeType st_width(){return ABS;} 
        virtual SizeType st_height(){return ABS;} 
        virtual SizeType st_posx(){return ABS;} 
        virtual SizeType st_posy(){return ABS;}

        virtual void st_width(SizeType ){} 
        virtual void st_height(SizeType ){} 
        virtual void st_posx(SizeType ){} 
        virtual void st_posy(SizeType ){}


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
        SizeType pxt = ABS; // pos x type
        SizeType pyt = ABS; // pos y type
        SizeType wt = ABS; // width type
        SizeType ht = ABS; // height type
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
                        //std::clog << "Element draw: " << wi << " : " << hi << std::endl;
                        auto& e = sb.get(wi, hi);
                        if(e.z_index > z_index()){
                            std::clog << "Skipping since bigger zindex: " << e.z_index <<'/'<<z_index() << std::endl;
                            continue;
                        }
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
