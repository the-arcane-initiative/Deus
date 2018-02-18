#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

#include <deus/unicode_view_impl/ASCIIImpl.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                     SHORT
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_byte_length_short_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_naive);

//------------------------------------STRLEN------------------------------------

// The results of this will be wrong, but we still want to use it as a benchmark
// to get as close as possible to
static void BM_utf8_compute_byte_length_short_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::ascii_impl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_strlen);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_byte_length_short_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_byte_length_short_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_short_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_short_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_simd_batching);

//------------------------------------------------------------------------------
//                                     MEDIUM
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_byte_length_medium_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_naive);

//------------------------------------STRLEN------------------------------------

// The results of this will be wrong, but we still want to use it as a benchmark
// to get as close as possible to
static void BM_utf8_compute_byte_length_medium_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::ascii_impl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_strlen);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_byte_length_medium_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_byte_length_medium_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_medium_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_medium_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_simd_batching);

//------------------------------------------------------------------------------
//                                      LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_byte_length_long_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_naive);

//------------------------------------STRLEN------------------------------------

// The results of this will be wrong, but we still want to use it as a benchmark
// to get as close as possible to
static void BM_utf8_compute_byte_length_long_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::ascii_impl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_strlen);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_byte_length_long_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_byte_length_long_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_long_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_long_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_simd_batching);

//------------------------------------------------------------------------------
//                                   EXTRA LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_byte_length_xlong_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_naive);

//------------------------------------STRLEN------------------------------------

// The results of this will be wrong, but we still want to use it as a benchmark
// to get as close as possible to
static void BM_utf8_compute_byte_length_xlong_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::ascii_impl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_strlen);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_byte_length_xlong_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_byte_length_xlong_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_xlong_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_xlong_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_simd_batching);

//------------------------------------------------------------------------------
//                                     MIXED
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_compute_byte_length_mixed_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_naive);

//------------------------------------STRLEN------------------------------------

// The results of this will be wrong, but we still want to use it as a benchmark
// to get as close as possible to
static void BM_utf8_compute_byte_length_mixed_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::ascii_impl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_strlen);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_compute_byte_length_mixed_wstring_convert(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_wstring_convert(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_wstring_convert);

//----------------------------------BYTE JUMP-----------------------------------

static void BM_utf8_compute_byte_length_mixed_byte_jump(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_byte_jump(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_byte_jump);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_mixed_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_utf8_compute_byte_length_mixed_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );

    for(auto _ : state)
    {
        // generate
        std::size_t dummy = 0;
        const char* s = deus_perf_util::get_next_rand_dyn_str(dummy);

        // call
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;
        deus::utf8_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_simd_batching);
