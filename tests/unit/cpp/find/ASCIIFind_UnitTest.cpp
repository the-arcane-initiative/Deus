#include <gtest/gtest.h>

#include <vector>

#include <deus/unicode_view_impl/EncodingImpl.hpp>


//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class ASCIIFindTest
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
            : a       (a_, deus::Encoding::kASCII)
            , b       (b_, deus::Encoding::kASCII)
            , position(0)
        {
            expected = a.get_string().find(b.get_string());
        }

        TestData(const char* a_, const char* b_, std::size_t position_)
            : a       (a_, deus::Encoding::kASCII)
            , b       (b_, deus::Encoding::kASCII)
            , position(position_)
        {
            expected = a.get_string().find(b.get_string(), position);
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
            // TestData("Hello world!", ""),
            // TestData("a", "a"),
            // TestData("aaaaaaa", "a"),
            // TestData("Hello world!", "Hello"),
            // TestData("Hello world!", "wolrd!"),
            // TestData("Hello world!", "lo wo!"),
            // TestData("Hello world!", "hello"),
            // TestData(
            //     "This string is quite a bit longer and contains the subject "
            //     "string more than once",
            //     "string"
            // ),
            // TestData(
            //     "This string is quite a bit longer and but does not contain "
            //     "the subject string",
            //     "and\t"
            // ),
            // TestData(
            //     "This string contains the subject right near the end of the "
            //     "string, and the subject is a single character: \'x\'.",
            //     "x"
            // ),
            TestData("", "", 0),
            // TestData("", "", 1),
            // TestData("a", "a", 0),
            // TestData("a", "a", 1),
            // TestData("aaaaaaa", "a", 3),
            // TestData("aaaaaaa", "a", 6),
            // TestData("Hello world!", "Hello", 1),
            // TestData("Hello world!", "wolrd!", 5),
            // TestData(
            //     "This string is quite a bit longer and contains the subject "
            //     "string more than once",
            //     "string",
            //     26
            // ),
            // TestData(
            //     "This string is quite a bit longer and but does not contain "
            //     "the subject string",
            //     "and\t",
            //     13
            // ),
            // TestData(
            //     "This string contains the subject right near the end of the "
            //     "string, and the subject is a single character: \'x\'.",
            //     "x",
            //     32
            // )
        };
    }
};

//------------------------------------------------------------------------------
//                                     TESTS
//------------------------------------------------------------------------------

TEST_F(ASCIIFindTest, naive)
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
