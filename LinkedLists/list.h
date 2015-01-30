#pragma once

#include <memory>
#include <utility>

template <typename T>
class List {
 public:
  List(T data, std::shared_ptr<List<T>> tail)
      : data_{std::move(data)}, tail_{tail} {}
  explicit List(T data) : List{std::move(data), nullptr} {}

  auto data() const -> T { return data_; }

  template <typename PT>
  auto set_data(PT&& data) -> void {
    data_ = data;
  }

  auto tail() -> std::shared_ptr<List<T>> { return tail_; }

  auto set_tail(std::shared_ptr<List<T>> tail) -> void { tail_ = tail; }

 private:
  T data_;
  std::shared_ptr<List<T>> tail_;
};

template <typename T>
using ListPtr = std::shared_ptr<List<T>>;

template <typename T>
auto EmptyList() -> ListPtr<T> {
  return ListPtr<T>{nullptr};
}

template <typename T, typename... Ts>
auto MakeList(T data, Ts... other) -> ListPtr<T> {
  return std::make_shared<List<T>>(data, other...);
}

template <typename T, typename FN>
auto ForEach(ListPtr<T> head, FN f) -> void {
  if (head != nullptr) {
    f(head->data());
    ForEach(head->tail(), f);
  }
}

template <typename T>
auto Append(ListPtr<T> head, T data) -> ListPtr<T> {
  if (head == nullptr) {
    return MakeList(data);
  }
  head->set_tail(Append(head->tail(), data));
  return head;
}

template <typename T>
auto Remove(ListPtr<T> head, T data) -> ListPtr<T> {
  if (head->data() == data) {
    return head->tail();
  }
  if (head->tail() != nullptr) {
    head->set_tail(Remove(head->tail(), data));
  }
  return head;
}

template <typename T>
auto Insert(ListPtr<T> head, T data, std::size_t position) -> ListPtr<T> {
  if (head == nullptr || position == 0) {
    return MakeList(data, head);
  }
  head->set_tail(Insert(head->tail(), data, position - 1));
  return head;
}

template <typename T>
auto Length(ListPtr<T> head) -> std::size_t {
  if (head == nullptr) {
    return 0;
  }
  return 1 + Length(head->tail());
}

// fold :: [a] -> (a -> b -> b) -> b -> b
template <typename T, typename RT, typename FN>
auto Fold(ListPtr<T> head, FN f, RT acc) -> RT {
  if (head == nullptr) {
    return acc;
  }
  return Fold(head->tail(), f, f(head->data(), acc));
}

// filter :: [a] -> (a -> bool) -> [a]
template <typename T, typename PRED>
auto Filter(ListPtr<T> head, PRED p) -> ListPtr<T> {
  return Fold(head, [&](T x, ListPtr<T> acc) {
    if (p(x)) {
      Append(acc, x);
    }
    return acc;
  }, EmptyList<T>());
}

template <typename T>
auto RemoveDuplicates(ListPtr<T> head) -> ListPtr<T> {
  if (head != nullptr) {
    head->set_tail(
        Filter(head->tail(), [&](T x) { return x == head->data(); }));
    head->set_tail(RemoveDuplicates(head->tail()));
  }
  return head;
}

template <typename T>
auto NthToLast(ListPtr<T> head, std::size_t n) -> ListPtr<T> {
  // might want to check that n is less than the size of the list
  if (head == nullptr) {
    return head;  // or error (e.g. return type could be Maybe<ListPtr<T>>)
  }
  ListPtr<T> ahead = head, behind = head;
  for (auto i = 0u; i <= n; ++i) {
    ahead = ahead->tail();
  }
  while (ahead != nullptr) {
    ahead = ahead->tail();
    behind = behind->tail();
  }
  return behind;
}

template <typename T>
auto RemoveInPlace(ListPtr<T> elem) -> void {
  if (elem->tail() == nullptr) {
    elem.reset();
  } else {
    elem->set_data(elem->tail()->data());
    elem->set_tail(elem->tail()->tail());
  }
}
