#pragma once
#include "Parser.hpp"
#include <string>
#include <vector>
#include "../../Events/MouseInput.hpp"



namespace NAMSP_NAME
{
    namespace Parsers
    {
        static Parser Mouse = [](std::vector<char>& vec){
            MouseInputType m;
            if(vec.size() < 9)
                return false;

            if(vec[0] != '\e')
                return false;
            if(vec[1] != '[')
                return false;
            if(vec[2] != '<')
                return false;

            int current_index = 2;
            int iaction = -1; //parse this shit later
            {
                std::string action;
                while (true) {
                    current_index++;
                    if(vec.size() <= current_index)
                        return false;
                    if(vec[current_index] >= '0' && vec[current_index] <= '9'){
                        action+=vec[current_index];
                    }
                    else if (vec[current_index] == ';') {
                        break;
                    }
                    else{
                        return false;
                    }
                }
                try {
                    iaction = std::stoi(action);
                } catch (...) {
                    return false;                    
                }
            }

            {
                std::string action;
                while (true) {
                    current_index++;
                    if(vec.size() <= current_index)
                        return false;
                    if(vec[current_index] >= '0' && vec[current_index] <= '9'){
                        action+=vec[current_index];
                    }
                    else if (vec[current_index] == ';') {
                        break;
                    }
                    else{
                        return false;
                    }
                }
                try {
                    m.x = std::stoi(action)-1;
                } catch (...) {
                    return false;                    
                }
            }

            {   //this reads till M or m
                std::string action;
                while (true) {
                    current_index++;
                    if(vec.size() <= current_index)
                        return false;
                    if(vec[current_index] >= '0' && vec[current_index] <= '9'){
                        action+=vec[current_index];
                    }
                    else if (vec[current_index] == 'M') {
                        m.a.set(MouseInputType::DOWN, true);
                        break;
                    }
                    else if (vec[current_index] == 'm') {
                        m.a.set(MouseInputType::UP, true);
                        break;
                    }
                    else{
                        return false;
                    }
                }
                try {
                    m.y = std::stoi(action)-1;
                } catch (...) {
                    return false;                    
                }
            }

            {
                //parse iaction
                char btn = iaction & 0b11;//take first 2 bits
                if(btn == 0)
                    m.a.set(MouseInputType::LEFT, true);
                if(btn == 1)
                    m.a.set(MouseInputType::CENTER, true);
                if(btn == 2)
                    m.a.set(MouseInputType::RIGHT, true);
                
                m.a.set(MouseInputType::ALT, iaction & 0b1000);
                m.a.set(MouseInputType::CTRL, iaction & 0b10000);
                //std::cout << "iaction: " << iaction << std::endl;
                m.a.set(MouseInputType::HILIGHT, iaction & 0b100000);
                if((iaction & 0x23) == 0x23){
                    m.a.set(MouseInputType::HOVER, true);
                }
                if((iaction & 64) == 64){
                    bool down = iaction & 0b1;
                    m.a.set(MouseInputType::SCROLL, true);
                    m.a.set(MouseInputType::DOWN, down);
                    m.a.set(MouseInputType::UP, !down);
                }
            }

            MouseInput::call(m);

            current_index++;
            auto it = vec.begin();
            std::advance(it, current_index);
            vec.erase(vec.begin(), it);
            return true;
        };
    } // namespace Parsers
    
    

}