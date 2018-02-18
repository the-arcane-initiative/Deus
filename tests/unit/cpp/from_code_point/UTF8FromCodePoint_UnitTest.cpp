#include <gtest/gtest.h>

#include <vector>

#include <deus/Constants.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8FromCodePointTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        std::vector<deus::CodePoint> code_points;
        std::string expected;

        TestData(
                const std::vector<deus::CodePoint>& code_points_,
                const std::string& expected_)
            : code_points(code_points_)
            , expected     (expected_)
        {
        }
    };

    //--------------------------------ATTRIBUTES--------------------------------

    std::vector<TestData> test_data;

    //--------------------------------FUNCTIONS--------------------------------

    virtual void SetUp()
    {
        test_data =
        {
            TestData({}, ""),
            TestData({0x61}, "a"),
            TestData(
                {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C,
                    0x64, 0x21},
                "Hello world!"
            ),
            TestData({0x7F}, "\x7F"),
            TestData({0xA7}, "§"),
            TestData({0x7FF}, "߿"),
            TestData({0x800}, "ࠀ"),
            TestData({0xD7F}, "ൿ"),
            TestData({0x10000}, "𐀀"),
            TestData({0x1F4A9}, "\xF0\x9F\x92\xA9"),
            TestData(
                {0x1F33F, 0x1D11E, 0xAB0D, 0xA74A, 0x079D, 0x039F, 0x7A, 0x40},
                "🌿𝄞ꬍꝊޝΟz@")
        };
    }
};


//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8FromCodePointTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::string result =
            deus::utf8_impl::from_code_point_naive(data.code_points);
        EXPECT_EQ(result, data.expected);
    }
}
