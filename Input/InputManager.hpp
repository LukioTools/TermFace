#pragma once
#include "../NAMSP_NAME.hpp"
#include <functional>
#include <iostream>
#include <istream>
#include <thread>
#include <vector>
#include "Parsers/Parser.hpp"
#include "Parsers/ArrowKey.hpp"
#include "Parsers/Mouse.hpp"
#include "Parsers/Charachter.hpp"
#include "Parsers/InputCap.hpp"

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
        static void input_loop(std::istream& is, InputManager& state){
            std::clog << "Starting input lööp!" << std::endl;
            while (state.run) {
                auto c = is.get();
                std::cout << "Got: " << c << std::endl;
                if(c == -1){
                    std::cin.clear();
                    std::clog << "Got -1... clearing...!\n";
                }
                else{
                    state.buffer.push_back(c);
                    relööp:
                    for (auto& e : parsers) {
                        if(e)
                            if(e(state.buffer)){
                                std::clog << "Successfull parse from: ";
                                if(e == Parsers::Mouse)
                                    std::clog << "Mouse parser!" << std::endl;
                                if(e == Parsers::ArrowKey)
                                    std::clog << "ArrowKey parser!" << std::endl;
                                if(e == Parsers::Characher)
                                    std::clog << "Characher parser!" << std::endl;
                                if(e == Parsers::InputCap)
                                    std::clog << "InputCap parser!" << std::endl;
                                goto relööp;
                            }
                    }
                }
            }
            std::clog << "Exitting input lööp!" << std::endl;
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

    inline std::vector<Parser> InputManager::parsers;


}