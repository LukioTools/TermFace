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
            CENTER,
            RIGHT,
            SCROLL,
        };
        enum Action : unsigned char{
            AUP = UP,
            ADOWN = DOWN,
            AHILIGHT = HILIGHT,
            AHOVER = HOVER,
        };
        enum Button : unsigned char{
            BNONE = 0,
            BLEFT = LEFT,
            BCENTER = CENTER,
            BRIGHT = RIGHT,
            BSCROLL = SCROLL,
        };
        /*
        struct Mouse {
            Button b = BLEFT;
            Action a = AUP;
            bool alt = false;
            bool ctrl = false;
            int x;
            int y;
            Mouse(MouseInputType m):  ctrl(m.a.get(CTRL)), alt(m.a.get(ALT)){
                if(m.a.get(SCROLL)){
                    b = BSCROLL;
                    a = m.a.get(UP) ? AUP : ADOWN;
                    return;
                }
                if(m.a.get(HOVER)){
                    b = BNONE;
                    a = AHOVER;
                    return;
                }
                if(m.a.get(LEFT))
                    b = BLEFT;
                else if(m.a.get(RIGHT))
                    b = BRIGHT;
                else if(m.a.get(CENTER))
                    b = BCENTER;
                if(m.a.get(HILIGHT))
                    a = AHILIGHT;
                else if(m.a.get(DOWN))
                    a = ADOWN;
                else if(m.a.get(UP))
                    a = AUP;
            }
        };
        */
        Button btn(){
            if(a.get(SCROLL))
                return BSCROLL;
            if(a.get(HOVER))
                return BNONE;
            if(a.get(LEFT))
                return BLEFT;
            else if(a.get(RIGHT))
                return BRIGHT;
            else if(a.get(CENTER))
                return BCENTER;
            return BNONE;
        }
        Action act(){
            if(a.get(HOVER))
                return AHOVER;
            if(a.get(HILIGHT))
                return AHILIGHT;
            return a.get(UP) ? AUP : ADOWN;
        }
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

    template<typename Fn>
    class MouseInputLambda : public MouseInput
    {
    public:
        Fn fn;
        void event(MouseInputType c) override{
            fn(c);
        }
        MouseInputLambda(Fn fn) : fn(fn){}
    };

    inline std::vector<MouseInput*> MouseInput::bound_inputs;
}
