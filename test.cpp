#include "Events/ArrowInput.hpp"
#include "Init.hpp"
#include "def.hpp"
#include <algorithm>
#include <bitset>
#include <chrono>
#include <cstring>
#include <ios>
#include <iostream>
#include "Input/Parsers/ArrowKey.hpp"
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <vector>

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

static termios newt, oldt;
int main(int argc, char const *argv[])
{
    tui::init(argc,argv);
    

    
    //std::cout << enable_mouse(SET_SGR_EXT_MODE_MOUSE) << enable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;

    while (true) {
        char n = std::cin.get();
        KeyboardInputType k = n;
        std::cout << std::dec <<  n << "  0x" << std::hex << n << "  0b" << std::bitset<8>(n) << "  char: " << (char) n << std::endl;
        if(n == 1)
            break;
        if((n & 0b10000000)){
            int n_extra_bytes = 0;
            int index = 1;
            while ((n & (0b10000000 >> index++))) {
                n_extra_bytes++;
            }
            if(n_extra_bytes > 3)
                throw std::runtime_error("Moar than 4");
            for (size_t i = 0; i < n_extra_bytes; i++)
            {
                k << std::cin.get();
            }
            std::cout << "Got: " << k << std::endl;
        }
        
    }


    //std::cout << disable_mouse(SET_SGR_EXT_MODE_MOUSE) << disable_mouse(SET_ANY_EVENT_MOUSE) << std::endl;


        //termios
    //tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    tui::deinit();
    return 0;
}
