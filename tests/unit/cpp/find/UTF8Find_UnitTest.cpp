#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/EncodingImpl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class UTF8FindTest
    : public ::testing::Test
{
protected:

    //---------------------------------STRUCTS----------------------------------

    struct TestData
    {
        deus::UnicodeStorage a;
        deus::UnicodeStorage b;
        std::size_t position;
        std::size_t expected;

        TestData(const char* a_, const char* b_)
            : a       (a_, deus::Encoding::kUTF8)
            , b       (b_, deus::Encoding::kUTF8)
            , position(0)
        {
            expected = byte_to_symbol(
                a.get_string().find(b.get_string())
            );
        }

        TestData(const char* a_, const char* b_, std::size_t position_)
            : a       (a_, deus::Encoding::kUTF8)
            , b       (b_, deus::Encoding::kUTF8)
            , position(position_)
        {
            expected = byte_to_symbol(a.get_string().find(
                b.get_string(),
                symbol_to_byte(position)
            ));
        }

        std::size_t symbol_to_byte(std::size_t symbol_index)
        {
            if(symbol_index != deus::NULL_POS)
            {
                std::size_t byte_index = a.symbol_to_byte_index(symbol_index);
                if(byte_index != deus::NULL_POS)
                {
                    return byte_index;
                }
            }
            return symbol_index;
        }

        std::size_t byte_to_symbol(std::size_t byte_index)
        {
            if(byte_index != deus::NULL_POS)
            {
                std::size_t symbol_index = a.byte_to_symbol_index(byte_index);
                if(symbol_index != deus::NULL_POS)
                {
                    return symbol_index;
                }
            }
            return byte_index;
        }
    };

    //--------------------------------ATTRIBUTES--------------------------------

    std::vector<TestData> test_data;

    //--------------------------------FUNCTIONS---------------------------------

    virtual void SetUp()
    {
        test_data =
        {
            // TestData("", ""),
            // TestData("a", ""),
            // TestData("Hello Мир!", ""),
            // TestData("a", "a"),
            // TestData("😺😺😺😺😺😺", "😺"),
            // TestData("Hello Мир!", "Hello"),
            // TestData("Hello Мир!", "Мир!"),
            // TestData("Hello Мир!", "lo Ми!"),
            // TestData("Hello Мир!", "hello"),
            // // from here
            // TestData(
            //     "This দড়ি is quite a bit longer và contains the subject "
            //     "দড়ি more than once",
            //     "দড়ি"
            // ),
            // TestData(
            //     "This দড়ি is quite a bit longer và but does not contain "
            //     "the subject দড়ি",
            //     "và\t"
            // ),
            // TestData(
            //     "This দড়ি contains the subject right near the end of the "
            //     "দড়ি, và the subject is a single character: \'x\'.",
            //     "x"
            // ),
            TestData("", "", 0),
            TestData("", "", 1),
            TestData("a", "a", 0),
            TestData("a", "a", 1),
            // TestData("😺😺😺😺😺😺", "😺", 3),
            TestData("😺😺😺😺😺😺", "😺", 6),
            // TestData("Hello world!", "Hello", 1),
            // TestData("Hello world!", "wolrd!", 5),
            // TestData(
            //     "This দড়ি is quite a bit longer và contains the subject "
            //     "দড়ি more than once",
            //     "দড়ি",
            //     26
            // ),
            // TestData(
            //     "This দড়ি is quite a bit longer và but does not contain "
            //     "the subject দড়ি",
            //     "và\t",
            //     13
            // ),
            // TestData(
            //     "This দড়ি contains the subject right near the end of the "
            //     "দড়ি, và the subject is a single character: \'x\'.",
            //     "x",
            //     32
            // )
            // TODO: might need an extra test that ensures pos is symbol based
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(UTF8FindTest, naive)
{
    for(const TestData& data : test_data)
    {
        std::size_t result = deus::generic_inl::find_naive(
            data.a.get_view(),
            data.b.get_view(),
            data.position
        );

        EXPECT_EQ(result, data.expected)
            << "Incorrect result when searching \"" << data.a.get_string()
            << "\" for \"" << data.b.get_string() << "\" from position: "
            << data.position;
    }
}
