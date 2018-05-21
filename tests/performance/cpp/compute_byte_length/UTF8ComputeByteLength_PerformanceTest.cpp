#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

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
        deus::utf8_inl::compute_byte_length_naive(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_naive);

//------------------------------------STRLEN------------------------------------

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
        deus::utf8_inl::compute_byte_length_strlen(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_short_strlen);

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
        deus::utf8_inl::compute_byte_length_naive(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_naive);

//------------------------------------STRLEN------------------------------------

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
        deus::utf8_inl::compute_byte_length_strlen(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_medium_strlen);

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
        deus::utf8_inl::compute_byte_length_naive(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_naive);

//------------------------------------STRLEN------------------------------------

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
        deus::utf8_inl::compute_byte_length_strlen(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_long_strlen);

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
        deus::utf8_inl::compute_byte_length_naive(s, byte_length);
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
        deus::utf8_inl::compute_byte_length_strlen(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_xlong_strlen);

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
        deus::utf8_inl::compute_byte_length_naive(s, byte_length);
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
        deus::utf8_inl::compute_byte_length_strlen(s, byte_length);
    }
}
BENCHMARK(BM_utf8_compute_byte_length_mixed_strlen);
