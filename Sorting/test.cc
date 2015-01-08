#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "sort.h"

template <typename Container>
auto Print(const Container& c) -> void {
  std::copy(
      std::begin(c), std::end(c),
      std::ostream_iterator<typename Container::value_type>(std::cout, ","));
  std::cout << '\n';
}

int main() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  auto v = std::vector<double>(10000000);
  auto fillRandom = [&]() {
    std::generate(std::begin(v), std::end(v), [&]() { return dist(rd); });
  };

  auto now = std::chrono::steady_clock::now;

  auto timedTest = [&]() {
    fillRandom();
    const auto start = now();
    MergeSort(std::begin(v), std::end(v));
    return std::chrono::duration_cast<std::chrono::milliseconds>(now() - start)
        .count();
  };

  std::cout << timedTest() << "ms\n";
}
