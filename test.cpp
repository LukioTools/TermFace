#include <chrono>
#include <ios>
#include <iostream>

#include <thread>
#include <unistd.h>
#include <termios.h>
static termios newt, oldt;
int main(int argc, char const *argv[])
{
        //termios
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    
    
    auto n = std::cin.get();
    std::cout << n << std::endl;


        //termios
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
