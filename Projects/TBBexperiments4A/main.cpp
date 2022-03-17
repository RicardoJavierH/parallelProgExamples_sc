// This program serves as a baseline for the TBB example
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>


int main() {
  // Size of the vector
  constexpr int N = 1 << 20;

  // Create our two vectors
  std::vector<int> v1(N);
  std::vector<int> v2(N);

  // Create our random number generators
  std::mt19937 rng;//The Mersenne Twist method for generating pseudorandom numbers
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0,255);

  // Generate our random inputs
  std::generate(begin(v1), end(v1), [&]() { return dist(rng); });
  std::generate(begin(v2), end(v2), [&]() { return dist(rng); });

  // Profile serial invoke
    auto start = std::chrono::system_clock::now();
  std::sort(begin(v1), end(v1));
  std::sort(begin(v2), end(v2));
    auto end = std::chrono::system_clock::now();

  // Print out the execution time
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout << duration.count() << " ms " << std::endl;

  return 0;
}
