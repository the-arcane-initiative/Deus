#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8ComputeSymbolLengthTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        const char* str;
        std::size_t byte_length;
        std::size_t expected_symbol_length;

        TestData(
                const char* str_,
                std::size_t byte_length_,
                std::size_t expected_symbol_length_)
            : str                   (str_)
            , byte_length           (byte_length_)
            , expected_symbol_length(expected_symbol_length_)
        {
        }

        TestData(const char* str_, std::size_t expected_symbol_length_)
            : str                   (str_)
            , byte_length           (strlen(str) + 1)
            , expected_symbol_length(expected_symbol_length_)
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
            TestData("", 0),
            TestData("a", 1),
            TestData("Hello", 5),
            TestData("Hello world!", 12),
            TestData("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 38),
            TestData("🌿𝄞ꬍꝊޝΟz@", 8),
            TestData("🌿𝄞ꬍꝊޝ", 5),
            TestData("🌿", 1),
            TestData("γειά σο", 7),
            TestData("this is a مزيج of text", 22),
            TestData(
                "This is a long string that is entirely composed of ASCII "
                "symbols. It does not have any Unicode symbols in it, which "
                "means that each symbol is worth exactly one byte!",
                165
            ),
            TestData(" ͡°)", 4),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)",
                177
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                169
            )
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8ComputeSymbolLengthTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::size_t symbol_length = 0;

        deus::utf8_inl::compute_symbol_length_naive(
            data.str,
            data.byte_length,
            symbol_length
        );

        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeSymbolLengthTest, wstring_convert)
{
    for(const TestData& data : test_data)
    {
        std::size_t symbol_length = 0;

        deus::utf8_inl::compute_symbol_length_wstring_convert(
            data.str,
            data.byte_length,
            symbol_length
        );

        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeSymbolLengthTest, byte_jump)
{
    for(const TestData& data : test_data)
    {
        std::size_t symbol_length = 0;

        deus::utf8_inl::compute_symbol_length_byte_jump(
            data.str,
            data.byte_length,
            symbol_length
        );

        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeSymbolLengthTest, word_batching)
{
    for(const TestData& data : test_data)
    {
        std::size_t symbol_length = 0;

        deus::utf8_inl::compute_symbol_length_word_batching(
            data.str,
            data.byte_length,
            symbol_length
        );

        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}
