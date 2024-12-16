#include <benchmark/benchmark.h>
#include <algorithm>
#include <execution>
#include <ctime>

// create a vector of 500 elements
// constexpr auto size = 1000000u;
// std::vector<double> v(size);

// void initVector(){
//   // for(int i=0; i<10; i++){
//   //   ;
//   // }
//   // std::srand(unsigned(std::time(nullptr)));
//   // std::generate(v.begin(), v.end(), std::rand);
// }

// void sequential(){
//   std::for_each(v.begin(), v.end(),[](double& x){ initVector(); ++x; });
// }

// void parallel(){
//   //std::for_each(std::execution::par,v.begin(), v.end(),[](double& x){ initVector(); ++x; });
//   std::for_each(std::execution::unseq,v.begin(), v.end(),[](double& x){ initVector(); ++x; });
// }

// // Benchmark: sequential()
// static void BM_Sequential(benchmark::State& state) {
//   for (auto _ : state)
//     sequential();
// }
// BENCHMARK(BM_Sequential);

// // Benchmark: parallel()
// static void BM_Parallel(benchmark::State& state) {
//   for (auto _ : state)
//     parallel();
// }
// BENCHMARK(BM_Parallel);

// Benchmark a function which creates empty strings
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
BENCHMARK(BM_StringCreation);

// Benchmark a function which copies strings
static void BM_StringCopy(benchmark::State& state) {
  for (auto _ : state)
    std::string copy("hello");
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();