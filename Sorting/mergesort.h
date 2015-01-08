#pragma once

#include <algorithm>
#include <iterator>

template <typename ForwardIterator>
auto Merge(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
    -> void {
  const auto dist = std::distance(first, last);
  auto v = std::vector<typename ForwardIterator::value_type>(dist);
  auto left = first, right = middle;
  std::generate(std::begin(v), std::end(v), [&]() {
    if (left >= middle || (right < last && *left > *right)) {
      return *right++;
    }
    return *left++;
  });
  std::copy(std::begin(v), std::end(v), first);
}

template <typename ForwardIterator>
auto MergeSort(ForwardIterator first, ForwardIterator last) -> void {
  const auto dist = std::distance(first, last);
  if (dist > 1) {
    const auto middle = first + dist / 2;
    MergeSort(first, middle);
    MergeSort(middle, last);
    Merge(first, middle, last);
  }
}
