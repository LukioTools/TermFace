#define EventListenerDEBUG 1
#define EventListenerERRORS 1
#include <iostream>
#include "Init.hpp"
#include "Input/InputManager.hpp"

int main(int argc, char const *argv[])
{
    tui::InputManager man;
    tui::init(argc, argv);




    tui::deinit();
    return 0;
}
