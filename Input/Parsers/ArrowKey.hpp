#pragma once
#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include "../../Events/ArrowInput.hpp"


namespace NAMSP_NAME
{
    namespace Parsers
    {
        static Parser ArrowKey = [](std::vector<char>& vec){
            ArrowInputType out;
            int n_remove = 3;
            if(vec.size() < 3)
                return false;
            if(vec[0] != '\e')
                return false;
            if(vec[1] != '[')
                return false;
            switch (vec[2])
            { 
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                out.dir(static_cast<Direction>(vec[2]-'A'));
                n_remove  = 3;
                break;
            default:
                return false;
            }
            
            ArrowInput::call(out);
            vec.erase(vec.begin(), vec.begin()+n_remove);
            return true;
        };
    } // namespace Parsers
    
    

}