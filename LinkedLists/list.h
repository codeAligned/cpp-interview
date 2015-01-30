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

template <typename T, typename FN>
auto ForEach(std::shared_ptr<List<T>> head, FN f) -> void {
  if (head != nullptr) {
    f(head->data());
    ForEach(head->tail(), f);
  }
}

template <typename T>
auto Append(std::shared_ptr<List<T>> head, T&& data) -> void {
  if (head->tail() != nullptr) {
    Append(head->tail(), std::forward<T>(data));
  } else {
    head->set_tail(std::make_shared<List<T>>(data));
  }
}

template <typename T>
auto Remove(std::shared_ptr<List<T>> head, T&& data)
    -> std::shared_ptr<List<T>> {
  if (head->data() == data) {
    return head->tail();
  }
  if (head->tail() != nullptr) {
    head->set_tail(Remove(head->tail(), std::forward<T>(data)));
  }
  return head;
}

template <typename T>
auto Insert(std::shared_ptr<List<T>> head, T&& data, std::size_t position)
    -> std::shared_ptr<List<T>> {
  if (head == nullptr || position == 0) {
    return std::make_shared<List<T>>(std::forward<T>(data), head);
  }
  head->set_tail(Insert(head->tail(), std::forward<T>(data), position - 1));
  return head;
}

template <typename T>
auto Length(std::shared_ptr<List<T>> head) -> std::size_t {
  if (head == nullptr) {
    return 0;
  }
  return 1 + Length(head->tail());
}

// fold :: [a] -> (a -> b -> b) -> b -> b
template <typename T, typename RT, typename FN>
auto Fold(std::shared_ptr<List<T>> head, FN f, RT acc) -> RT {
  if (head == nullptr) {
    return acc;
  }
  return Fold(head->tail(), f, f(head->data(), acc));
}
