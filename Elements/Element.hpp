#include "../NAMSP_NAME.hpp"
#include "../Data/Color.hpp"
#include "../Data/Position.hpp"
#include "../Screen/ScreenBuffer.hpp"
#include <string>
namespace NAMSP_NAME
{

    enum SizeType{
        ABS,
        REL,
        SCR,
    };

    class ElementAbstract
    {
    public:
        
        virtual ElementAbstract* parent(){return nullptr;}
                //will be made unique
        virtual void child(ElementAbstract* e){delete e;}

        virtual double width(){return 0;} 
        virtual double height(){return 0;} 

        virtual Position wh(){return {width(), height()};}
        virtual Position pos(){return {};}

        virtual void draw(ScreenBuffer& sb){}

        virtual void color(Color col){}
        virtual Color color(){return {};}

        virtual void text(const std::string&){}
        virtual std::string text() const{return "";}

        ElementAbstract(/* args */) {}
        virtual ~ElementAbstract() {}
    };

}
