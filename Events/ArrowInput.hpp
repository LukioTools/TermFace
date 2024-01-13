#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include <iostream>
#include <iterator>
#include <vector>
namespace NAMSP_NAME
{
    enum Direction : char{
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    class ArrowInput : public EventListener<void, Direction>
    {
    private:
    public:
        static std::vector<ArrowInput*> bound_inputs;

        
        static void call(Direction c){
            for(auto& e : bound_inputs)
                if(e)
                    e->event(c);
        }
        ArrowInput() {
            bound_inputs.push_back(this);
        }
        ~ArrowInput() {
            for (size_t i = 0; i < bound_inputs.size(); i++)
            {
                if(bound_inputs[i] != this)
                    continue;
                auto it = bound_inputs.begin();
                std::advance(it, i);
                bound_inputs.erase(it);
                #if defined(EventListenerDEBUG)
                std::clog << "ArrowInput event listener: " << this << " unbound successfully!\n";
                #endif // EventListenerDEBUG
                
                return;
            }
            #if defined(EventListenerDEBUG) || defined (EventListenerERRORS)
            std::cerr << "ArrowInput event listener: " << this << " was not unbound: did not find in vector!\n";
            #endif // EventListenerDEBUG
        }
    };

    template<typename Fn>
    class ArrowInputLambda : public ArrowInput
    {
    public:
        Fn fn;
        void event(Direction c) override{
            fn(c);
        }
        ArrowInputLambda(Fn fn) : fn(fn){}
    };

    inline std::vector<ArrowInput*> ArrowInput::bound_inputs;
}
