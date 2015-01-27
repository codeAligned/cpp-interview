#pragma once

#include <algorithm>
#include <iterator>

template <typename BidirIt>
auto QuickSort(BidirIt first, BidirIt last) -> void {
  if (first == last) {
    return;
  }
  auto& pivot = *first;
  ++first;
  auto pred = [&](const typename std::iterator_traits<BidirIt>::value_type& x)
                  -> bool { return pivot > x; };
  auto mid = std::partition(first, last, pred);
  --first;
  --mid;
  if (mid != first) {
    std::swap(pivot, *mid);
  }
  QuickSort(first, mid);
  ++mid;
  QuickSort(mid, last);
}


// For reference this file also contains an implementation that doesn't use the
// STL.
template <typename Container>
auto swap(Container& c, size_t i, size_t k) -> void {
  const auto tmp = c[i];
  c[i] = c[k];
  c[k] = tmp;
}

template <typename Container>
auto _qsort(Container& c, int left, int right) -> void {
  if (left >= right) {
    return;
  }
  const auto& p = c[left];  // pivot element
  auto i = left, k = right;
  while (i < k) {
    while (i < k && c[i] <= p) {
      ++i;
    }
    while (i < k && c[k] > p) {
      --k;
    }
    swap(c, i, k);
  }
  if (c[i] > p) {
    --i;
  }
  swap(c, left, i);  // swap pivot element into place
  _qsort(c, left, i - 1);
  _qsort(c, i + 1, right);
}

template <typename Container>
auto qsort(Container& c) -> void {
  _qsort(c, 0, c.size() - 1);
}

