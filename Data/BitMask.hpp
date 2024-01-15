#pragma once
#include <bitset>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <ostream>


template<size_t ByteSize>
struct BitMask
{
    static_assert(ByteSize > 0, "ByteSize must be greater than 0");

    unsigned char mask[ByteSize] = {0};

    inline void clear(){
        for (size_t i = 0; i < ByteSize; i++)
        {
            mask[ByteSize] = 0;
        }
    }

    inline constexpr size_t nbits() const noexcept {
        return ByteSize * sizeof(unsigned char) * 8;
    }

    inline constexpr size_t nbytes() const noexcept {
        return ByteSize * sizeof(unsigned char);
    }
    inline unsigned char getByte(size_t i) const{
        return mask[i/8]; // c++11 says it is always rounded down
    }

    inline unsigned char& getByteRef(size_t i) {
        return mask[i/8]; // c++11 says it is always rounded down
    }

    inline void set(size_t i, bool on){
        if(i >= nbits())
            return;
        
        unsigned char& m = getByteRef(i);
        if(on){
            m = m | (1 << i%8);
        }
        else{
            m = m & ~(1 << i%8);
        }
    }

    bool get(size_t i) const {
        if(i >= nbits())
            return false;

        auto m = getByte(i);
        return m & (1 << i%8);
    }

    BitMask(){}
    BitMask(std::initializer_list<size_t> l){
        for (auto& e : l)
        {
            set(e, true);
        }
    }


};
template<size_t sz, typename type>
struct TypedBitMask : public BitMask<sz>
{
    inline void set(type i, bool on){
        if(i >= this->nbits())
            return;
        
        auto& m = this->getByteRef(i);
        if(on){
            m = m | (1 << i%8);
        }
        else{
            m = m & ~(1 << i%8);
        }
    }

    bool get(type i) const {
        if(i >= this->nbits())
            return false;

        auto m = this->getByte(i);
        return m & (1 << i%8);
    }
};

