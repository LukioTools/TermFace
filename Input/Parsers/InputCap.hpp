#pragma once
#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include <vector>

#if !defined(INPUT_CAP_MAX)
#define INPUT_CAP_MAX 16
#endif // INPUT_CAP_MAX


namespace NAMSP_NAME
{
    namespace Parsers
    {
        static Parser InputCap = [](std::vector<char>& vec){
            
            if(vec.size() > INPUT_CAP_MAX)
                vec.erase(vec.begin());
            if(vec.empty())
                return false;
                //clearing esc sequences
            if(vec[0] == '\e'){
                if(vec.size() < 2){
                    //std::clog << "VEC 2 SMOL\n";
                    return false;
                }
                if(vec[1] != '['){
                    //std::cout << "Was not!\n";
                    vec.clear();
                    return false;
                }
                else{
                    if(vec.size() < 3)
                        return false;
                    if(vec[2] == '<' || (vec[2] >= 'A' && vec[2] <= 'D'))
                        return false;
                    else{
                        //std::cout << "clear: " << vec[2] << "\n";
                        vec.clear();
                    }
                }
            }

            return false;
        };
    } // namespace Parsers
    

}