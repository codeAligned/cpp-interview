#include "heap.h"

#include <iostream>

int main() {
  auto h = Heap<unsigned>{};
  h.push(4);
  h.push(6);
  h.push(8);
  h.push(3);
  std::cout << "  : ";
  std::cout << h << '\n';
  std::cout << h.top() << " : ";
  h.pop();
  std::cout << h << '\n';
  std::cout << h.top() << " : ";
  h.pop();
  std::cout << h << '\n';
  std::cout << h.top() << " : ";
  h.pop();
  std::cout << h << '\n';
  std::cout << h.top() << " : ";
  h.pop();
  std::cout << h << '\n';

  std::cout << h.isHeap() << '\n';
  std::cout << h.empty() << '\n';
  std::cout << h.size() << '\n';

  auto v = std::vector<int>{-3, 1, 4, -2, 7, 9};
  auto h2 = Heap<int>{v};
  std::cout << h2 << '\n';
}
