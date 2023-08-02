#include <benchmark/benchmark.h>
#include <algorithm>
#include <execution>
#include <limits>
#include <random>
#include <vector>

// create a vector of 500 elements
constexpr auto size = 1000000u;
static std::vector<double> v;

static void generate_data(size_t size)
{
    using value_type = int;
    // We use static in order to instantiate the random engine and the distribution once only.
    // It may provoke some thread-safety issues.
    static std::uniform_int_distribution<value_type> distribution(
        std::numeric_limits<value_type>::min(),
        std::numeric_limits<value_type>::max());
    static std::default_random_engine generator;

    // generate
    v.reserve(size);
    std::generate(v.begin(), v.end(), []() { return distribution(generator); });
}

void initVector(size_t size){
  generate_data(size);
}

static void DoSetup(const benchmark::State& state) {
  // first argument is size
  initVector(state.range(0));
}

static void DoTeardown(const benchmark::State& state) {
}

void sequential(){
  std::sort(v.begin(), v.end());  
  //std::for_each(v.begin(), v.end(),[](double& x){ ++x; });
}

// void parallel(){
//   std::for_each(std::execution::par,v.begin(), v.end(),[](double& x){ initVector(); ++x; });
// }

// Benchmark: sequential()
static void BM_Sequential(benchmark::State& state) {
  for (auto _ : state)
    sequential();
}
BENCHMARK(BM_Sequential)->Arg(1024)->Arg(32*1024)->Arg(64*1024)->Setup(DoSetup);

// // Benchmark: parallel()
// static void BM_Parallel(benchmark::State& state) {
//   for (auto _ : state)
//     parallel();
// }
// BENCHMARK(BM_Parallel);


BENCHMARK_MAIN();