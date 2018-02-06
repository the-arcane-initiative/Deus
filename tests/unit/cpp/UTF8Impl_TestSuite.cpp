#include "Catch.hpp"

#include <deus/UnicodeView.hpp>


//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

TEST_CASE("UTF8 constructors", "[UnicodeView][UTF8Impl]")
{
    SECTION("const char*")
    {
        SECTION("empty string")
        {
            deus::UnicodeView s("", deus::Encoding::kUTF8);

            SECTION("encoding type")
            {
                REQUIRE(s.encoding() == deus::Encoding::kUTF8);
            }
            SECTION("length")
            {
                REQUIRE(s.length() == 0);
            }
        }

        SECTION("Hello world!")
        {
            deus::UnicodeView s("Hello world!", deus::Encoding::kUTF8);

            SECTION("encoding type")
            {
                REQUIRE(s.encoding() == deus::Encoding::kUTF8);
            }
            SECTION("length")
            {
                REQUIRE(s.length() == 12);
            }
        }

        // TODO: normal strings

        SECTION("γειά σου Κόσμε")
        {
            deus::UnicodeView s("γειά σου Κόσμε", deus::Encoding::kUTF8);

            SECTION("encoding type")
            {
                REQUIRE(s.encoding() == deus::Encoding::kUTF8);
            }
            SECTION("length")
            {
                REQUIRE(s.length() == 14);
            }
        }
    }
}
