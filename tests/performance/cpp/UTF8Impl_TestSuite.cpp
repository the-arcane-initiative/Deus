#include <benchmark/benchmark.h>

#include <cstring>

// TODO:
#define protected public
#define private public

#include <deus/unicode_view_impl/UTF8Impl.hpp>


static void BM_compute_symbol_length(benchmark::State& state)
{
    for(auto _ : state)
    {
        deus::UnicodeView::UTF8Impl s(12, deus::NULL_POS, "Hello world!");
        s.compute_symbol_length();
    }
}
BENCHMARK(BM_compute_symbol_length);

static void BM_strlen(benchmark::State& state)
{
    for(auto _ : state)
    {
        const char* s = "Hello world!";
        std::size_t i = strlen(s);
    }
}
BENCHMARK(BM_strlen);
