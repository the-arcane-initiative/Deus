#include <gtest/gtest.h>

#include <deus/Exceptions.hpp>
#include <deus/UnicodeView.hpp>


//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST(UnicodeView, null_constructor)
{
    EXPECT_THROW(
        deus::UnicodeView(nullptr),
        deus::ValueError
    );

    EXPECT_THROW(
        deus::UnicodeView(nullptr, deus::Encoding::kUTF8),
        deus::ValueError
    );

    EXPECT_THROW(
        deus::UnicodeView(nullptr, 0),
        deus::ValueError
    );

    EXPECT_THROW(
        deus::UnicodeView(nullptr, 0, deus::Encoding::kUTF8),
        deus::ValueError
    );

    EXPECT_THROW(
        deus::UnicodeView(nullptr, 0, 0),
        deus::ValueError
    );

    EXPECT_THROW(
        deus::UnicodeView(nullptr, 0, 0, deus::Encoding::kUTF8),
        deus::ValueError
    );
}
