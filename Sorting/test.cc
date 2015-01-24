#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "mergesort.h"

template <typename Container>
auto Print(const Container& c) -> void {
  std::copy(
      std::begin(c), std::end(c),
      std::ostream_iterator<typename Container::value_type>(std::cout, ","));
  std::cout << '\n';
}

template <typename Func>
auto Time(const Func& f) -> unsigned {
  const auto start = std::chrono::steady_clock::now();
  f();
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - start).count();
}

int main() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  auto fillRandom = [&](std::vector<double>& v) {
    std::generate(std::begin(v), std::end(v), [&]() { return dist(rd); });
  };

  auto v = std::vector<double>(10000000);
  fillRandom(v);
  auto w = v;
  const auto timeStd = Time([&]() { std::sort(std::begin(v), std::end(v)); });
  const auto timeMrg = Time([&]() { MergeSort(std::begin(w), std::end(w)); });
  std::cout << "std::sort: " << timeStd << "ms\n";
  std::cout << "MergeSort: " << timeMrg << "ms\n";

}
