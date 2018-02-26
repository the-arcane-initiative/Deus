#include <gtest/gtest.h>

#include <vector>

#include <deus/UnicodeView.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ASCIIConcatenate
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        deus::UnicodeStorage a;
        // in utf8
        deus::UnicodeStorage b;
        deus::UnicodeStorage result;

        TestData(const char* a_, const char* b_, const char* result_)
            : a     (a_, deus::Encoding::kASCII)
            , b     (b_, deus::Encoding::kUTF8)
            , result(result_, deus::Encoding::kASCII)
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
            TestData("", "", ""),
            TestData("a", "", "a"),
            TestData("", "a", "a"),
            TestData("Hello world!", "", "Hello world!"),
            TestData("", "Hello world!", "Hello world!"),
            TestData("Hello ", "world!", "Hello world!"),
            TestData("Hello world!", "", "Hello world!"),
            TestData(
                "some text",
                "🌿𝄞ꬍꝊޝΟz@",
                "some text\x1A\x1A\x1A\x1A\x1A\x1Az@"
            ),
            TestData(
                "",
                "γειά σο",
                "\x1A\x1A\x1A\x1A \x1A\x1A"
            ),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols",
                " 😺. This means that *most* but not all     💣 symbols have a "
                "byte length of one. ( ͡° ͜ʖ ͡°)",
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

TEST_F(ASCIIConcatenate, with_ascii)
{
    for(const TestData& data : test_data)
    {
        deus::UnicodeStorage b =
            data.b.get_view().convert(deus::Encoding::kASCII);
        deus::UnicodeStorage result =
            data.a.get_view().concatenate(b.get_view());

        EXPECT_EQ(result.get_string(), data.result.get_string());
    }
}

TEST_F(ASCIIConcatenate, with_utf8)
{
    for(const TestData& data : test_data)
    {
        deus::UnicodeStorage b =
            data.b.get_view().convert(deus::Encoding::kUTF8);
        deus::UnicodeStorage result =
            data.a.get_view().concatenate(b.get_view());

        EXPECT_EQ(result.get_string(), data.result.get_string());
    }
}

// TODO: tests for other encodings
