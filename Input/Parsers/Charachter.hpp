#pragma once
#include "Parser.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include "../../Events/KeyboardInput.hpp"


namespace NAMSP_NAME
{
    namespace Parsers
    {
        static Parser Characher = [](std::vector<char>& vec){
            if(vec.empty())
                return false;
            auto a = vec[0];
            if(a == '\e'){
                if(vec.size() < 2)
                    return false;
                if(vec[1] != '\e')
                    return false;
                
                auto it = vec.begin();
                std::advance(it, 1);
                vec.erase(vec.begin(), it);
            }
            else{
                vec.erase(vec.begin());
            }
            std::cout << "Char parser, got: " << a << std::endl;
            KeyboardInput::call(a);

            return true;
        };
    } // namespace Parsers
    
    

}