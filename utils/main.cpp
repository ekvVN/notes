#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <string>
#include "val_container.h"
#include "TestVariadicTemplate.h"
#include <list>


template <typename T> std::string type_name();

int main()
{
    std::vector<double> vd{3.14, 8.1, 3.2, 1.0};
    print_container(vd);

    std::list<int> li{1, 2, 3, 5};
    print_container(li);


    CC::coder1 c1{10,20,30,40,50,60,70,80,64,128,255};
    CC::coder2 c2{0,0,0,0,0,0,0,0,0,0,0};
    auto pixCount = c1.size();
    encode(c1, c2, pixCount);

    auto srcType = std::make_shared<VideoTypeIr<6>>();
    auto dstType = std::make_shared<VideoTypeIr<4>>();
    CC::coder1 src1{10,20,30,40,50,60,70,80,64,128,255};
    CC::coder2 dst2{0,0,0,0,0,0,0,0,0,0,0};
    encode(src1, srcType.get(), dst2, dstType.get(), pixCount);

//    std::vector<bool> vec = {0xFF};
    std::cout << "Hello, World!" << std::endl;


    std::cout << "************* get **************" << std::endl;
    std::array<unsigned char, 3> arr =
            {
                    0x28,
                    0xE7,
                    0xFF
            };

    constexpr size_t bit_count = 6;
    using data_type = unsigned char;
    using value_type = unsigned char;
    val_container<bit_count, data_type, value_type> values(arr.data(), arr.size());

    for (auto it = values.begin(); it != values.end(); ++it)
    {
        unsigned int aa = *it;
        std::cout << std::hex << "0x" << aa << std::endl;
    }

    std::cout << "************* set **************" << std::endl;
    // Установка
    std::vector<unsigned char> vec = {
            0x0A,
            0x0E,
            0x1F,
            0x3F
    };

    std::vector<bool>aa {false, true, false};

    for (auto it = aa.begin(); it != aa.end(); ++it) {
        *it = !*it;
        std::cout << *it << std::endl;
    }

    std::cout << "aa[0] = " << aa[0] << std::endl;
    std::cout << "aa[1] = " << aa[1] << std::endl;
    std::cout << "aa[2] = " << aa[2] << std::endl;

    std::vector<int> aaa;
    std::array<unsigned char, 3> arr2;
    val_container<bit_count, data_type, value_type> values2(arr2.data(), arr2.size());

    auto val_it = values2.begin();
    for (auto it = vec.begin(); it != vec.end(); ++it, ++val_it) {
        *val_it = *it;
        auto a = (*val_it);

    }
    std::cout << "************* set2 **************" << std::endl;

    for (auto it = arr2.begin(); it != arr2.end(); ++it) {
        std::cout << std::hex << "0x" << (unsigned int)*it << std::endl;
    }

    return 0;
}