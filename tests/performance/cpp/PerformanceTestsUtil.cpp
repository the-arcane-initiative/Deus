#include "PerformanceTestsUtil.hpp"

#include <vector>
#include <stdlib.h>
#include <time.h>


namespace deus_perf_util
{

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

namespace
{

// gen_rand_dyn_str
static std::size_t g_gen_rand_dyn_str_index = 0;
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes = {
    10,
    1,
    13,
    44,
    7,
    9,
    66,
    128,
    64,
    346,
    2,
    4,
    17,
    64,
    12,
    12,
    45,
    124,
    256
};

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void clear_generators()
{
    g_gen_rand_dyn_str_index = 0;

    // reseed random
    srand(time(nullptr));
}

void gen_rand_dyn_str(const char** str, std::size_t& byte_length)
{
    // wrap generator
    if(g_gen_rand_dyn_str_index >= g_gen_rand_dyn_str_sizes.size())
    {
        g_gen_rand_dyn_str_index = 0;
    }
    // get the current size to generate
    byte_length = g_gen_rand_dyn_str_sizes[g_gen_rand_dyn_str_index++];
    char* s = new char[byte_length];
    for(std::size_t i = 0; i < byte_length - 1; ++i)
    {
        s[i] = (rand() % 128) + 1;
    }
    s[byte_length - 1] = '\0';
    *str = s;
}

} // namespace deus_perf_util
