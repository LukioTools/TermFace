#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
namespace NAMSP_NAME
{
    struct KeyboardInputType
    {
        int ch = ' ';

        void operator=(int c){
            ch = c;
        }
        friend std::ostream& operator<<(std::ostream& os, KeyboardInputType k){
            auto p = reinterpret_cast<char*>(&k.ch);
            for (size_t i = 0; i < sizeof(ch); i++)
            {
                char c = p[i];
                if(c == 0)
                    break;
                os << c;
            }
            return os;
        }
        operator int(){
            return ch;
        }
        KeyboardInputType(){}
        KeyboardInputType(int c): ch(c){}
    };
    
    //typedef char KeyboardInputType;
    class KeyboardInput : public EventListener<void, KeyboardInputType>
    {
    private:
    public:
        static std::vector<KeyboardInput*> bound_inputs;
        
        static void call(KeyboardInputType c){
            for(auto& e : bound_inputs)
                if(e)
                    e->event(c);
        }

        KeyboardInput() {
            bound_inputs.push_back(this);
        }
        ~KeyboardInput() {
            for (size_t i = 0; i < bound_inputs.size(); i++)
            {
                if(bound_inputs[i] != this)
                    continue;
                auto it = bound_inputs.begin();
                std::advance(it, i);
                bound_inputs.erase(it);
                #if defined(EventListenerDEBUG)
                std::clog << "KeyboardInput event listener: " << this << " unbound successfully!\n";
                #endif // EventListenerDEBUG
                
                return;
            }
            #if defined(EventListenerDEBUG) || defined (EventListenerERRORS)
            std::cerr << "KeyboardInput event listener: " << this << " was not unbound: did not find in vector!\n";
            #endif // EventListenerDEBUG
        }
    };

    inline std::vector<KeyboardInput*> KeyboardInput::bound_inputs;


    template<typename Fn>
    class KeyboardInputLambda : public KeyboardInput
    {
    public:
        Fn fn;
        void event(KeyboardInputType c) override{
            fn(c);
        }
        KeyboardInputLambda(Fn fn) : fn(fn){}
    };
}
