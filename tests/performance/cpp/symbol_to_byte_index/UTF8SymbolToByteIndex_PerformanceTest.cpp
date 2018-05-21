#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                     SHORT
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_symbol_to_byte_index_short_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_views(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kShort
    );
    for(auto _ : state)
    {
        const deus::UnicodeView& view =
            deus_perf_util::get_next_rand_dyn_view();

        // call
        deus::utf8_inl::symbol_to_byte_index_naive(
            view,
            view.length() - 1
        );
    }
}
BENCHMARK(BM_utf8_symbol_to_byte_index_short_naive);

//------------------------------------------------------------------------------
//                                     MEDIUM
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_symbol_to_byte_index_medium_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_views(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMedium
    );
    for(auto _ : state)
    {
        const deus::UnicodeView& view =
            deus_perf_util::get_next_rand_dyn_view();

        // call
        deus::utf8_inl::symbol_to_byte_index_naive(
            view,
            view.length() - 1
        );
    }
}
BENCHMARK(BM_utf8_symbol_to_byte_index_medium_naive);

//------------------------------------------------------------------------------
//                                      LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_symbol_to_byte_index_long_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_views(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kLong
    );
    for(auto _ : state)
    {
        const deus::UnicodeView& view =
            deus_perf_util::get_next_rand_dyn_view();

        // call
        deus::utf8_inl::symbol_to_byte_index_naive(
            view,
            view.length() - 1
        );
    }
}
BENCHMARK(BM_utf8_symbol_to_byte_index_long_naive);

//------------------------------------------------------------------------------
//                                   EXTRA LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_symbol_to_byte_index_xlong_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_views(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kExtraLong
    );
    for(auto _ : state)
    {
        const deus::UnicodeView& view =
            deus_perf_util::get_next_rand_dyn_view();

        // call
        deus::utf8_inl::symbol_to_byte_index_naive(
            view,
            view.length() - 1
        );
    }
}
BENCHMARK(BM_utf8_symbol_to_byte_index_xlong_naive);

//------------------------------------------------------------------------------
//                                     MIXED
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_symbol_to_byte_index_mixed_naive(benchmark::State& state)
{
    deus_perf_util::gen_rand_dyn_views(
        deus::Encoding::kUTF8,
        deus_perf_util::StringSize::kMixed
    );
    for(auto _ : state)
    {
        const deus::UnicodeView& view =
            deus_perf_util::get_next_rand_dyn_view();

        // call
        deus::utf8_inl::symbol_to_byte_index_naive(
            view,
            view.length() - 1
        );
    }
}
BENCHMARK(BM_utf8_symbol_to_byte_index_mixed_naive);
