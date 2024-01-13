#include "../NAMSP_NAME.hpp"
#include "../Screen/ScreenBuffer.hpp"
#include <cstddef>
#include <iostream>


namespace NAMSP_NAME
{
    inline static void flatshade(ScreenElement& a, const ScreenElement& b){
        a = b;
    }
        //for simple 2d applications
    inline static void flatrender(ScreenBuffer& sba, const ScreenBuffer& sbb, std::size_t x, std::size_t y){
        auto& a =sba.get(x,y);
        auto& b = sbb.get(x,y);
        if(b.z_index < a.z_index)
            return;
        a = b;
        mv(x, y) << b.p;
    }
}