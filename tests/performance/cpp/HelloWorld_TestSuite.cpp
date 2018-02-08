#include <benchmark/benchmark.h>


static void BM_HelloWorld(benchmark::State& state)
{
    for(auto _ : state)
    {
        std::string empty_string("Hello world");
    }
}
BENCHMARK(BM_HelloWorld);

