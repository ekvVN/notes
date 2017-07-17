#include <gtest/gtest.h>
#include "../val_container.h"

/**
 * Пример:
 * std::array<unsigned char, 6> arr = {
 *  0x28, // '0010 1000'
 *  0xE7, // '1110 0111'
 *  0xFF, // '1111 1111'
 *  0xAB, // '1010 1011'
 *  0xCD, // '1100 1101'
 *  0xEF, // '1110 1111'
 *  };
 *
 * val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());
 * values[0] == 0x0A    // '00 1010'
 * values[1] == 0x0E    // '00 1110'
 * values[2] == 0x1F    // '01 1111'
 * values[3] == 0x3F    // '11 1111'
 * values[4] == 0x2A    // '10 1010'
 * values[5] == 0x3C    // '11 1100'
 * values[6] == 0x37    // '11 0111'
 * values[7] == 0x2F    // '10 1111'
 *
 *  в 6 байт умещается 8 элементов по 6 бит
 *  '0x28     '_'0xE7     '_'0xFF     '_____'0xAB     '_'0xCD     '_'0xEF     '
 *  '0010 1000'_'1110 0111'_'1111 1111'_____'1010 1011'_'1100 1101'_'1110 1111'
 *
 *  '0x0A   '_'0x0E   '_'0x1F   '_'0x3F   '_'0x2A   '_'0x3C   '_'0x37   '_'0x2F   '
 *  '00 1010'_'00 1110'_'01 1111'_'11 1111'_'10 1010'_'11 1100'_'11 0111'_'10 1111'
 */

TEST(val_help, BitCount_1)
{
    using h = val_help<1, unsigned char, unsigned char>;
    h::init();

    EXPECT_EQ(8, h::vals_count_in_block);
    EXPECT_EQ(1, h::bytes_count_in_block);
    EXPECT_EQ(0x1, h::max_value);
}

TEST(val_help, BitCount_2)
{
    using h = val_help<2, unsigned char, unsigned char>;
    h::init();

    EXPECT_EQ(4, h::vals_count_in_block);
    EXPECT_EQ(1, h::bytes_count_in_block);
    EXPECT_EQ(0x3, h::max_value);
}

TEST(val_help, BitCount_4)
{
    using h = val_help<4, unsigned char, unsigned char>;
    h::init();

    EXPECT_EQ(2, h::vals_count_in_block);
    EXPECT_EQ(1, h::bytes_count_in_block);
    EXPECT_EQ(0xF, h::max_value);
}

TEST(val_help, BitCount_6)
{
    using h = val_help<6, unsigned char, unsigned char>;
    h::init();

    EXPECT_EQ(4, h::vals_count_in_block);
    EXPECT_EQ(3, h::bytes_count_in_block);
    EXPECT_EQ(0x3F, h::max_value);
}

TEST(val_help, BitCount_8)
{
    using h = val_help<8, unsigned char, unsigned char>;
    h::init();

    EXPECT_EQ(1, h::vals_count_in_block);
    EXPECT_EQ(1, h::bytes_count_in_block);
    EXPECT_EQ(0xFF, h::max_value);
}

TEST(val_help, BitCount_10)
{
    using h = val_help<10, unsigned char, unsigned short>;
    h::init();

    EXPECT_EQ(4, h::vals_count_in_block);
    EXPECT_EQ(5, h::bytes_count_in_block);
    EXPECT_EQ(0x3FF, h::max_value);
}

TEST(val_help, BitCount_12)
{
    using h = val_help<12, unsigned char, unsigned short>;
    h::init();

    EXPECT_EQ(2, h::vals_count_in_block);
    EXPECT_EQ(3, h::bytes_count_in_block);
    EXPECT_EQ(0xFFF, h::max_value);
}

TEST(val_help, BitCount_14)
{
    using h = val_help<14, unsigned char, unsigned short>;
    h::init();

    EXPECT_EQ(4, h::vals_count_in_block);
    EXPECT_EQ(7, h::bytes_count_in_block);
    EXPECT_EQ(0x3FFF, h::max_value);
}

TEST(val_help, BitCount_16)
{
    using h = val_help<16, unsigned char, unsigned short>;
    h::init();

    EXPECT_EQ(1, h::vals_count_in_block);
    EXPECT_EQ(2, h::bytes_count_in_block);
    EXPECT_EQ(0xFFFF, h::max_value);
}
TEST(val_iterator, operator_assign)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    auto it2 = it;

    EXPECT_EQ(values[0], *it2);
    ++it;
    EXPECT_EQ(values[0], *it2);
}

