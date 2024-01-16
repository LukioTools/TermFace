#pragma once
#include "../NAMSP_NAME.hpp"
#include "EventListener.hpp"
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
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
    KeyboardInputType& operator+=(char c){  //automated construction of the charachters
        for (size_t i = 0; i < sizeof(ch); i++)
        {
            if(ch[i] != 0)
                continue;
            ch[i] = c;
            break;
        }
        return *this;
    }
    friend std::string& operator+=(std::string& str, const KeyboardInputType k){
        for (size_t i = 0; i < sizeof(k.ch) && k[i] != 0; i++)
        {
            str+=k[i];
        }
        return str;
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
    char operator[](size_t index) const{
        if(index >= sizeof(ch))
            throw std::out_of_range("KeyboardInputType::[]::index >= sizeof(ch)");
        return ch[index]; 
    }
    bool operator==(KeyboardInputType k) const {
        return ch[0] == k.ch[0] && ch[1] == k.ch[1] && ch[2] == k.ch[2] && ch[3] == k.ch[3];
    }
    
    bool operator!=(KeyboardInputType k) const {
        return !this->operator==(k);
    }
    bool operator<(KeyboardInputType k) const {
        return getInt() < k.getInt();
    }
    bool operator>(KeyboardInputType k) const {
        return getInt() > k.getInt();
    }
    bool operator<=(KeyboardInputType k) const {
        return getInt() <= k.getInt();
    }
    bool operator>=(KeyboardInputType k) const {
        return getInt() >= k.getInt();
    }
    int getInt() const{
        return *reinterpret_cast<const int*>(ch);
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

    KeyboardInputType(){}
    KeyboardInputType(int c){this->operator=(c);}
    KeyboardInputType(wchar_t c){this->operator=(c);}
    KeyboardInputType(const char* c){this->operator=(c);}
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
