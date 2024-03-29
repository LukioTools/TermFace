#include "Elements/TextField.hpp"
#include <cstdio>
#include <ostream>
#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#define DEBUG 1

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
    refresh_screen_size();
    refresh_screen_buffers();
    while (render_run)
    {
        refresh_screen_size();
        refresh_screen_buffers();
        //render_buffer.fill({Pixel{
        //    {{0,0,0},{200,200,200}},
        //    ' ',
        //}, 0});

        body.draw(render_buffer);

        display_buffer.difference([](ScreenBuffer& sba, const ScreenBuffer& sbb, size_t x, size_t y){
            auto& a = sba.get(x,y);
            auto& b = sbb.get(x,y);
            a=b;
            mv(x, y) << b.p << attr_reset;
        }, render_buffer);

        std::cout.flush();
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
        auto e = new TextField;
        e->colornormal({{255,0,0},{255,255,255}});
        e->colorhover({{0,255,0},{255,255,255}});
        e->coloractive({{0,0,255},{255,255,255}});
        e->width(100.);
        e->st_width(SizeType::SCR);
        e->height(5);
        e->text(std::string("Write here: "));


        body.child(std::unique_ptr<ElementAbstract>(e));        
        body.colornormal({{255,0,255},{255,255,255}});
        
        bool run = true;
        KeyboardInputLambda lambda([&](KeyboardInputType c){
                if(c == 1 || c == 4)
                    run = false;
                
                if(e->active())
                    return;
                if(c == 'd')
                    e->posx(e->abs_posx()+1);
                if(c == 'a')
                    e->posx(e->abs_posx()-1);
                if(c == 'w')
                    e->posy(e->abs_posy()-1);
                if(c == 's')
                    e->posy(e->abs_posy()+1);

                std::clog << "Got:: " << c << std::endl;
                auto l = e->wh();
                auto p = e->pos();
                auto drawable = e->clamp(render_buffer, l.x, l.y, p.x, p.y);
                std::clog << "drawable: " << (drawable ? "true" : "false")<< "\t" << l.x << " : " << l.y << " / " << p.x << " : " << p.y << std::endl;
        });

        MouseInputLambda mlambda([&](MouseInputType m){
            if(m.a.get(MouseInputType::LEFT) && m.a.get(MouseInputType::DOWN) && !m.a.get(MouseInputType::HILIGHT)){
                auto a  = render_buffer.get(m.x, m.y);
                auto b  = display_buffer.get(m.x, m.y);
                std::clog << "a!=b: " << ( a!=b ? "true" : "false") << std::endl;
                std::clog << "a.p.ch: '" << a.p.ch.getInt() << "' (aka: '" << a.p.ch << "')" <<    std::endl;
                std::clog << "b.p.ch: '" << b.p.ch.getInt() << "' (aka: '" << b.p.ch << "')" <<    std::endl;
            }
        });

        while (run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        render_run = false;
        rthr.join();
    }
    catch(const std::out_of_range& out_of_range){
        render_run = false;
        std::cerr <<attr_reset << color_fg(255,0,0) <<out_of_range.what() << attr_reset << std::endl;
    }
    deinit();
    return 0;
}
