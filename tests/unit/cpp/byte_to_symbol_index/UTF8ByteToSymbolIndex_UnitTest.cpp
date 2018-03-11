#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8ByteToSymbolIndexTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        deus::UnicodeStorage str;
        std::size_t byte_index;
        std::size_t expected;

        TestData(
                const char* str_,
                std::size_t byte_index_,
                std::size_t expected_)
            : str       (str_, deus::Encoding::kUTF8)
            , byte_index(byte_index_)
            , expected  (expected_)
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
            TestData("", 0, deus::NULL_POS),
            TestData("a", 0, 0),
            TestData("a", 1, deus::NULL_POS),
            TestData("a", 5, deus::NULL_POS),
            TestData("ab", 1, 1),
            TestData("Hello world!", 6, 6),
            TestData("Hello world!", 11, 11),
            TestData("Hello world!", 12, deus::NULL_POS),
            TestData(
                "This is a really long string compared to this other strings. "
                "It contains only ASCII symbols even though it's UTF-8 "
                "encoded.",
                6,
                6
            ),
            TestData(
                "This is a really long string compared to this other strings. "
                "It contains only ASCII symbols even though it's UTF-8 "
                "encoded.",
                58,
                58
            ),
            TestData(
                "This is a really long string compared to this other strings. "
                "It contains only ASCII symbols even though it's UTF-8 "
                "encoded.",
                333,
                deus::NULL_POS
            ),
            TestData("Ꝋ", 0, 0),
            TestData("Ꝋ", 1, 0),
            TestData("Ꝋ", 2, 0),
            TestData("Ꝋ", 3, deus::NULL_POS),
            TestData("this is a مزيج of text", 3, 3),
            TestData("this is a مزيج of text", 21, 17),
            TestData("this is a مزيج of text", 26, deus::NULL_POS),
            TestData("🌿𝄞ꬍꝊޝΟz@", 0, 0),
            TestData("🌿𝄞ꬍꝊޝΟz@", 14, 4),
            TestData("🌿𝄞ꬍꝊޝΟz@", 19, 7),
            TestData("🌿𝄞ꬍꝊޝΟz@", 20, deus::NULL_POS),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)",
                186,
                175
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                69,
                27
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                412,
                160
            )
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8ByteToSymbolIndexTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::size_t result = deus::utf8_impl::byte_to_symbol_index_naive(
            data.str.get_view(),
            data.byte_index
        );
        EXPECT_EQ(result, data.expected)
            << "Incorrect result when getting the symbol index of the byte at "
            << "index " << data.byte_index << " in the string \""
            << data.str.get_string() << "\"";
    }
}
