#include <gtest/gtest.h>

#include <vector>

#include <deus/UnicodeView.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8Concatenate
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        deus::UnicodeStorage a;
        deus::UnicodeStorage b;
        deus::UnicodeStorage result;
        deus::UnicodeStorage ascii_result;

        TestData(const char* a_, const char* b_, const char* result_)
            : a           (a_, deus::Encoding::kUTF8)
            , b           (b_, deus::Encoding::kUTF8)
            , result      (result_, deus::Encoding::kUTF8)
            , ascii_result(result)
        {
        }

        TestData(
                const char* a_,
                const char* b_,
                const char* result_,
                const char* ascii_result_)
            : a           (a_, deus::Encoding::kUTF8)
            , b           (b_, deus::Encoding::kUTF8)
            , result      (result_, deus::Encoding::kUTF8)
            , ascii_result(ascii_result_, deus::Encoding::kUTF8)
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
                "some text🌿𝄞ꬍꝊޝΟz@",
                "some text\x1A\x1A\x1A\x1A\x1A\x1Az@"
            ),
            TestData(
                "γειά σο",
                "",
                "γειά σο"
            ),
            TestData(
                "",
                "γειά σο",
                "γειά σο",
                "\x1A\x1A\x1A\x1A \x1A\x1A"
            ),
            TestData(
                "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols",
                " 😺. This means that *most* but not all     💣 symbols have a "
                "byte length of one. ( ͡° ͜ʖ ͡°)",
                 "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols 😺. This means that *most* but not "
                "all     💣 symbols have a byte length of one. ( ͡° ͜ʖ ͡°)",
                 "This is a long string that is composed of ASCII and a sparse "
                "amount of Unicode symbols \x1A. This means that *most* but "
                "not all     \x1A symbols have a byte length of one. ( \x1A"
                "\x1A \x1A\x1A \x1A\x1A)"
            ),
            TestData(
                "this is a مزيج ",
                "of text",
                "this is a مزيج of text"
            ),
            TestData(
                "this is a مز",
                "يج of text",
                "this is a مزيج of text",
                "this is a مز\x1A\x1A of text"
            )
            // TODO: more tests with unicode in first string
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8Concatenate, with_ascii)
{
    for(const TestData& data : test_data)
    {
        deus::UnicodeStorage b =
            data.b.get_view().convert(deus::Encoding::kASCII);
        deus::UnicodeStorage result =
            data.a.get_view().concatenate(b.get_view());

        EXPECT_EQ(result.get_string(), data.ascii_result.get_string());
    }
}

TEST_F(UTF8Concatenate, with_utf8)
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
