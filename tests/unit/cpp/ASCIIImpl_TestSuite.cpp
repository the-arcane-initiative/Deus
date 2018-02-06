#include "Catch.hpp"

#include <deus/UnicodeView.hpp>


//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

TEST_CASE("ASCII Constructors", "[UnicodeView][ASCIIImpl]")
{
    SECTION("const char*")
    {
        SECTION("empty string")
        {
            deus::UnicodeView s("", deus::Encoding::kASCII);

            SECTION("encoding type")
            {
                REQUIRE(s.encoding() == deus::Encoding::kASCII);
            }
            SECTION("length")
            {
                REQUIRE(s.length() == 0);
            }
        }

        SECTION("Hello world!")
        {
            deus::UnicodeView s("Hello world!", deus::Encoding::kASCII);

            SECTION("encoding type")
            {
                REQUIRE(s.encoding() == deus::Encoding::kASCII);
            }
            SECTION("length")
            {
                REQUIRE(s.length() == 12);
            }
        }
    }
}
