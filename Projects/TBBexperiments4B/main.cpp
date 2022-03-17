// This program shows the basics of using TBB in C++
// By: Nick from CoffeeBeforeArch https://github.com/CoffeeBeforeArch/parallel_programming

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "tbb/parallel_invoke.h"

int main() {
  // Size of the vector
  constexpr int N = 1 << 20;

  // Create our two vectors
  std::vector<int> v1(N);
  std::vector<int> v2(N);

  // Create our random number generators
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);

  // Generate our random inputs
  std::generate(begin(v1), end(v1), [&]() { return dist(rng); });
  std::generate(begin(v2), end(v2), [&]() { return dist(rng); });

  // Profile parallel invoke
    auto start = std::chrono::system_clock::now();
    tbb::parallel_invoke([&] { std::sort(begin(v1), end(v1)); },
                       [&] { std::sort(begin(v2), end(v2)); });
    auto end = std::chrono::system_clock::now();

  // Print out the execution time
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout << duration.count() << " ms " << std::endl;

  return 0;
}

