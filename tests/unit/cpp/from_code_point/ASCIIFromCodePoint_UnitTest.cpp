#include <gtest/gtest.h>

#include <vector>

#include <deus/Constants.hpp>
#include <deus/unicode_view_impl/ASCIIImpl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ASCIIFromCodePointTest
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
                "Hello world!"),
            TestData({0xFF}, "\xFF"),
            TestData({0x1FF, 0xFFFFFFFF, 0x2B}, "\xFF\xFF+"),
        };
    }
};


//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(ASCIIFromCodePointTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::string result =
            deus::ascii_inl::from_code_point_naive(data.code_points);
        EXPECT_EQ(result, data.expected);
    }
}
