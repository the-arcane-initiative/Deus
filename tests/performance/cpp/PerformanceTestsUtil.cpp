#include "PerformanceTestsUtil.hpp"

#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <vector>

#include <deus/Exceptions.hpp>
#include <deus/UnicodeStorage.hpp>
#include <deus/UnicodeView.hpp>


namespace deus_perf_util
{

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

namespace
{

//-------------------------------GEN DYN STRINGS--------------------------------

struct GenDynStr
{
    const char* str;
    std::size_t byte_length;

    GenDynStr(const char* str_, std::size_t byte_length_)
        : str        (str_)
        , byte_length(byte_length_)
    {
    }

    ~GenDynStr()
    {
        if(str != nullptr)
        {
            // TODO: why does this cause a double free
            delete[] str;
            str = nullptr;
        }
    }
};

static std::vector<GenDynStr*> g_gen_rand_dyn_strs;
static std::size_t g_gen_rand_dyn_str_index = 0;
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes_short =
{
    1,
    12,
    7,
    20,
    17,
    3,
    7,
    2,
    1,
    5,
    3,
    15,
    19,
    8,
    9
};
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes_medium =
{
    21,
    100,
    87,
    45,
    25,
    128,
    250,
    147,
    36,
    77,
    202,
    47,
    99,
    127,
    32,
    64
};
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes_long =
{
    1000,
    8944,
    7363,
    2008,
    1050,
    3849,
    9999,
    1286,
    5894,
    4009
};
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes_xlong =
{
    10000,
    34595,
    99999,
    123940,
    74682,
    12874,
    76542,
    200982
};
static std::vector<std::size_t> g_gen_rand_dyn_str_sizes_mixed;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void clear_generators()
{
    // generated the mixed lengths the first time
    if(g_gen_rand_dyn_str_sizes_mixed.empty())
    {
        g_gen_rand_dyn_str_sizes_mixed.insert(
            g_gen_rand_dyn_str_sizes_mixed.end(),
            g_gen_rand_dyn_str_sizes_short.begin(),
            g_gen_rand_dyn_str_sizes_short.end()
        );
        g_gen_rand_dyn_str_sizes_mixed.insert(
            g_gen_rand_dyn_str_sizes_mixed.end(),
            g_gen_rand_dyn_str_sizes_medium.begin(),
            g_gen_rand_dyn_str_sizes_medium.end()
        );
        g_gen_rand_dyn_str_sizes_mixed.insert(
            g_gen_rand_dyn_str_sizes_mixed.end(),
            g_gen_rand_dyn_str_sizes_long.begin(),
            g_gen_rand_dyn_str_sizes_long.end()
        );
        g_gen_rand_dyn_str_sizes_mixed.insert(
            g_gen_rand_dyn_str_sizes_mixed.end(),
            g_gen_rand_dyn_str_sizes_xlong.begin(),
            g_gen_rand_dyn_str_sizes_xlong.end()
        );
        std::random_shuffle(
            g_gen_rand_dyn_str_sizes_mixed.begin(),
            g_gen_rand_dyn_str_sizes_mixed.end()
        );
    }

    g_gen_rand_dyn_str_index = 0;
    for(GenDynStr* dyn_str : g_gen_rand_dyn_strs)
    {
        delete dyn_str;
    }
    g_gen_rand_dyn_strs.clear();

    // reseed random
    srand(0xDEADBEEF);
}

void gen_rand_dyn_strs(
        deus::Encoding encoding,
        deus_perf_util::StringSize string_size)
{
    clear_generators();

    // determine size
    std::vector<std::size_t>* sizes = nullptr;
    switch(string_size)
    {
        case deus_perf_util::StringSize::kShort:
        {
            sizes = & g_gen_rand_dyn_str_sizes_short;
            break;
        }
        case deus_perf_util::StringSize::kMedium:
        {
            sizes = & g_gen_rand_dyn_str_sizes_medium;
            break;
        }
        case deus_perf_util::StringSize::kLong:
        {
            sizes = & g_gen_rand_dyn_str_sizes_long;
            break;
        }
        case deus_perf_util::StringSize::kExtraLong:
        {
            sizes = & g_gen_rand_dyn_str_sizes_xlong;
            break;
        }
        default:
        {
            sizes = & g_gen_rand_dyn_str_sizes_mixed;
            break;
        }
    }

    g_gen_rand_dyn_strs.reserve(sizes->size());
    for(std::size_t i = 0; i < sizes->size(); ++i)
    {
        // get the current size to generate
        std::size_t length = (*sizes)[g_gen_rand_dyn_str_index++];

        // generate based on requested encoding
        switch(encoding)
        {
            case deus::Encoding::kUTF8:
            {
                // generate random code-points
                std::vector<deus::CodePoint> code_points;
                code_points.reserve(length);
                std::size_t byte_count = 0;
                for(std::size_t i = 0; byte_count < length; ++i)
                {
                    // evenly distribute bytes sizes (but ensue we don't run off
                    // the end)
                    std::size_t remaining_bytes = length - byte_count;
                    int width = rand() % 4;
                    if(width >= remaining_bytes)
                    {
                        width = remaining_bytes - 1;
                    }

                    if(width == 0)
                    {
                        code_points.push_back(1 + (rand() % 0x7E));
                    }
                    else if(width == 1)
                    {
                        code_points.push_back(0x7F + (rand() % 0x780));
                    }
                    else if(width == 2)
                    {
                        code_points.push_back(0x7FF + (rand() % 0xF800));
                    }
                    else
                    {
                        code_points.push_back(0xFFFF + (rand() % 0x100000));
                    }
                    byte_count += width + 1;
                }

                // construct from code points using UnicodeStorage
                deus::UnicodeStorage storage(code_points);
                std::size_t byte_length = storage.get_view().byte_length();
                char* s = new char[byte_length];
                std::memcpy(s, storage.get_string().c_str(), byte_length);

                // store
                g_gen_rand_dyn_strs.push_back(new GenDynStr(s, byte_length));
                break;
            }
            case deus::Encoding::kUTF16_LE:
            {
                throw deus::NotImplementedError(
                    "gen_rand_dyn_strs is not yet supported for the UTF-16 "
                    "little endian encoding."
                );
                break;
            }
            case deus::Encoding::kUTF16_BE:
            {
                throw deus::NotImplementedError(
                    "gen_rand_dyn_strs is not yet supported for the UTF-16 "
                    "big endian encoding."
                );
            }
            case deus::Encoding::kUTF32_LE:
            {
                throw deus::NotImplementedError(
                    "gen_rand_dyn_strs is not yet supported for the UTF-32 "
                    "little endian encoding."
                );
            }
            case deus::Encoding::kUTF32_BE:
            {
                throw deus::NotImplementedError(
                    "gen_rand_dyn_strs is not yet supported for the UTF-32 "
                    "big endian encoding."
                );
            }
            default:
            {
                // generate random characters
                char* s = new char[length];
                for(std::size_t i = 0; i < length - 1; ++i)
                {
                    s[i] = (rand() % 127) + 1;
                }
                s[length - 1] = '\0';

                // store
                g_gen_rand_dyn_strs.push_back(new GenDynStr(s, length));
                break;
            }
        }
    }
}

const char* get_next_rand_dyn_str(std::size_t& byte_length)
{
    // wrap index
    if(g_gen_rand_dyn_str_index >= g_gen_rand_dyn_strs.size())
    {
        g_gen_rand_dyn_str_index = 0;
    }
    const char* ret = g_gen_rand_dyn_strs[g_gen_rand_dyn_str_index]->str;
    byte_length = g_gen_rand_dyn_strs[g_gen_rand_dyn_str_index]->byte_length;
    ++g_gen_rand_dyn_str_index;
    return ret;
}

} // namespace deus_perf_util
