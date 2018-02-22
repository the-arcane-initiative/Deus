#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8ComputeByteLengthTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        const char* str;
        std::size_t expected_byte_length;


        TestData(const char* str_)
            : str                 (str_)
            , expected_byte_length(strlen(str) + 1)
        {
        }

        TestData(
                const char* str_,
                std::size_t expected_byte_length_)
            : str                   (str_)
            , expected_byte_length  (expected_byte_length_)
        {
        }

    };

    //--------------------------------ATTRIBUTES--------------------------------

    std::vector<TestData> test_data;

    //--------------------------------FUNCTIONS---------------------------------

    virtual void SetUp()
    {
        test_data =
        {
            TestData(""),
            TestData("a"),
            TestData("Hello"),
            TestData("Hello world!"),
            TestData("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),
            TestData("🌿𝄞ꬍꝊޝΟz@"),
            TestData("🌿𝄞ꬍꝊޝ"),
            TestData("🌿"),
            TestData("γειά σο"),
            TestData("this is a مزيج of text"),
            TestData(
                "This is a long string that is entirely composed of ASCII "
                "symbols. It does not have any Unicode symbols in it, which "
                "means that each symbol is worth exactly one byte!"
            ),
            TestData(" ͡°)"),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)"
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!"
            )
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8ComputeByteLengthTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        deus::utf8_impl::compute_byte_length_naive(data.str, byte_length);

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeByteLengthTest, strlen)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        deus::utf8_impl::compute_byte_length_strlen(data.str, byte_length);

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
    }
}
