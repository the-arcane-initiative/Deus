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

TEST(UnicodeView, equality)
{
    {
        const std::string a_str("");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kASCII);
        const std::string b_str("");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kASCII);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_TRUE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kASCII);
        const std::string b_str("");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kASCII);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("a");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_FALSE(a_view == b_view);
        EXPECT_TRUE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("a");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("a");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_TRUE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("Hello world!");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("Hello world!");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_TRUE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("Hello world!");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("Hello world!");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kASCII);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("Hello world!");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("Hello world");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_FALSE(a_view == b_view);
        EXPECT_TRUE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("Hello world!");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kASCII);
        const std::string b_str("Hello world");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_FALSE(a_view == b_view);
        EXPECT_TRUE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_TRUE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_TRUE(a_view.explicit_equals(b_view));
    }


    {
        const std::string a_str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kUTF8);
        const std::string b_str("🌿𝄞ꬍꝊ😺Οz@");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_FALSE(a_view == b_view);
        EXPECT_TRUE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    {
        const std::string a_str("\x1A\x1A\x1A\x1A \x1A\x1A");
        const deus::UnicodeView a_view(a_str, deus::Encoding::kASCII);
        const std::string b_str("γειά σο");
        const deus::UnicodeView b_view(b_str, deus::Encoding::kUTF8);

        EXPECT_TRUE(a_view == b_view);
        EXPECT_FALSE(a_view != b_view);
        EXPECT_FALSE(a_view.explicit_equals(b_view));
    }

    // TODO: more tests for different encodings
}

TEST(UnicodeView, bytes_as_hex)
{
    {
        const std::string str("");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {};

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        // TODO: can probably provider a macro for this
        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("a");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {"0x61"};

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("Hello world!");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {
            "0x48", "0x65", "0x6C", "0x6C", "0x6F", "0x20", "0x77", "0x6F",
            "0x72", "0x6C", "0x64", "0x21"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("Hello world!");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {
            "\\x48", "\\x65", "\\x6C", "\\x6C", "\\x6F", "\\x20", "\\x77",
            "\\x6F", "\\x72", "\\x6C", "\\x64", "\\x21"
        };

        const std::vector<deus::UnicodeStorage> result =
            input.bytes_as_hex("\\x");

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("Hello world!");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {
            "0x48", "0x65", "0x6c", "0x6c", "0x6f", "0x20", "0x77", "0x6f",
            "0x72", "0x6c", "0x64", "0x21"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex(
            "0x",
            false
        );

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("Hello world!");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {
            "hex48", "hex65", "hex6c", "hex6c", "hex6f", "hex20", "hex77",
            "hex6f", "hex72", "hex6c", "hex64", "hex21"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex(
            "hex",
            false
        );

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("\xFF");
        const deus::UnicodeView input(str, deus::Encoding::kASCII);
        const std::vector<std::string> expected = {"0xFF"};

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("Hello world!");
        const deus::UnicodeView input(str, deus::Encoding::kUTF8);
        const std::vector<std::string> expected = {
            "0x48", "0x65", "0x6C", "0x6C", "0x6F", "0x20", "0x77", "0x6F",
            "0x72", "0x6C", "0x64", "0x21"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("🌿");
        const deus::UnicodeView input(str, deus::Encoding::kUTF8);
        const std::vector<std::string> expected = {
            "0xF0", "0x9F", "0x8C", "0xBF"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    {
        const std::string str("🌿𝄞ꬍꝊޝΟz@");
        const deus::UnicodeView input(str, deus::Encoding::kUTF8);
        const std::vector<std::string> expected = {
            "0xF0", "0x9F", "0x8C", "0xBF", "0xF0", "0x9D", "0x84", "0x9E",
            "0xEA", "0xAC", "0x8D", "0xEA", "0x9D", "0x8A", "0xDE", "0x9D",
            "0xCE", "0x9F", "0x7A", "0x40"
        };

        const std::vector<deus::UnicodeStorage> result = input.bytes_as_hex();

        ASSERT_EQ(result.size(), expected.size());
        for(std::size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_EQ(result[i].get_string(), expected[i]);
        }
    }

    // TODO: more tests for different encodings
}
