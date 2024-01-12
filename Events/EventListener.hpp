#pragma once

#include "../NAMSP_NAME.hpp"
namespace NAMSP_NAME
{
    template<typename Ret = void, typename... Args>
    class EventListener
    {
    public:
        virtual Ret event(Args... a){}
        EventListener(/* args */) {}
        ~EventListener() {}
    };    
}
