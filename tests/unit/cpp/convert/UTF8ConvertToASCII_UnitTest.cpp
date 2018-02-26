#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8ConvertToASCII
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        const char* utf8;
        const char* ascii;
        std::size_t byte_length;
        std::size_t symbol_length;

        TestData(const char* utf8_, const char* ascii_)
            : utf8 (utf8_)
            , ascii(ascii_)
        {
            deus::UnicodeView view(utf8_, deus::Encoding::kUTF8);
            byte_length = view.byte_length();
            symbol_length = view.length();
        }
    };

    //--------------------------------ATTRIBUTES--------------------------------

    std::vector<TestData> test_data;

    //--------------------------------FUNCTIONS---------------------------------

    virtual void SetUp()
    {
        test_data =
        {
            TestData("", ""),
            TestData("a", "a"),
            TestData("Hello world!", "Hello world!"),
            TestData(
                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            ),
            TestData("🌿𝄞ꬍꝊޝΟz@", "\x1A\x1A\x1A\x1A\x1A\x1Az@"),
            TestData("γειά σο", "\x1A\x1A\x1A\x1A \x1A\x1A"),
            TestData(
                "this is a مزيج of text",
                "this is a \x1A\x1A\x1A\x1A of text"
            ),
            TestData(
                "This is a long string that is entirely composed of ASCII "
                "symbols. It does not have any Unicode symbols in it, which "
                "means that each symbol is worth exactly one byte!",
                "This is a long string that is entirely composed of ASCII "
                "symbols. It does not have any Unicode symbols in it, which "
                "means that each symbol is worth exactly one byte!"
            ),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)",
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols \x1A. This means that *most* but "
                "not all     \x1A symbols have a byte length of one. ( \x1A"
                "\x1A \x1A\x1A \x1A\x1A)"
            )
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8ConvertToASCII, naive)
{
    for(const TestData& data : test_data)
    {
        deus::UnicodeStorage ascii = deus::utf8_impl::convert_to_ascii_naive(
            data.utf8,
            data.byte_length,
            data.symbol_length
        );

        EXPECT_EQ(ascii.get_string(), std::string(data.ascii));
    }
}
