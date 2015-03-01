#pragma once

#include <cassert>
#include <ostream>
#include <tuple>
#include <vector>

// For simplicity, this uses a std::vector as underlying data structure. In
// order to optimise for data access, one could use a std::array (or
// std::vector) of a fixed capacity as a ring-buffer. Then one would have to do
// a bit more arithmetic to figure out positions but in exchange one would get
// O(1) pop().

template <typename T>
class Heap {
 public:
  Heap() = default;
  explicit Heap(std::vector<T> v) : data_{v} { makeHeap(); }

  auto size() const noexcept -> std::size_t { return data_.size(); }

  auto empty() const noexcept -> bool { return size() == 0; }

  auto top() const noexcept -> const T & {
    assert(!empty());
    return data_[0];
  }

  auto pop() noexcept -> void {
    assert(!empty());
    std::swap(data_[0], data_[size() - 1u]);
    data_.pop_back();
    if (size() > 0) {
      heapify(0);
    }
  }

  auto push(T x) -> void {
    data_.push_back(x);  // can throw when realloc fails
    auto pos = size() - 1u;
    while (pos > 0) {  // not yet at root
      auto par = parent(pos);
      if (data_[pos] < data_[par]) {  // heap-condition violated
        std::swap(data_[pos], data_[par]);
        pos = par;
      } else {
        break;
      }
    }
  }

  auto isHeap() const noexcept -> bool { return isPartialHeap(0); }

  template <typename U>
  friend auto operator<<(std::ostream&, const Heap<U>&) -> std::ostream&;

 private:
  // helper functions
  auto parent(std::size_t pos) const noexcept -> std::size_t {
    return (pos - 1u) / 2u;
  }

  auto children(std::size_t pos) const noexcept
      -> std::tuple<std::size_t, std::size_t> {
    return std::make_tuple(2 * pos + 1, 2 * pos + 2);
  }

  auto isLeaf(std::size_t pos) const noexcept -> bool {
    return pos > (size() - 2u) / 2u;
  }

  auto isPartialHeap(std::size_t pos) const noexcept -> bool {
    if (isLeaf(pos)) {
      return true;  // a leaf or an empty structure is a heap
    }
    std::size_t lc, rc;
    std::tie(lc, rc) = children(pos);
    if (data_[pos] > data_[lc] ||
        (rc < data_.size() && data_[pos] > data_[rc])) {
      return false;
    }
    return isPartialHeap(lc) && isPartialHeap(rc);
  }

  auto heapify(std::size_t pos) noexcept -> void {
    if (isLeaf(pos) || isPartialHeap(pos)) {
      return;
    }
    std::size_t lc, rc;
    std::tie(lc, rc) = children(pos);
    auto branch = lc;
    if (rc < size() && data_[rc] < data_[lc]) {
      branch = rc;
    }
    if (data_[branch] < data_[pos]) {  // heap broken
      std::swap(data_[branch], data_[pos]);
      heapify(branch);
    }
  }

  auto makeHeap() noexcept -> void {
    for (auto i = (size() - 2u) / 2u + 1; i > 0; --i) {
      heapify(i - 1);
    }
  }
  // members
  std::vector<T> data_;
};

template <typename T>
auto operator<<(std::ostream& os, const Heap<T>& heap) -> std::ostream & {
  for (const auto& elem : heap.data_) {
    os << elem << ' ';
  }
  return os;
}