TEST(val_iterator, operator_asterisk)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    EXPECT_EQ(0xA, *it++);
    EXPECT_EQ(0xE, *it++);
    EXPECT_EQ(0x1F, *it++);
    EXPECT_EQ(0x3F, *it++);

    EXPECT_EQ(0x2A, *it++);
    EXPECT_EQ(0x3C, *it++);
    EXPECT_EQ(0x37, *it++);
    EXPECT_EQ(0x2F, *it++);
}

TEST(val_iterator, operator_braces)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    EXPECT_EQ(0xA, values[0]);
    EXPECT_EQ(0xE, values[1]);
    EXPECT_EQ(0x1F, values[2]);
    EXPECT_EQ(0x3F, values[3]);

    EXPECT_EQ(0x2A, values[4]);
    EXPECT_EQ(0x3C, values[5]);
    EXPECT_EQ(0x37, values[6]);
    EXPECT_EQ(0x2F, values[7]);

    auto it = values.begin();
    EXPECT_EQ(0xA, it[0]);
    EXPECT_EQ(0xE, it[1]);
    EXPECT_EQ(0x1F, it[2]);
    EXPECT_EQ(0x3F, it[3]);

    EXPECT_EQ(0x2A, it[4]);
    EXPECT_EQ(0x3C, it[5]);
    EXPECT_EQ(0x37, it[6]);
    EXPECT_EQ(0x2F, it[7]);
}

TEST(val_iterator, operator_prefix_increment)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    EXPECT_EQ(values[1], *(++it));
    EXPECT_EQ(values[2], *(++it));
    EXPECT_EQ(values[4], *(++++it));
}

TEST(val_iterator, operator_prefix_decrement)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    EXPECT_EQ(values[7], *--it);
    EXPECT_EQ(values[6], *--it);
    EXPECT_EQ(values[4], *----it);
}

TEST(val_iterator, operator_postfix_increment)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    EXPECT_EQ(values.begin(), it++);
    EXPECT_EQ(values[1], *it++);
    EXPECT_EQ(values[2], *it++);
    EXPECT_EQ(values[3], *it++++);
}

TEST(val_iterator, operator_postfix_decrement)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    EXPECT_EQ(values.end(), it--);
    EXPECT_EQ(values[7], *it--);
    EXPECT_EQ(values[6], *it--);
    EXPECT_EQ(values[5], *it----);
}

TEST(val_iterator, operator_plus_assign_n)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    EXPECT_EQ(values[0], *it);
    it += 3;
    EXPECT_EQ(values[3], *it);
    it += 4;
    EXPECT_EQ(values[7], *it);
}

TEST(val_iterator, operator_plus_n)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    EXPECT_EQ(values[0], *it);
    it = it + 3;
    EXPECT_EQ(values[3], *it);
    it = it + 4;
    EXPECT_EQ(values[7], *it);
}

TEST(val_iterator, operator_minus_assign_n)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    it -= 1;
    EXPECT_EQ(values[7], *it);
    it -= 3;
    EXPECT_EQ(values[4], *it);
    it -= 4;
    EXPECT_EQ(values[0], *it);

    it = values.end();
    it -= 6;
    EXPECT_EQ(values[2], *it);
}

TEST(val_iterator, operator_minus_n)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    it = it - 1;
    EXPECT_EQ(values[7], *it);
    it = it - 3;
    EXPECT_EQ(values[4], *it);
    it = it - 4;
    EXPECT_EQ(values[0], *it);

    it = values.end();
    it = it - 6;
    EXPECT_EQ(values[2], *it);
}

TEST(val_iterator, operator_eq)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    it += 8;
    auto endIt = values.end();

    EXPECT_TRUE(it == endIt);
}

TEST(val_iterator, operator_less)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    auto it2 = it;

    EXPECT_FALSE(it < it2);
    EXPECT_TRUE(it < ++it2);
}

TEST(val_iterator, operator_less_eq)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.begin();
    auto it2 = it;

    EXPECT_TRUE(it <= it2);
    EXPECT_TRUE(it <= ++it2);
}

TEST(val_iterator, operator_greater)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    auto it2 = it;

    EXPECT_FALSE(it > it2);
    EXPECT_TRUE(it > --it2);
}

