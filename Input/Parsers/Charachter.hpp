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
            KeyboardInputType k;
            if(vec.empty())
                return false;
            auto a = vec[0];
            k = a;
            if(a == '\e'){
                std::clog << "Escape\n";
                if(vec.size() < 2)
                    return false;
                if(vec[1] != '\e')
                    return false;
                
                auto it = vec.begin();
                std::advance(it, 1);
                vec.erase(vec.begin(), it);
            }
            else if(a & 0b10000000){
                std::clog << "Unicode\n";
                int n_extra_bytes = 0;
                int index = 1;
                while (a & (0b10000000 >> index++))
                    n_extra_bytes++;
                
                if(n_extra_bytes > 3)
                    throw std::runtime_error("Moar than 4");
                for (size_t i = 0; i < n_extra_bytes; i++)
                {
                    if(i+1 >= vec.size())
                        return false;
                    k += vec[i+1];
                }
                std::clog << "Success";
                vec.erase(vec.begin(), vec.begin()+n_extra_bytes+1);

            }
            else{
                std::clog << "Standard\n";
                vec.erase(vec.begin());
            }
            //std::cout << "Char parser, got: " << a << std::endl;
            KeyboardInput::call(k);

            return true;
        };
    } // namespace Parsers
    
    

}