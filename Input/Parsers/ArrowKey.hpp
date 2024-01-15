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
            //std::clog << "VEC SIZE: " << vec.size() << std::endl;
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
            case '1':
                if(vec.size() < 6){
                    //std::clog << "if(vec.size() < 6){" << std::endl;
                    return false;
                }
                if(vec[3] != ';'){
                    //std::clog << "if(vec[3] != ';'){" << std::endl;
                    return false;
                }
                out.shift(vec[4] == '2');
                out.ctrl(vec[4] == '5');
                //char shift_ctrl = vec[4];
                out.dir(static_cast<Direction>(vec[5]-'A'));
                n_remove  = 6;
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