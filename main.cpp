#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#include <iostream>
#include "Init.hpp"
#include "Input/InputManager.hpp"
#include "Events/MouseInput.hpp"


using namespace::tui;

class SomeThing : MouseInput
{
private:
public:
    void event(MouseInputType a) override{
        std::cout << "Got mouse event!!" << std::endl;
    }
    SomeThing(/* args */) {}
    ~SomeThing() {}
};


int main(int argc, char const *argv[])
{
    InputManager man;
    init(argc, argv);


    while (true) {
        
    }


    deinit();
    return 0;
}
