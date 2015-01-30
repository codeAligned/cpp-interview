#include <cassert>
#include <iostream>
#include <memory>

#include "list.h"

int main() {
  using L = List<int>;
  auto list = MakeList(4, MakeList(5));
  Append(list, 6);
  Append(list, 7);
  list = Remove(list, 6);
  list = Remove(list, 4);
  list = Insert(list, 6, 1);
  list = Insert(list, 10, 10);
  ForEach(list, [](int x) { std::cout << x << ','; });
  std::cout << '\n';
  std::cout << "Length: " << Length(list) << '\n';
  auto lsquared = Map(list, [](int x) { return x * x; });
  ForEach(lsquared, [](int x) { std::cout << x << ','; });
  std::cout << '\n';

  int sum, product;
  std::tie(sum, product) = Fold(list, [](int x, std::tuple<int, int> acc) {
    return std::make_tuple(x + std::get<0>(acc), x * std::get<1>(acc));
  }, std::make_tuple(0, 1));
  std::cout << "Sum: " << sum << '\n';
  std::cout << "Product: " << product << '\n';

  // Test problem 2.1: RemoveDuplicates
  std::cout << "--- Problem 2.1 ---\n";
  auto l = MakeList(1, MakeList(2, MakeList(1)));
  l = RemoveDuplicates(l);
  ForEach(l, [](int x) { std::cout << x << '\n'; });
  
  // Test problem 2.2: NthToLast
  std::cout << "--- Problem 2.2 ---\n";
  auto l2 = MakeList(
      5, MakeList(4, MakeList(3, MakeList(2, MakeList(1, MakeList(0))))));
  for (int i = 0; i <= 5; ++i) {
    assert(i == NthToLast(l2, i)->data());
  }
  std::cout << "Okay!\n";

  // Test problem 2.3: delete in the middle given only access to the element
  std::cout << "--- Problem 2.3 ---\n";
  auto elem = MakeList(4, MakeList(5, MakeList(6)));
  auto l3 = MakeList(1, MakeList(2, MakeList(3, elem)));
  ForEach(l3, [](int x) { std::cout << x << ','; });
  std::cout << '\n';
  RemoveInPlace(elem);
  ForEach(l3, [](int x) { std::cout << x << ','; });
  std::cout << '\n';

}
