#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

#include <deus/unicode_view_impl/UTF8Impl.hpp>


//------------------------------------------------------------------------------
//                                     SHORT
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_byte_to_symbol_index_short_naive(benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_naive(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_short_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_byte_to_symbol_index_short_wstring_convert(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_wstring_convert(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_short_wstring_convert);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_byte_to_symbol_index_short_word_batching(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_word_batching(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_short_word_batching);

//------------------------------------------------------------------------------
//                                     MEDIUM
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_byte_to_symbol_index_medium_naive(benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_naive(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_medium_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_byte_to_symbol_index_medium_wstring_convert(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_wstring_convert(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_medium_wstring_convert);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_byte_to_symbol_index_medium_word_batching(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_word_batching(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_medium_word_batching);

//------------------------------------------------------------------------------
//                                      LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_byte_to_symbol_index_long_naive(benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_naive(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_long_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_byte_to_symbol_index_long_wstring_convert(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_wstring_convert(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_long_wstring_convert);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_byte_to_symbol_index_long_word_batching(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_word_batching(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_long_word_batching);

//------------------------------------------------------------------------------
//                                   EXTRA LONG
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_byte_to_symbol_index_xlong_naive(benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_naive(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_xlong_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_byte_to_symbol_index_xlong_wstring_convert(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_wstring_convert(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_xlong_wstring_convert);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_byte_to_symbol_index_xlong_word_batching(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_word_batching(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_xlong_word_batching);

//------------------------------------------------------------------------------
//                                     MIXED
//------------------------------------------------------------------------------

//------------------------------------NAIVE-------------------------------------

static void BM_utf8_byte_to_symbol_index_mixed_naive(benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_naive(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_mixed_naive);

//-------------------------------WSTRING CONVERT--------------------------------

static void BM_utf8_byte_to_symbol_index_mixed_wstring_convert(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_wstring_convert(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_mixed_wstring_convert);

//--------------------------------WORD BATCHING---------------------------------

static void BM_utf8_byte_to_symbol_index_mixed_word_batching(
        benchmark::State& state)
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
        deus::utf8_inl::byte_to_symbol_index_word_batching(
            view,
            view.c_str_length() - 1
        );
    }
}
BENCHMARK(BM_utf8_byte_to_symbol_index_mixed_word_batching);
