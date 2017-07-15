#include <iostream>
#include <array>
#include <map>
#include <vector>
#include <string>
#include "val_container.h"

template <typename T> std::string type_name();

int main()
{
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