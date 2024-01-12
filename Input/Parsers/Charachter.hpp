#include "Parser.hpp"
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
            if(vec.size() >= 2 && a == '\e'){
                if(vec[0] != '\e')
                    return false;
                
                auto it = vec.begin();
                std::advance(it, 1);
                vec.erase(vec.begin(), it);
            }
            else{
                vec.erase(vec.begin());
            }
            KeyboardInput::call(a);

            return true;
        };
    } // namespace Parsers
    
    

}