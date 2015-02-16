#include <iostream>
#include <vector>
#include <queue>

template <typename T>
auto merge(const std::vector<std::vector<T>>& lists) -> std::vector<T> {
  auto res = std::vector<T>{};
  auto pos = std::vector<std::size_t>(lists.size(), 0u);
  auto less = [&](const std::size_t& x, const std::size_t& y) {
    return lists[x][pos[x]] >= lists[y][pos[y]];  // priority_queue uses max heap...
  };
  auto pq = std::priority_queue<std::size_t, std::vector<std::size_t>, decltype(less)>(less);
  for (auto i = 0u; i < lists.size(); ++i) {
    pq.push(i);
  }
  while (!pq.empty()) {
    auto l = pq.top();
    auto& p = pos[l];
    pq.pop();
    res.push_back(lists[l][p]);
    ++p;
    if (p < lists[l].size()) {
      pq.push(l);
    }
  }
  return res;
}

int main() {
  auto lists = std::vector<std::vector<unsigned>>{
    {3, 6, 9},
    {4, 7, 8},
    {1, 2, 5}
  };
  auto res = merge(lists);
  for (const auto& elem : res) {
    std::cout << elem << '\n';
  }
}
