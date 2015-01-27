#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

#include "mergesort.h"
#include "quicksort.h"

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

  auto now = std::chrono::high_resolution_clock::now;
  auto s = now();
  auto time = [&](decltype(s) start) -> unsigned {
    return std::chrono::duration_cast<std::chrono::milliseconds>(now() - start)
      .count();
  };

  auto v = std::vector<double>(10000000);
  fillRandom(v);

  auto w = v;
  auto start = now();
  std::sort(std::begin(w), std::end(w));
  std::cout << "std::sort: " << time(start) << "ms\n";
  assert(std::is_sorted(std::begin(w), std::end(w)) && "std::sort");
  w = v;
  start = now();
  MergeSort(std::begin(w), std::end(w));
  std::cout << "MergeSort: " << time(start) << "ms\n";
  assert(std::is_sorted(std::begin(w), std::end(w)) && "MergeSort");
  w = v;
  start = now();
  QuickSort(std::begin(w), std::end(w));
  std::cout << "QuickSort: " << time(start) << "ms\n";
  assert(std::is_sorted(std::begin(w), std::end(w)) && "QuickSort");
  w = v;
  start = now();
  qsort(w);
  std::cout << "Legacy QuickSort: " << time(start) << "ms\n";
  assert(std::is_sorted(std::begin(w), std::end(w)) && "Legacy QuickSort");
}
