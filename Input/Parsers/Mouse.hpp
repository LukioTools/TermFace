#include "Parser.hpp"
#include <iterator>
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
                    m.x = std::stoi(action);
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
                        m.a.set(MouseInputType::UP, true);
                        break;
                    }
                    else if (vec[current_index] == 'm') {
                        m.a.set(MouseInputType::DOWN, true);
                        break;
                    }
                    else{
                        return false;
                    }
                }
                try {
                    m.y = std::stoi(action);
                } catch (...) {
                    return false;                    
                }
            }

            




            return false;
        };
    } // namespace Parsers
    
    

}