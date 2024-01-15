#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include "../Data/BitMask.hpp"
#include <iostream>
#include <iterator>
#include <vector>
namespace NAMSP_NAME
{
    enum Direction : char{
        UP,
        DOWN,
        RIGHT,
        LEFT,
    };

    struct ArrowInputType{
        BitMask<1> bm;
        enum Attr{
            RESERVED_DIR0,
            RESERVED_DIR1,
            CTRL,
            SHIFT,
        };
        Direction dir(){
            return static_cast<Direction>(bm.mask[0] & 0b11);
        };
        inline void dir(Direction d){
            bm.mask[0] &= (~0b11); // turn off all that are not first 2 bytes
            bm.mask[0] |= d; // or the shit together
        }
        inline bool get(Attr a){
            return bm.get(a);
        }
        inline void set(Attr a, bool on){
            bm.set(a, on);
        }
        inline bool shift(){
            return get(SHIFT);
        }
        inline bool ctrl(){
            return get(CTRL);
        }
        inline void shift(bool on){
            set(SHIFT, on);
        }
        inline void ctrl(bool on){
            set(CTRL, on);
        }
        bool operator==(Direction d){
            return d == dir();
        }
        ArrowInputType(){}
        ArrowInputType(Direction d){dir(d);}
    };
    class ArrowInput : public EventListener<void, ArrowInputType>
    {
    private:
    public:
        static std::vector<ArrowInput*> bound_inputs;

        
        static void call(ArrowInputType c){
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
        void event(ArrowInputType c) override{
            fn(c);
        }
        ArrowInputLambda(Fn fn) : fn(fn){}
    };

    inline std::vector<ArrowInput*> ArrowInput::bound_inputs;
}
