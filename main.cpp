#include <chrono>
#include <thread>
#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#include <iostream>
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "Events/MouseInput.hpp"


using namespace::tui;




int main(int argc, char const *argv[])
{
    init(argc, argv);
    {
        InputManager man;
        
        class SomeThing : MouseInput, KeyboardInput
        {
        private:
        public:
            volatile bool run = true;
            void event(KeyboardInputType c) override{
                if(c == 1 || c == 4)
                    run = false;
            }
            void event(MouseInputType a) override{
                std::cout << "Got mouse event!!" << std::endl;
                std::cout << "x: " << a.x << std::endl;
                std::cout << "y: " << a.y << std::endl;
                std::cout << "LEFT: " <<    (a.a.get(MouseInputType::LEFT) ? "true" : "false")   << '\n';
                std::cout << "RIGHT: " <<   (a.a.get(MouseInputType::RIGHT) ? "true" : "false")  << '\n';
                std::cout << "CENTER: " <<  (a.a.get(MouseInputType::CENTER) ? "true" : "false") << '\n';
                std::cout << "HILIGHT: " << (a.a.get(MouseInputType::HILIGHT) ? "true" : "false")<< '\n';
                std::cout << "HOVER: " <<   (a.a.get(MouseInputType::HOVER) ? "true" : "false")  << '\n';
                std::cout << "SCROLL: " <<  (a.a.get(MouseInputType::SCROLL) ? "true" : "false") << '\n';
                std::cout << "DOWN: " <<    (a.a.get(MouseInputType::DOWN) ? "true" : "false")   << '\n';
                std::cout << "UP: " <<      (a.a.get(MouseInputType::UP) ? "true" : "false")     << '\n';
                std::cout << "CTRL: " <<    (a.a.get(MouseInputType::CTRL) ? "true" : "false")   << '\n';
                std::cout << "ALT: " <<     (a.a.get(MouseInputType::ALT) ? "true" : "false")    << '\n';
            }
            SomeThing(/* args */) {}
            ~SomeThing() {}
        } elem;
        while (elem.run) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    deinit();
    return 0;
}
