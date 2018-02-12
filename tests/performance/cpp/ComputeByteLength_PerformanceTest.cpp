#include <benchmark/benchmark.h>

#include "PerformanceTestsUtil.hpp"

// obtain access to the private components of Deus
#define protected public
#define private public

#include <deus/unicode_view_impl/ASCIIImpl.hpp>
#include <deus/unicode_view_impl/UTF8Impl.hpp>


static void BM_ascii_compute_byte_length_naive(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::ASCIIImpl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_ascii_compute_byte_length_naive);

static void BM_ascii_compute_byte_length_strlen(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::ASCIIImpl::compute_byte_length_strlen(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_ascii_compute_byte_length_strlen);

static void BM_ascii_compute_byte_length_std_string(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::ASCIIImpl::compute_byte_length_std_string(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_ascii_compute_byte_length_std_string);

static void BM_ascii_compute_byte_length_word_batching(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::ASCIIImpl::compute_byte_length_word_batching(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_ascii_compute_byte_length_word_batching);

static void BM_ascii_compute_byte_length_simd_batching(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::ASCIIImpl::compute_byte_length_simd_batching(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_ascii_compute_byte_length_simd_batching);

static void BM_utf8_compute_byte_length_naive(benchmark::State& state)
{
    deus_perf_util::clear_generators();
    for(auto _ : state)
    {
        const char* s = nullptr;
        std::size_t byte_length = 0;
        std::size_t symbol_length = 0;

        // generate
        std::size_t dummy = 0;
        deus_perf_util::gen_rand_dyn_str(&s, dummy);

        // TODO: maybe we want static strings???
        deus::UnicodeView::UTF8Impl::compute_byte_length_naive(
            s,
            byte_length,
            symbol_length
        );

        delete[] s;
    }
}
BENCHMARK(BM_utf8_compute_byte_length_naive);
