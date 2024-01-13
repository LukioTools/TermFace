#pragma once
#include "../NAMSP_NAME.hpp"
#include <chrono>
#include <iostream>
#include <istream>
#include <ostream>
#include <thread>
#include <vector>
#include "Parsers/Parser.hpp"
#if defined(DEBUG)

#include "Parsers/ArrowKey.hpp"
#include "Parsers/Mouse.hpp"
#include "Parsers/Charachter.hpp"
#include "Parsers/InputCap.hpp"

#endif

namespace NAMSP_NAME
{

    class InputManager
    {
    private:
    public:
        std::vector<char> buffer;
        std::thread run_thread;
        bool run = true;
        static std::vector<Parser> parsers;
        static std::chrono::microseconds delay_between_getch;
        static void input_loop(std::istream& is, InputManager& state){
            #if defined(DEBUG)
            std::clog << "Starting input lööp!" << std::endl;
            #endif
            while (state.run) {
                int c;
                while (state.run) {
                    c = is.get();
                    if(c == -1)
                        is.clear();
                    else
                        break;
                    std::this_thread::sleep_for(delay_between_getch); //dont kill the thread
                }
                #if defined(DEBUG)
                std::cout << "Got: " << c << std::endl;
                #endif
                if(c == -1){
                    std::cin.clear();
                    #if defined(DEBUG)
                    std::clog << "Got -1... clearing...!\n";
                    #endif
                }
                else{
                    state.buffer.push_back(c);
                    relööp:
                    for (auto& e : parsers) {
                        if(e)
                            if(e(state.buffer)){
                                #if defined(DEBUG)
                                                                
                                std::clog << "Successfull parse from: ";
                                if(e == Parsers::Mouse)
                                    std::clog << "Mouse parser!" << std::endl;
                                if(e == Parsers::ArrowKey)
                                    std::clog << "ArrowKey parser!" << std::endl;
                                if(e == Parsers::Characher)
                                    std::clog << "Characher parser!" << std::endl;
                                if(e == Parsers::InputCap)
                                    std::clog << "InputCap parser!" << std::endl;
                                #endif // DEBUG

                                goto relööp;
                            }
                    }
                }
            }
            #if defined(DEBUG)
            std::clog << "Exitting input lööp!" << std::endl;
            #endif

        }
        InputManager(std::istream& is = std::cin) : run_thread(input_loop, std::ref(is), std::ref(*this)) {}
        template<typename Fn>
        InputManager(Fn fn, std::istream& is) : run_thread(fn, std::ref(is), std::ref(*this)){}
        ~InputManager() {
            run = false;
            #if defined(DEBUG)
            std::clog << "Waiting for thread.." << std::flush;
            #endif

            #if defined(InputManagerDEATTACH)
            
            
            if(run_thread.joinable())
                run_thread.detach();

            #else

            if(run_thread.joinable())
                run_thread.join();
            
            #endif // InputManagerDEATTACH
            #if defined(DEBUG)
            std::clog << " SUCCESS" << std::endl;
            #endif

            
        }
    };

    inline std::vector<Parser> InputManager::parsers;
    inline std::chrono::microseconds InputManager::delay_between_getch = std::chrono::milliseconds(16);


}