TEST(val_iterator, operator_greater_eq)
{
    std::array<unsigned char, 6> arr = {0x28, 0xE7, 0xFF, 0xAB, 0xCD, 0xEF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto it = values.end();
    auto it2 = it;

    EXPECT_TRUE(it >= it2);
    EXPECT_TRUE(it >= --it2);
}

TEST(val_container, empty)
{
    val_container<6, unsigned char, unsigned char> values;
    EXPECT_TRUE(values.empty());
}

TEST(val_container, not_empty)
{
    std::array<unsigned char, 3> arr = {0x28, 0xE7, 0xFF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());
    EXPECT_FALSE(values.empty());
}

TEST(val_container, get)
{
    std::array<unsigned char, 3> arr = {0x28, 0xE7, 0xFF};
    val_container<6, unsigned char, unsigned char> values(arr.data(), arr.size());

    EXPECT_EQ(0xA, values[0]);
    EXPECT_EQ(0xE, values[1]);
    EXPECT_EQ(0x1F, values[2]);
    EXPECT_EQ(0x3F, values[3]);
}

TEST(val_container, set)
{
    std::array<unsigned char, 3> arr;
    val_container<6, unsigned char, unsigned char> values2(arr.data(), arr.size());

    std::vector<unsigned char> vec = {0x0A, 0x0E, 0x1F, 0x3F};
    auto val_it = values2.begin();
    for (auto it = vec.begin(); it != vec.end(); ++it, ++val_it)
        *val_it = *it;

    EXPECT_EQ(0x28, arr[0]);
    EXPECT_EQ(0xE7, arr[1]);
    EXPECT_EQ(0xFF, arr[2]);
}

//TEST(val_container, unsigned_short)
//{
//    std::vector<unsigned short> vec = { 0x3FF, 0x1FF, 0x1FC, 0x19C};
//    std::array<unsigned char, 4 * 2> arr;
//    memcpy(arr.data(), vec.data(), arr.size());
//
//    val_container<16, unsigned char, unsigned short> values(arr.data(), arr.size());
//
//    EXPECT_EQ(vec[0], (unsigned short)values[0]);
//    EXPECT_EQ(vec[1], (unsigned short)values[1]);
//    EXPECT_EQ(vec[2], (unsigned short)values[2]);
//    EXPECT_EQ(vec[3], (unsigned short)values[3]);
//}

TEST(val_container, fiil_bit1)
{
    constexpr size_t bits = 1;
    std::array<unsigned char, 80> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x1, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit2)
{
    constexpr size_t bits = 2;
    std::array<unsigned char, 80> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x3, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit3)
{
    constexpr size_t bits = 3;
    std::array<unsigned char, 60> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x7, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit4)
{
    constexpr size_t bits = 4;
    std::array<unsigned char, 120> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0xF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit5)
{
    constexpr size_t bits = 5;
    std::array<unsigned char, 80> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x1F, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit6)
{
    constexpr size_t bits = 6;
    std::array<unsigned char, 120> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x3F, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit7)
{
    constexpr size_t bits = 7;
    std::array<unsigned char, 70> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x7F, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit8)
{
    constexpr size_t bits = 8;
    std::array<unsigned char, 120> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned char> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0xFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit9)
{
    constexpr size_t bits = 9;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    //auto idx = 0;
    //for (auto it = values.begin(); it != values.end(); ++it, ++idx)
    //    EXPECT_EQ(0x1FF, *it) << "idx = " << idx;

    auto idx = 0;
    for (size_t i = 0; i < values.size(); ++i, ++idx)
        EXPECT_EQ(0x1FF, values[i]) << "idx = " << idx;

    EXPECT_EQ(0x1FF, values[79]) << "idx = " << 793;
}

TEST(val_container, fiil_bit10)
{
    constexpr size_t bits = 10;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x3FF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit11)
{
    constexpr size_t bits = 11;
    std::array<unsigned char, 110> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x7FF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit12)
{
    constexpr size_t bits = 12;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0xFFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit13)
{
    constexpr size_t bits = 13;
    std::array<unsigned char, 130> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x1FFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit14)
{
    constexpr size_t bits = 14;
    std::array<unsigned char, 140> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x3FFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit15)
{
    constexpr size_t bits = 15;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x7FFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit16)
{
    constexpr size_t bits = 16;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned short> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0xFFFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit17)
{
    constexpr size_t bits = 17;
    std::array<unsigned char, 170> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned int> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0x1FFFF, *it) << "idx = " << idx;
}

TEST(val_container, fiil_bit24)
{
    constexpr size_t bits = 24;
    std::array<unsigned char, 90> arr;
    arr.fill(0xFF);

    val_container<bits, unsigned char, unsigned int> values(arr.data(), arr.size());

    auto idx = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++idx)
        EXPECT_EQ(0xFFFFFF, *it) << "idx = " << idx;
}