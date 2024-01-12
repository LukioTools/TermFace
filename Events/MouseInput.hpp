#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include "../Data/BitMask.hpp"
namespace NAMSP_NAME
{
    struct MouseInputType
    {
        int x;
        int y;
        enum Attribute : unsigned char{
            UP,
            DOWN,
            HILIGHT,
            HOVER,
            CTRL,
            ALT,
            LEFT,
            RIGHT,
            CENTER,
            SCROLL,
        };
        BitMask<2> a;

    };
    
    class MouseInput : public EventListener<void, MouseInputType>
    {
    private:
    public:
        static std::vector<MouseInput*> bound_inputs;

        static void call(MouseInputType c){
            for(auto& e : bound_inputs)
                if(e)
                    e->event(c);
        }
        
        MouseInput() {
            bound_inputs.push_back(this);
        }
        ~MouseInput() {
            for (size_t i = 0; i < bound_inputs.size(); i++)
            {
                if(bound_inputs[i] != this)
                    continue;
                auto it = bound_inputs.begin();
                std::advance(it, i);
                bound_inputs.erase(it);
                #if defined(EventListenerDEBUG)
                std::clog << "MouseInput event listener: " << this << " unbound successfully!\n";
                #endif // EventListenerDEBUG
                
                return;
            }
            #if defined(EventListenerDEBUG) || defined (EventListenerERRORS)
            std::cerr << "MouseInput event listener: " << this << " was not unbound: did not find in vector!\n";
            #endif // EventListenerDEBUG
        }
    };

    inline std::vector<MouseInput*> MouseInput::bound_inputs;
}
