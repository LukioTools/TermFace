#pragma once
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <stdexcept>

#include "../NAMSP_NAME.hpp"
#include "../Data/Pixel.hpp"

namespace NAMSP_NAME
{
    struct ScreenElement
    {
        Pixel p;
        unsigned int z_index = 0;
        bool operator!=(const ScreenElement& e)const{
            return p != e.p;
        }
    };
    
    class ScreenBuffer
    {
    private:
        std::size_t allocn  = 0;
        std::size_t width   = 0;
        std::size_t height  = 0;
        std::unique_ptr<ScreenElement[]> ptr  = nullptr;

        inline bool need_to_realloc(std::size_t n_elements){
            if(allocn < n_elements || allocn/4 >= n_elements)
                return true;
            return false;
        }

    public:
        inline ScreenElement* get(){
            return ptr.get();
        }
        inline ScreenBuffer& clear(){
            memset(ptr.get(), 0, allocn*sizeof(ScreenElement));
            return *this;
        }
        inline ScreenBuffer& fill(const ScreenElement& e){
            for (auto& a : *this)
                a = e;
            return *this;
        }
        inline ScreenBuffer& fillall(const ScreenElement& e){
            for (size_t i = 0; i < allocn; i++)
                ptr.get()[i] = e;
            return *this;
        }

        inline ScreenBuffer& alloc(std::size_t n){
            if(need_to_realloc(n))
                ptr.reset(new ScreenElement[n]());
            return *this;
        }
        inline ScreenBuffer& alloc(std::size_t x, std::size_t y){
            return alloc(x*y);
        };
        inline std::size_t size(){
            return width*height;
        }
        inline ScreenElement& get(std::size_t index) const{
            if(index > width*height)
                throw std::out_of_range("ScreenBuffer::get::out of range");
            return ptr[index];
        }
        inline ScreenElement& get(std::size_t x, std::size_t y) const{
            return get(x+y*width);
        }

        struct _Row
        {
            std::size_t y = 0;
            ScreenBuffer& parent;

            ScreenElement& operator[](std::size_t x){
                return parent.get(x,y);
            }
        };

        struct _Colum
        {
            std::size_t x = 0;
            ScreenBuffer& parent;

            ScreenElement& operator[](std::size_t y){
                return parent.get(x,y);
            }
        };

        inline _Row Row(std::size_t y){
            return{
                y,
                *this
            };
        }

        inline _Colum Colum(std::size_t x){
            return{
                x,
                *this
            };
        }

        struct iterator
        {
            std::size_t offset = 0;
            ScreenBuffer& parent;

            std::size_t operator++(){
                return ++offset;
            }
            std::size_t operator++(int){
                return offset++;
            }
            ScreenElement& operator*(){
                return parent.get(offset);
            }
            bool operator!=(const iterator& it) const {
                return offset != it.offset;
            }
            bool operator==(const iterator& it) const {
                return offset == it.offset;
            }
            bool operator<(const iterator& it) const {
                return offset < it.offset;
            }
            bool operator<=(const iterator& it) const {
                return offset <= it.offset;
            }
            bool operator>(const iterator& it) const {
                return offset > it.offset;
            }
            bool operator>=(const iterator& it) const {
                return offset >= it.offset;
            }
        };

        inline iterator begin(){
            return {
                0,
                *this
            };
        }
        inline iterator end(){
            return {
                width*height,
                *this
            };
        }

        /*
            usage:
            auto it = sb.while();
            while(it){
                
                it++;
            }
            or 
            auto it = sb.while();
            while(it.inc()){

            }
        */
        struct while_iterator 
        {
            std::size_t offset = 0;
            ScreenBuffer& parent;

            bool inc(){
                offset++;
                return *this;
            }

            while_iterator& operator++(){
                ++offset;
                return * this;
            }
            while_iterator& operator++(int){
                offset++;
                return * this;
            }
            ScreenElement& operator*(){
                return parent.get(offset);
            }
            bool operator!=(const while_iterator& it)const{
                return offset != it.offset;
            }
            bool operator==(const while_iterator& it)const{
                return offset == it.offset;
            }
            bool operator<(const while_iterator& it)const{
                return offset < it.offset;
            }
            bool operator<=(const while_iterator& it)const{
                return offset <= it.offset;
            }
            bool operator>(const while_iterator& it)const{
                return offset > it.offset;
            }
            bool operator>=(const while_iterator& it)const{
                return offset >= it.offset;
            }
            operator bool()const{
                return offset < parent.size();
            }
        };

        while_iterator while_begin(){
            return {0, *this};
        }

        template<typename Fn>
        ScreenBuffer& difference(Fn fn, const ScreenBuffer& sb){
            auto hmin =     std::min(sb.height, height);
            auto wmin =     std::min(sb.width, width);
            for (size_t h = 0; h < hmin; h++)
            {
                for (size_t w = 0; w < wmin; w++)
                {
                    if(get(w,h) != sb.get(w,h))
                        fn(*this, sb, w, h);
                }
            }
            return *this;
        }
        
        
        


        ScreenBuffer(/* args */) {}
        ~ScreenBuffer() {}
    };
} // namespace NAMSP_NAME

