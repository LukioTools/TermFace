#include "../NAMSP_NAME.hpp"
#include <functional>
#include <iostream>
#include <istream>
#include <thread>
#include <vector>
#include "Parsers/Parser.hpp"


namespace NAMSP_NAME
{

    class InputManager
    {
    private:
    public:
        std::vector<char> buffer;
        std::thread run_thread;
        bool run;
        static std::vector<Parser> parsers;
        static void input_loop(std::istream& is, InputManager& state){ 
            while (state.run) {
                auto c = is.get();
                if(c == -1)
                    std::cin.clear();
                else
                    state.buffer.push_back(c);
            }
        }
        InputManager(std::istream& is = std::cin) : run_thread(input_loop, std::ref(is), std::ref(*this)) {}
        template<typename Fn>
        InputManager(Fn fn, std::istream& is) : run_thread(fn, std::ref(is), std::ref(*this)){}
        ~InputManager() {
            run = false;
            #if defined(InputManagerDEATTACH)
            
            if(run_thread.joinable())
                run_thread.detach();

            #else

            if(run_thread.joinable())
                run_thread.join();
            
            #endif // InputManagerDEATTACH
            
            
        }
    };


}