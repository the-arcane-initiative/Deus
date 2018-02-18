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
        std::size_t expected_symbol_length;

        TestData(
                const char* str_,
                std::size_t expected_byte_length_,
                std::size_t expected_symbol_length_)
            : str                   (str_)
            , expected_byte_length  (expected_byte_length_)
            , expected_symbol_length(expected_symbol_length_)
        {
        }

        TestData(const char* str_, std::size_t expected_symbol_length_)
            : str                   (str_)
            , expected_byte_length  (strlen(str) + 1)
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
            TestData(nullptr, 0, 0),
            TestData("", 0),
            TestData("a", 1),
            TestData("Hello", 5),
            TestData("Hello world!", 12),
            TestData("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 38),
            TestData("🌿𝄞ꬍꝊޝΟz@", 8),
            TestData("🌿𝄞ꬍꝊޝ", 5),
            TestData("🌿", 1),
            TestData("γειά σο", 7),
            TestData("this is a مزيج of text", 22)
            // TODO: harder tests cases
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
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_naive(
            data.str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeByteLengthTest, wstring_convert)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_wstring_convert(
            data.str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeByteLengthTest, byte_jump)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_byte_jump(
            data.str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeByteLengthTest, word_batching)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_word_batching(
            data.str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}

TEST_F(UTF8ComputeByteLengthTest, simd_batching)
{
    for(const TestData& data : test_data)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_simd_batching(
            data.str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, data.expected_byte_length)
            << "Incorrect byte length for \"" << data.str << "\"";
        EXPECT_EQ(symbol_length, data.expected_symbol_length)
            << "Incorrect symbol length for \"" << data.str << "\"";
    }
}
