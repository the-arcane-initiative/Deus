#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/ASCIIImpl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ASCIIComputeByteLengthTest
    : public ::testing::Test
{
protected:

    //--------------------------------ATTRIBUTES--------------------------------

    std::vector<const char*> test_strs;

    //--------------------------------FUNCTIONS---------------------------------

    virtual void SetUp()
    {
        test_strs =
        {
            "",
            "a",
            "Hello",
            "Hello world!"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
            "This is a much longer string, to test that the algorithims work"
                "on longer ASCII strings! Here are some digits and symbols to "
                "finish off with, 83489324839*($)>?4328493{}{\"\"\"",
            "This string contains some UTF8 unicode γειά σου Κόσμε! event "
                "though we're running it through an ASCII implementation. mجmج"
        };
    }
};


//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(ASCIIComputeByteLengthTest, naive)
{
    for(const char* test_str : test_strs)
    {
        std::size_t expect_byte_length = 0;
        if(test_str != nullptr)
        {
            expect_byte_length = strlen(test_str) + 1;
        }

        std::size_t byte_length = 0;

        deus::ascii_impl::compute_byte_length_naive(
            test_str,
            byte_length
        );

        EXPECT_EQ(byte_length, expect_byte_length)
            << "Incorrect byte length for \"" << test_str << "\"";
    }
}


TEST_F(ASCIIComputeByteLengthTest, strlen)
{
    for(const char* test_str : test_strs)
    {
        std::size_t expect_byte_length = 0;
        if(test_str != nullptr)
        {
            expect_byte_length = strlen(test_str) + 1;
        }

        std::size_t byte_length = 0;

        deus::ascii_impl::compute_byte_length_strlen(
            test_str,
            byte_length
        );

        EXPECT_EQ(byte_length, expect_byte_length)
            << "Incorrect byte length for \"" << test_str << "\"";
    }
}


TEST_F(ASCIIComputeByteLengthTest, std_string)
{
    for(const char* test_str : test_strs)
    {
        std::size_t expect_byte_length = 0;
        if(test_str != nullptr)
        {
            expect_byte_length = strlen(test_str) + 1;
        }

        std::size_t byte_length = 0;

        deus::ascii_impl::compute_byte_length_std_string(
            test_str,
            byte_length
        );

        EXPECT_EQ(byte_length, expect_byte_length)
            << "Incorrect byte length for \"" << test_str << "\"";
    }
}


TEST_F(ASCIIComputeByteLengthTest, word_batching)
{
    for(const char* test_str : test_strs)
    {
        std::size_t expect_byte_length = 0;
        if(test_str != nullptr)
        {
            expect_byte_length = strlen(test_str) + 1;
        }

        std::size_t byte_length = 0;

        deus::ascii_impl::compute_byte_length_word_batching(
            test_str,
            byte_length
        );

        EXPECT_EQ(byte_length, expect_byte_length)
            << "Incorrect byte length for \"" << test_str << "\"";
    }
}
