#pragma once
#include <sstream>
#include "BitMask.hpp"
#include "../def.hpp"
#include "../NAMSP_NAME.hpp"


namespace NAMSP_NAME{
    class Attribute
    {
    public:
        enum Attributes{
            BOLD,
            DIM,
            ITALIC,
            UNDERLINE,
            STRIKETROUGH,
            BLINK,
            REVERSE_COLOR,
            HIDDEN,
        }; //perfectly fits all the shits

        BitMask<1> bm;

        inline void set(Attributes a, bool on){
            bm.set(a, on);
        }
        inline bool get(Attributes a) const{
            return bm.get(a);
        }

        inline std::string str() const {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& os, const Attribute& a){
            if (a.get(BOLD)) {
                os << bold;
            }
            if(a.get(DIM)){
                os << dim;
            }
            if(a.get(ITALIC)){
                os << italic;
            }
            if(a.get(UNDERLINE)){
                os << underline;
            }
            if(a.get(STRIKETROUGH)){
                os << strike;
            }
            if(a.get(BLINK)){
                os << blink;
            }
            if(a.get(REVERSE_COLOR)){
                os << reverse_str;
            }
            if(a.get(HIDDEN)){
                os << hidden;
            }
            return os;
        }

        bool operator==(const BitMask<1>& b) const {
            return bm.mask[0] == b.mask[0];
        }
        bool operator!=(const BitMask<1>& b) const {
            return bm.mask[0] != b.mask[0];
        }

        bool operator==(const Attribute& a) const {
            return bm.mask[0] == a.bm.mask[0];
        }
        bool operator!=(const Attribute& a) const {
            return bm.mask[0] != a.bm.mask[0];
        }

        Attribute(/* args */) {}
        ~Attribute() {}
    };
}