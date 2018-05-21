#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                     SHORT
//------------------------------------------------------------------------------

//---------------------------U T F 8    S T R I N G S---------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_short_utf8_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_utf8_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_short_utf8_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_utf8_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_short_utf8_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_utf8_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_short_utf8_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_utf8_word_batching);

//--------------------------A S C I I    S T R I N G S--------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_short_ascii_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_ascii_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_short_ascii_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_ascii_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_short_ascii_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_ascii_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_short_ascii_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_short_ascii_word_batching);

//------------------------------------------------------------------------------
//                                     MEDIUM
//------------------------------------------------------------------------------

//---------------------------U T F 8    S T R I N G S---------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_medium_utf8_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_utf8_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_medium_utf8_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_utf8_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_medium_utf8_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_utf8_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_medium_utf8_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_utf8_word_batching);

//--------------------------A S C I I    S T R I N G S--------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_medium_ascii_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_ascii_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_medium_ascii_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_ascii_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_medium_ascii_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_ascii_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_medium_ascii_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_medium_ascii_word_batching);

//------------------------------------------------------------------------------
//                                      LONG
//------------------------------------------------------------------------------

//---------------------------U T F 8    S T R I N G S---------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_long_utf8_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_utf8_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_long_utf8_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_utf8_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_long_utf8_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_utf8_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_long_utf8_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_utf8_word_batching);

//--------------------------A S C I I    S T R I N G S--------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_long_ascii_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_ascii_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_long_ascii_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_ascii_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_long_ascii_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_ascii_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_long_ascii_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_long_ascii_word_batching);

//------------------------------------------------------------------------------
//                                   EXTRA LONG
//------------------------------------------------------------------------------

//---------------------------U T F 8    S T R I N G S---------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_xlong_utf8_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_utf8_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_xlong_utf8_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_utf8_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_xlong_utf8_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_utf8_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_xlong_utf8_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_utf8_word_batching);

//--------------------------A S C I I    S T R I N G S--------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_xlong_ascii_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_ascii_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_xlong_ascii_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_ascii_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_xlong_ascii_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_ascii_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_xlong_ascii_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_xlong_ascii_word_batching);

//------------------------------------------------------------------------------
//                                     MIXED
//------------------------------------------------------------------------------

//---------------------------U T F 8    S T R I N G S---------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_mixed_utf8_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_utf8_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_mixed_utf8_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_utf8_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_mixed_utf8_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_utf8_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_mixed_utf8_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_utf8_word_batching);

//--------------------------A S C I I    S T R I N G S--------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_symbol_length_mixed_ascii_naive(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_ascii_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_symbol_length_mixed_ascii_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_ascii_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_symbol_length_mixed_ascii_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_ascii_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_symbol_length_mixed_ascii_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t byte_length = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(byte_length);

        // call
        std::size_t symbol_length = 0;
        deus::utf8_inl::compute_symbol_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_symbol_length_mixed_ascii_word_batching);
