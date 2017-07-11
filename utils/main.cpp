#include <iostream>
#include "offset_of.h"

struct A
{
    int a;
    int b;
//private:
    int c;
};

int main()
{
    std::cout << offset_of(&A::b) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}