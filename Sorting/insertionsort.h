#pragma once

template <typename Container>
auto InsertionSort(Container& c) -> void {
  for (auto i = 1u; i < c.size(); ++i) {
    auto cur = c[i];
    auto k = i;
    while (k > 0 && c[k - 1] > cur) {
      c[k] = c[k - 1];
      --k;
    }
    c[k] = cur;
  }
}
