#pragma once
#include "../NAMSP_NAME.hpp"
#include "../Data/Pixel.hpp"
#include "../Globals/ScreenSize.hpp"
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace NAMSP_NAME
{
    struct ScreenElement
    {
        Pixel p;
        unsigned int z_index = 0;
    };
    
    class ScreenBuffer
    {
    private:
        std::size_t allocm  = 0;
        std::size_t width   = 0;
        std::size_t height  = 0;
        std::unique_ptr<ScreenElement[]> ptr  = nullptr;

        inline bool need_to_realloc(std::size_t n_elements){
            if(allocm < n_elements || allocm/4 >= n_elements)
                return true;
            return false;
        }

    public:
        inline void alloc(std::size_t n){
            if(need_to_realloc(n))
                ptr.reset(new ScreenElement[n]());
        }
        inline void alloc(std::size_t x, std::size_t y){
            alloc(x*y);
        };
        inline std::size_t size(){
            return width*height;
        }
        inline ScreenElement& get(std::size_t index){
            if(index > width*height)
                throw std::out_of_range("ScreenBuffer::get::out of range");
            return ptr[index];
        }
        inline ScreenElement& get(std::size_t x, std::size_t y){
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
            bool operator!=(const iterator& it){
                return offset != it.offset;
            }
            bool operator==(const iterator& it){
                return offset == it.offset;
            }
            bool operator<(const iterator& it){
                return offset < it.offset;
            }
            bool operator<=(const iterator& it){
                return offset <= it.offset;
            }
            bool operator>(const iterator& it){
                return offset > it.offset;
            }
            bool operator>=(const iterator& it){
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
            or
            while(it++){
                
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

            std::size_t operator++(){
                return ++offset;
            }
            std::size_t operator++(int){
                return offset++;
            }
            ScreenElement& operator*(){
                return parent.get(offset);
            }
            bool operator!=(const while_iterator& it){
                return offset != it.offset;
            }
            bool operator==(const while_iterator& it){
                return offset == it.offset;
            }
            bool operator<(const while_iterator& it){
                return offset < it.offset;
            }
            bool operator<=(const while_iterator& it){
                return offset <= it.offset;
            }
            bool operator>(const while_iterator& it){
                return offset > it.offset;
            }
            bool operator>=(const while_iterator& it){
                return offset >= it.offset;
            }
            operator bool(){
                return offset < parent.size();
            }
        };
        
        
        


        ScreenBuffer(/* args */) {}
        ~ScreenBuffer() {}
    };
} // namespace NAMSP_NAME

