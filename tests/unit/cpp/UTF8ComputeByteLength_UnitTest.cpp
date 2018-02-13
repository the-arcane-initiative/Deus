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

    std::vector<const char*> test_strs;

    virtual void SetUp()
    {
        test_strs =
        {
            nullptr,
            "",
            "a",
            "Hello",
            "Hello world!"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8ComputeByteLengthTest, naive)
{
    for(const char* test_str : test_strs)
    {
        std::size_t expect_byte_length = 0;
        std::size_t expect_symbol_length = 0;
        if(test_str != nullptr)
        {
            expect_symbol_length = strlen(test_str);
            expect_byte_length = expect_symbol_length + 1;
        }

        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        deus::utf8_impl::compute_byte_length_naive(
            test_str,
            byte_length,
            symbol_length
        );

        EXPECT_EQ(byte_length, expect_byte_length)
            << "Incorrect byte length for \"" << test_str << "\"";
        EXPECT_EQ(symbol_length, expect_symbol_length)
            << "Incorrect symbol length for \"" << test_str << "\"";
    }
}
