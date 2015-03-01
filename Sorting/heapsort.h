#pragma once

#include <algorithm>

template <typename RandomAccessIterator>
auto StlHeapSort(RandomAccessIterator first, RandomAccessIterator last) -> void {
  std::make_heap(first, last);
  std::sort_heap(first, last);
}
