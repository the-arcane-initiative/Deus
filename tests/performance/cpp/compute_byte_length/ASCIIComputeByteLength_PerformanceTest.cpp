#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

#include <deus/unicode_view_impl/ASCIIImpl.hpp>

//------------------------------------------------------------------------------
//                                     SHORT
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_ascii_compute_byte_length_short_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_short_naive);

//------------------------------------STRLEN------------------------------------

static void BM_ascii_compute_byte_length_short_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
BENCHMARK(BM_ascii_compute_byte_length_short_strlen);

//----------------------------------STD STRING----------------------------------

static void BM_ascii_compute_byte_length_short_std_string(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_short_std_string);

//--------------------------------WORD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_short_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_short_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_short_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_short_simd_batching);

//------------------------------------------------------------------------------
//                                     MEDIUM
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_ascii_compute_byte_length_medium_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_medium_naive);

//------------------------------------STRLEN------------------------------------

static void BM_ascii_compute_byte_length_medium_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
BENCHMARK(BM_ascii_compute_byte_length_medium_strlen);

//----------------------------------STD STRING----------------------------------

static void BM_ascii_compute_byte_length_medium_std_string(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_medium_std_string);

//--------------------------------WORD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_medium_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_medium_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_medium_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_medium_simd_batching);

//------------------------------------------------------------------------------
//                                      LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_ascii_compute_byte_length_long_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_long_naive);

//------------------------------------STRLEN------------------------------------

static void BM_ascii_compute_byte_length_long_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
BENCHMARK(BM_ascii_compute_byte_length_long_strlen);

//----------------------------------STD STRING----------------------------------

static void BM_ascii_compute_byte_length_long_std_string(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_long_std_string);

//--------------------------------WORD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_long_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_long_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_long_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_long_simd_batching);

//------------------------------------------------------------------------------
//                                   EXTRA LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_ascii_compute_byte_length_xlong_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_xlong_naive);

//------------------------------------STRLEN------------------------------------

static void BM_ascii_compute_byte_length_xlong_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
BENCHMARK(BM_ascii_compute_byte_length_xlong_strlen);

//----------------------------------STD STRING----------------------------------

static void BM_ascii_compute_byte_length_xlong_std_string(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_xlong_std_string);

//--------------------------------WORD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_xlong_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_xlong_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_xlong_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_xlong_simd_batching);

//------------------------------------------------------------------------------
//                                     MIXED
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_ascii_compute_byte_length_mixed_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_mixed_naive);

//------------------------------------STRLEN------------------------------------

static void BM_ascii_compute_byte_length_mixed_strlen(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
BENCHMARK(BM_ascii_compute_byte_length_mixed_strlen);

//----------------------------------STD STRING----------------------------------

static void BM_ascii_compute_byte_length_mixed_std_string(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_mixed_std_string);

//--------------------------------WORD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_mixed_word_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_mixed_word_batching);

//--------------------------------SIMD BATCHING---------------------------------

static void BM_ascii_compute_byte_length_mixed_simd_batching(
        benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_strs(
        deus::Encoding::kASCII,
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
        deus::ascii_impl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );
    }
}
BENCHMARK(BM_ascii_compute_byte_length_mixed_simd_batching);
