#pragma once
#include "Parser.hpp"
#include <iterator>
#include <vector>
#include "../../Events/ArrowInput.hpp"


namespace NAMSP_NAME
{
    namespace Parsers
    {
        static Parser ArrowKey = [](std::vector<char>& vec){
            if(vec.size() < 3)
                return false;
            if(vec[0] != '\e')
                return false;
            if(vec[1] != '[')
                return false;
            switch (vec[2])
            { 
            case 'A':
                ArrowInput::call(Direction::UP);
                break;
            case 'B':
                ArrowInput::call(Direction::DOWN);
                break;
            case 'C':
                ArrowInput::call(Direction::RIGHT);
                break;
            case 'D':
                ArrowInput::call(Direction::LEFT);
                break;
            default:
                return false;
            }
            auto it = vec.begin();
            std::advance(it, 3);
            vec.erase(vec.begin(), it);
            return true;
        };
    } // namespace Parsers
    
    

}