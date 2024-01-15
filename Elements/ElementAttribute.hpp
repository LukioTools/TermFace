#pragma once
#include "../NAMSP_NAME.hpp"
namespace NAMSP_NAME
{

    class ElementAttribute //usefull?
    {
    protected:
    public:
        enum Enum{
            HOVER,
            ACTIVE,
        };

        virtual bool hover(){
            return false;
        }
        virtual bool active(){
            return false;
        }
        ElementAttribute(/* args */) {}
        ~ElementAttribute() {}
    };
}