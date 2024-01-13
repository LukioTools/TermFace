#define EventListenerDEBUG 1
#define EventListenerERRORS 1


#include "def.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <thread>

#include <iostream>
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "Events/MouseInput.hpp"
#include "Elements/Element.hpp"
#include "Elements/Body.hpp"
#include "Globals/ScreenBuffers.hpp"
#include "Shaders/flatshade.hpp"
#include "Screen/refreshScreenBuffers.hpp"
#include "Screen/refreshScreenSize.hpp"
#include "Events/ArrowInput.hpp"

using namespace::tui;



bool render_run = true;
void render_thread(){
    while (render_run)
    {
        refresh_screen_size();
        refresh_screen_buffers();
        render_buffer.fill({Pixel{
            {{0,0,0},{200,200,200}},
            ' ',
        }, 0});

        body.draw(render_buffer);



        display_buffer.difference([](ScreenBuffer& sba, const ScreenBuffer& sbb, size_t x, size_t y){
            //std::clog << "diff: " << x << '/' << y << std::endl;
            auto& a = sba.get(x,y);
            auto& b = sbb.get(x,y);
            a=b;
            mv(x, y) << b.p << attr_reset;
        }, render_buffer);
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
}

int main(int argc, char const *argv[])
{
    init(argc, argv);
    try
    {
        InputManager man;
        std::clog << "WIDTH: " << WIDTH << std::endl;
        std::clog << "HEIGHT: " << HEIGHT << std::endl;
        std::thread rthr(render_thread);
        auto e = new Element;
        e->color({{255,0,0},{255,255,255}});
        e->width(100.);
        e->st_width(SizeType::SCR);
        e->height(5);

        body.child(std::unique_ptr<ElementAbstract>(e));        
        body.color({{255,0,255},{255,255,255}});

        class SomeThing : MouseInput, KeyboardInput, ArrowInput
        {
        public:
            volatile bool run = true;
            Element* e;
            void event(Direction d) override{
                if(d == Direction::RIGHT)
                    e->posx(e->posx()+1);
            }
            void event(KeyboardInputType c) override{
                if(c == 1 || c == 4)
                    run = false;
                if(c == 'd')
                    e->posx(e->abs_posx()+1);
                if(c == 'a')
                    e->posx(e->abs_posx()-1);
                
                auto l = e->wh();
                auto p = e->pos();
                auto drawable = e->clamp(render_buffer, l.x, l.y, p.x, p.y);

                std::clog << "drawable: " << (drawable ? "true" : "false")<< "\t" << l.x << " : " << l.y << " / " << p.x << " : " << p.y << std::endl;
            }
            void event(MouseInputType a) override{
            }
            SomeThing(Element* e) : e(e) {}
            ~SomeThing() {}
        } elem(e);

        

        while (elem.run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        render_run = false;
        rthr.join();
    }
    catch(const std::out_of_range& out_of_range){
        render_run = false;
        std::clog << out_of_range.what() << std::endl;
    }
    deinit();
    return 0;
}
