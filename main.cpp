#include "def.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <thread>
#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#include <iostream>
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "Events/MouseInput.hpp"
#include "Elements/Element.hpp"
#include "Globals/ScreenBuffers.hpp"
#include "Shaders/flatshade.hpp"
#include "Screen/refreshScreenBuffers.hpp"
#include "Screen/refreshScreenSize.hpp"

using namespace::tui;


class SomeThing : MouseInput, KeyboardInput, ArrowInput
{
private:
public:
    volatile bool run = true;
    void event(Direction d) override{

    }
    void event(KeyboardInputType c) override{
        if(c == 1 || c == 4)
            run = false;
    }
    void event(MouseInputType a) override{
        //std::cout << "Got mouse event!!" << std::endl;
        //std::cout << "x: " << a.x << std::endl;
        //std::cout << "y: " << a.y << std::endl;
        //std::cout << "LEFT: " <<    (a.a.get(MouseInputType::LEFT) ? "true" : "false")   << '\n';
        //std::cout << "RIGHT: " <<   (a.a.get(MouseInputType::RIGHT) ? "true" : "false")  << '\n';
        //std::cout << "CENTER: " <<  (a.a.get(MouseInputType::CENTER) ? "true" : "false") << '\n';
        //std::cout << "HILIGHT: " << (a.a.get(MouseInputType::HILIGHT) ? "true" : "false")<< '\n';
        //std::cout << "HOVER: " <<   (a.a.get(MouseInputType::HOVER) ? "true" : "false")  << '\n';
        //std::cout << "SCROLL: " <<  (a.a.get(MouseInputType::SCROLL) ? "true" : "false") << '\n';
        //std::cout << "DOWN: " <<    (a.a.get(MouseInputType::DOWN) ? "true" : "false")   << '\n';
        //std::cout << "UP: " <<      (a.a.get(MouseInputType::UP) ? "true" : "false")     << '\n';
        //std::cout << "CTRL: " <<    (a.a.get(MouseInputType::CTRL) ? "true" : "false")   << '\n';
        //std::cout << "ALT: " <<     (a.a.get(MouseInputType::ALT) ? "true" : "false")    << '\n';
    }
    SomeThing(/* args */) {}
    ~SomeThing() {}
} elem;

int main(int argc, char const *argv[])
{
    init(argc, argv);
    {
        InputManager man;
        refresh_screen_size();
        std::clog << "WIDTH: " << WIDTH << std::endl;
        std::clog << "HEIGHT: " << HEIGHT << std::endl;
        refresh_screen_buffers();
        render_buffer.alloc(WIDTH,HEIGHT);
        display_buffer.alloc(WIDTH,HEIGHT);
        render_buffer.fill({Pixel{
            {{0,0,0},{200,200,200}},
            ' ',
        }, 0});

        body.draw(render_buffer);


        display_buffer.difference([](ScreenBuffer& sba, const ScreenBuffer& sbb, size_t x, size_t y){
            auto& a = sba.get(x,y);
            auto& b = sbb.get(x,y);
            a=b;
            mv(x, y) << b.p << attr_reset;
        }, render_buffer);
        std::cout.flush();

        while (elem.run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    deinit();
    return 0;
}
