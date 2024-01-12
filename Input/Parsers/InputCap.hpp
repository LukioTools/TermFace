#pragma once
#include "Parser.hpp"
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
            return false;
        };
    } // namespace Parsers
    

}