#pragma once
#include "../NAMSP_NAME.hpp"
#include <sys/poll.h>
#include <chrono>
#include <iostream>
#include <istream>
#include <ostream>
#include <thread>
#include <unistd.h>
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
            pollfd fds;
            fds.fd = STDIN_FILENO; /* this is STDIN */
            fds.events = POLLIN;
            while (state.run) {
                
                //while (true) {  //wait until has char
                //    if(!state.run)
                //        return;
                //    int ret = poll(&fds, 1, 0);
                //    if(ret == 1)
                //        break;
                //    if(ret == -1)
                //        std::cin.clear();
                //    std::this_thread::sleep_for(std::chrono::milliseconds(16));
                //}


                int c = is.get();
                if(c == -1){
                    is.clear();
                    continue;
                }
                
                state.buffer.push_back(c);
                redo:
                for (auto& e : parsers) {
                    if(e)
                        if(e(state.buffer))
                        goto redo;
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