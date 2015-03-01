#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename Container = std::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
class StlHeap {
 public:
  using value_type = T;
  using container_type = Container;
  using reference = T&;
  using const_reference = const T&;
  using size_type = typename Container::size_type;
  // Constructors
  StlHeap(const Compare& cmp, const Container& data)
      : cmp_{cmp}, data_{data} {
    makeHeap();
  }
  template <typename InputIterator>
  StlHeap(InputIterator first, InputIterator last,
          const Compare& cmp, const Container& data)
      : cmp_{cmp}, data_{data} {
    data_.insert(first, last);
    makeHeap();
  }
  explicit StlHeap(const Compare& cmp = Compare(),
                   Container&& data = Container())
      : cmp_{cmp}, data_{std::move(data)} {
    makeHeap();
  }
  template <typename InputIterator>
  StlHeap(InputIterator first, InputIterator last, const Compare& cmp,
          Container&& data = Container()) : cmp_{cmp}, data_{std::move(data)} {
    data_.insert(first, last);
    makeHeap();
  }
  // Methods
  auto size() const noexcept -> size_type {
    return data_.size();
  }
  auto empty() const noexcept -> bool {
    return size() == 0;
  }
  auto top() const noexcept -> const_reference {
    assert(!empty());
    return data_[0];
  }
  auto push(const_reference ref) -> void {
    data_.push_back(ref);
    heapify();
  }
  auto push(value_type&& v) -> void {
    data_.push_back(std::move(v));
    heapify();
  }
  template <typename... Args>
  auto emplace(Args&&... args) -> void {
    data_.emplace_back(std::forward<Args>(args)...);
    heapify();
  }
  auto pop() -> void {
    assert(!empty());
    std::pop_heap(std::begin(data_), std::end(data_), cmp_);
    data_.pop_back();
  }
  auto sorted() const -> container_type {
    container_type res(data_);
    std::sort_heap(std::begin(res), std::end(res), cmp_);
    return res;
  }

 private:
  // Helper functions
  auto makeHeap() noexcept -> void {
    std::make_heap(std::begin(data_), std::end(data_), cmp_);
  }
  auto heapify() noexcept -> void {
    std::push_heap(std::begin(data_), std::end(data_), cmp_);
  }
  // Members
  const Compare& cmp_;
  Container data_;
};
