#include <gtest/gtest.h>
#include "../val_container.h"

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