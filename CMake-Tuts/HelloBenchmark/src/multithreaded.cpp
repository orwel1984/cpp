#include <benchmark/benchmark.h>
#include <algorithm>
#include <execution>
#include <limits>
#include <random>
#include <vector>
#include <iostream>

using value_type = int;
static std::vector<value_type> v;

static void generate_data(size_t size)
{
  auto randomNumberBetween = [](int low, int high)
  {
      auto randomFunc = [distribution_ = std::uniform_int_distribution<int>(low, high), 
                        random_engine_ = std::mt19937{ std::random_device{}() }]() mutable
      {
          return distribution_(random_engine_);
      };
      return randomFunc;
  };

    // generate
    // v.reserve(size);
    v = std::vector<value_type>(size);
    std::generate(v.begin(), v.end(), randomNumberBetween(1,100000000));
}

void output()
{
  for(int i=0; i<8; i++){
    std::cout<<"\n"<<i<<":"<<v[i];
  }
}

void initVector(size_t size){
  generate_data(size);
}

static void Setup(const benchmark::State& state) {
  initVector(state.range(0));
}

static void Teardown(const benchmark::State& state) { }

void sequential(){
  std::sort(v.begin(), v.end());  
}

// void parallel(){
//   std::for_each(std::execution::par,v.begin(), v.end(),[](double& x){ initVector(); ++x; });
// }

// Benchmark: sequential()
static void BM_Sequential(benchmark::State& state) {
  state.PauseTiming();
  Setup(state);
  state.ResumeTiming();
  for (auto _ : state)
    sequential();
  
  //benchmark::DoNotOptimize(v);
  int bytes = state.range(0)*sizeof(value_type);
  state.SetBytesProcessed( long(state.iterations())* long(bytes));
  state.SetLabel(std::to_string(bytes/1024) + "kb");

}

// BENCHMARK(BM_Sequential)->Arg(1024)->Arg(32*1024)->Arg(640*1024)->Setup(Setup)->Teardown(Teardown);
BENCHMARK(BM_Sequential)->RangeMultiplier(2)->Range(8, 8<<10)
                        ;//->Setup(Setup)->Teardown(Teardown);

;

// // Benchmark: parallel()
// static void BM_Parallel(benchmark::State& state) {
//   for (auto _ : state)
//     parallel();
// }
// BENCHMARK(BM_Parallel);


BENCHMARK_MAIN();