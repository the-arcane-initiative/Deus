#include "Catch.hpp"

// obtain access to the private components of Deus
#define protected public
#define private public

#include <deus/unicode_view_impl/ASCIIImpl.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>

// TODO: REMOVE ME
#include <iostream>

TEST_CASE(
    "ascii_compute_byte_length_naive",
    "[UnicodeView][ASCII][compute_byte_length][naive]")
{
    std::size_t byte_length = 0;
    std::size_t symbol_length = 0;

    SECTION("empty string")
    {
        const std::string test_str;

        deus::UnicodeView::ASCIIImpl::compute_byte_length_naive(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        REQUIRE(byte_length == test_str.length() + 1);
        REQUIRE(symbol_length == test_str.length());
    }
    SECTION("a")
    {
        const std::string test_str("a");

        deus::UnicodeView::ASCIIImpl::compute_byte_length_naive(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        REQUIRE(byte_length == test_str.length() + 1);
        REQUIRE(symbol_length == test_str.length());
    }
    SECTION("a")
    {
        const std::string test_str("a");

        deus::UnicodeView::ASCIIImpl::compute_byte_length_naive(
            test_str.c_str(),
            byte_length,
            symbol_length
        );
        REQUIRE(byte_length == test_str.length() + 1);
        REQUIRE(symbol_length == test_str.length());
    }
}


// TEST_CASE("compute_byte_length", "[UnicodeView]")
// {
//     SECTION("ASCII")
//     {
//         std::vector<std::string> test_strs =
//         {
//             "",
//             "a",
//             "Hello",
//             "Hello world!"
//         };

//         for(const std::string& test_str : test_strs)
//         {
//             std::cout << "TEST STR: " << test_str << std::endl;

//             std::size_t byte_length = 0;
//             std::size_t symbol_length = 0;

//             SECTION("naive")
//             {
//                 deus::UnicodeView::ASCIIImpl::compute_byte_length_naive(
//                     test_str.c_str(),
//                     byte_length,
//                     symbol_length
//                 );
//                 REQUIRE(byte_length == test_str.length() + 1);
//                 REQUIRE(symbol_length == test_str.length());
//             }
//             SECTION("strlen")
//             {
//                 deus::UnicodeView::ASCIIImpl::compute_byte_length_strlen(
//                     test_str.c_str(),
//                     byte_length,
//                     symbol_length
//                 );
//                 REQUIRE(byte_length == test_str.length() + 1);
//                 REQUIRE(symbol_length == test_str.length());
//             }
//             SECTION("std_string")
//             {
//                 deus::UnicodeView::ASCIIImpl::compute_byte_length_std_string(
//                     test_str.c_str(),
//                     byte_length,
//                     symbol_length
//                 );
//                 REQUIRE(byte_length == test_str.length() + 1);
//                 REQUIRE(symbol_length == test_str.length());
//             }
//             SECTION("word_batching")
//             {
//                 deus::UnicodeView::ASCIIImpl::compute_byte_length_word_batching(
//                     test_str.c_str(),
//                     byte_length,
//                     symbol_length
//                 );
//                 REQUIRE(byte_length == test_str.length() + 1);
//                 REQUIRE(symbol_length == test_str.length());
//             }
//             SECTION("word_batching")
//             {
//                 deus::UnicodeView::ASCIIImpl::compute_byte_length_word_batching(
//                     test_str.c_str(),
//                     byte_length,
//                     symbol_length
//                 );
//                 REQUIRE(byte_length == test_str.length() + 1);
//                 REQUIRE(symbol_length == test_str.length());
//             }
//         }
//     }

// }
