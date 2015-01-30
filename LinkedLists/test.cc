#include <iostream>
#include <memory>

#include "list.h"

int main() {
  using L = List<int>;
  auto list = std::make_shared<L>(4, std::make_shared<L>(5));
  Append(list, 6);
  Append(list, 7);
  list = Remove(list, 6);
  list = Remove(list, 4);
  list = Insert(list, 6, 1);
  list = Insert(list, 10, 10);
  ForEach(list, [](int x) { std::cout << x << '\n'; });
  std::cout << "Length: " << Length(list) << '\n';

  int sum, product;
  std::tie(sum, product) = Fold(list, [](int x, std::tuple<int, int> acc) {
    return std::make_tuple(x + std::get<0>(acc), x * std::get<1>(acc));
  }, std::make_tuple(0, 1));
  std::cout << "Sum: " << sum << '\n';
  std::cout << "Product: " << product << '\n';
}
