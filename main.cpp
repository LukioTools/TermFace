#include "def.hpp"
#include <chrono>
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
        render_buffer.alloc(WIDTH,HEIGHT);
        display_buffer.alloc(WIDTH,HEIGHT);
        InputManager man;
        auto e = new Element;
        e->color({{255,0,255},{255,255,255}});
        tui::body.child(std::unique_ptr<ElementAbstract>(e));

        std::clog << "Drawing" << std::endl;
        body.draw(render_buffer);

        std::clog << "Rendering" << std::endl;
        display_buffer.difference([](ScreenBuffer & sba, const ScreenBuffer & sbb, std::size_t x, std::size_t y ){
            std::clog << "Difference: " << x << " : " << y << std::endl;
            mv(x, y) << sba.get(x,y).p;
        }, render_buffer);
        std::clog << "Rendered" << std::endl;


        while (elem.run) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    deinit();
    return 0;
}
