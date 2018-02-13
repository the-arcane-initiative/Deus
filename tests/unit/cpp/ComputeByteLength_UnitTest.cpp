#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/ASCIIImpl.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ASCIIComputeByteLengthTest
    : public ::testing::Test
{
protected:

    std::vector<std::string> test_strs;

    virtual void SetUp()
    {
        test_strs =
        {
            "",
            "a",
            "Hello",
            "Hello world!"
            // TODO:
        };
    }
};


//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(ASCIIComputeByteLengthTest, naive)
{
    for(const std::string& test_str : test_strs)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::ascii_impl::compute_byte_length_naive(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        EXPECT_EQ(byte_length, test_str.length() + 1)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, test_str.length())
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}


TEST_F(ASCIIComputeByteLengthTest, strlen)
{
    for(const std::string& test_str : test_strs)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::ascii_impl::compute_byte_length_strlen(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        EXPECT_EQ(byte_length, test_str.length() + 1)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, test_str.length())
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}

TEST_F(ASCIIComputeByteLengthTest, std_string)
{
    for(const std::string& test_str : test_strs)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::ascii_impl::compute_byte_length_std_string(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        EXPECT_EQ(byte_length, test_str.length() + 1)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, test_str.length())
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}

TEST_F(ASCIIComputeByteLengthTest, word_batching)
{
    for(const std::string& test_str : test_strs)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::ascii_impl::compute_byte_length_word_batching(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        EXPECT_EQ(byte_length, test_str.length() + 1)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, test_str.length())
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}

TEST_F(ASCIIComputeByteLengthTest, simd_batching)
{
    for(const std::string& test_str : test_strs)
    {
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::ascii_impl::compute_byte_length_simd_batching(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        EXPECT_EQ(byte_length, test_str.length() + 1)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, test_str.length())
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}
