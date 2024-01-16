#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
namespace NAMSP_NAME
{
struct KeyboardInputType
{
    char ch[4] = {0};
    KeyboardInputType& operator<<(char c){  //automated construction of the charachters
        for (size_t i = 0; i < sizeof(ch); i++)
        {
            if(ch[i] != 0)
                continue;
            ch[i] = c;
            break;
        }
        return *this;
    }
    bool empty(){
        return getInt() == 0;
    }
    int nbytes(){
        int ret = 0;
        for (size_t i = 0; i < sizeof(ch) && ch[i] != 0; i++)
            ret++;
        return ret;
    }
    char operator[](size_t index){
        if(index >= sizeof(ch))
            throw std::out_of_range("KeyboardInputType::[]::index >= sizeof(ch)");
        return ch[index]; 
    }
    bool operator!=(KeyboardInputType k){
        return memcmp(ch, k.ch, sizeof(ch)) != 0;
    }
    bool operator==(KeyboardInputType k){
        return memcmp(ch, k.ch, sizeof(ch)) != 0;
    }
    bool operator!=(int k){
        return memcmp(ch, &k, sizeof(ch)) != 0;
    }
    bool operator==(int k){
        return memcmp(ch, &k, sizeof(ch)) != 0;
    }
    bool operator<(KeyboardInputType k){
        return getInt() < k.getInt();
    }
    bool operator>(KeyboardInputType k){
        return getInt() > k.getInt();
    }
    bool operator<=(KeyboardInputType k){
        return getInt() <= k.getInt();
    }
    bool operator>=(KeyboardInputType k){
        return getInt() >= k.getInt();
    }
    int getInt(){
        return *reinterpret_cast<int*>(ch);
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
    inline void clear(){
        memset(ch, 0, sizeof(ch));
    }
    inline wchar_t wchar(){
        wchar_t wc = 0;
        memcpy(&wc, ch, std::min(sizeof(wc), sizeof(ch)));
        return wc;
    }
    inline void wchar(wchar_t wc){
        clear();
        memcpy(ch, &wc, std::min(sizeof(wc), sizeof(ch)));
    }
    inline void operator=(char c){
        clear();
        ch[0] = c;
    }
    inline void operator=(wchar_t c){
        wchar(c);
    }
    KeyboardInputType(){}
    KeyboardInputType(char c){this->operator=(c);}
    KeyboardInputType(wchar_t c){this->operator=(c);}
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
