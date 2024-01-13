#include <chrono>
#include <ios>
#include <iostream>

#include <fcntl.h>
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

        //fcntl
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    int n;  // get a char non blocking
    while (true) {
        n = std::cin.get();
        if(n == -1){
            std::cin.clear();
        }
        else
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::cout << n << std::endl;


        //fcntl
    fcntl(STDIN_FILENO, F_SETFL, flags);
        //termios
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
