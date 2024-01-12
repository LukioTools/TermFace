


#include <iostream>
int main(int argc, char const *argv[])
{
    int a = 0x04030201;
    auto p = reinterpret_cast<char*>(&a);
    std::cout << (int) p[0] << std::endl; // 1
    std::cout << (int) p[1] << std::endl; // 2
    std::cout << (int) p[2] << std::endl; // 3
    std::cout << (int) p[3] << std::endl; // 4

    return 0;
}
