#include "test1.h"
#include "test2.h"
//#include "test3.h"
#include "test4.h"
#include "test5.h"
#include "test6.h"

int main()
{
    test1::run::main();
    test2::run::main();
//    test3::run::main();
    test4::run::main();
    test5::run::main();
    test6::run::main();

    std::cout << "end" << std::endl;
    return 0;
}