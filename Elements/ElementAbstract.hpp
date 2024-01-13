#pragma once
#include "../NAMSP_NAME.hpp"
#include "../Screen/ScreenBuffer.hpp"
#include "../Data/Color.hpp"
#include "../Data/Position.hpp"
#include <vector>

namespace NAMSP_NAME
{
    enum SizeType : unsigned char{
        ABS,
        REL,
        SCR,
    };

    enum TextAlingment : unsigned char{
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        CENTER_LEFT,
        CENTER_RIGHT,
        CENTER,
    };
        //maby implement in the bitmask
    enum TextBreak : unsigned char{
        ANYWHERE,
        WORDBREAK,
    };

    typedef unsigned char TextPadding;


    class ElementAbstract
    {
    protected:
    public:
            //returns if displayable
        static bool clamp(const ScreenBuffer& sb, double& w, double& h, double& x, double& y){
            if(x >= sb.width() || y >= sb.height())
                return false;
            if(x+w <= 0 || y+h <= 0)
                return false;
            if(x < 0)
                w = w+x;
            if(y < 0)
                h = h+y;
            if(x+w >= sb.width()){
                w = sb.width()-x;
            }
            if(y+h >= sb.height()){
                h = sb.height()-y;
            }
            //end adjustments
            if(x < 0){
                x = 0;
            }
            if(y < 0){
                y = 0;
            }
            return true;
        }
        
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

        virtual void width  (double){} 
        virtual void height (double){} 
        virtual void posx   (double){} 
        virtual void posy   (double){}

        virtual double abs_width(){return 0;};  
        virtual double abs_height(){return 0;}; 
        virtual double abs_posx(){return 0;};   
        virtual double abs_posy(){return 0;};   

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
    
} // namespace NAMSP_NAME
