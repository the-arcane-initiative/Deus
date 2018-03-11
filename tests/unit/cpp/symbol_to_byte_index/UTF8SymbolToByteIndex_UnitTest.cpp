#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8SymbolToByteIndexTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        deus::UnicodeStorage str;
        std::size_t symbol_index;
        std::size_t expected;

        TestData(
                const char* str_,
                std::size_t symbol_index_,
                std::size_t expected_)
            : str         (str_, deus::Encoding::kUTF8)
            , symbol_index(symbol_index_)
            , expected    (expected_)
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
            TestData("Ꝋ", 1, deus::NULL_POS),
            TestData("this is a مزيج of text", 3, 3),
            TestData("this is a مزيج of text", 17, 21),
            TestData("this is a مزيج of text", 22, deus::NULL_POS),
            TestData("🌿𝄞ꬍꝊޝΟz@", 0, 0),
            TestData("🌿𝄞ꬍꝊޝΟz@", 4, 14),
            TestData("🌿𝄞ꬍꝊޝΟz@", 7, 19),
            TestData("🌿𝄞ꬍꝊޝΟz@", 8, deus::NULL_POS),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)",
                175,
                186
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                27,
                69
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                160,
                412
            ),
            TestData(
                "यो एक लामो स्ट्रिंग हो जुन पुरा तरिकाले ASCII बाट "
                "बनाइएको छ प्रतीकहरू। यसमा यसको कुनै यूनिकोड प्रतीकहरू "
                "छैनन्, जुन यसको मतलब छ कि प्रत्येक प्रतीक बिल्कुल एक बाइट "
                "लायक छ!",
                169,
                deus::NULL_POS
            )

        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8SymbolToByteIndexTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::size_t result = deus::utf8_impl::symbol_to_byte_index_naive(
            data.str.get_view(),
            data.symbol_index
        );
        EXPECT_EQ(result, data.expected)
            << "Incorrect result when getting the byte index of the symbol at "
            << "index " << data.symbol_index << " in the string \""
            << data.str.get_string() << "\"";
    }
}
