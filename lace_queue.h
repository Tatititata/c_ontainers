#ifndef _lace_QUEUE_H_
#define _lace_QUEUE_H_
#include <iostream>
#include <list>
#include <stdexcept>

// #include "lace_list.h"

namespace lace {

template <class T, class Container = std::list<T>>

class queue {
  Container container_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() = default;

  queue(const queue& other) : container_(other.container_) {}

  queue(std::initializer_list<value_type> const& items) : container_(items) {}

  queue(queue&& other) noexcept : container_(std::move(other.container_)) {}

  void push(const_reference tail) { container_.push_back(tail); }

  void pop() { container_.pop_front(); }

  size_type size() const { return container_.size(); }
  bool empty() const { return container_.empty(); }

  ~queue() = default;

  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  reference front() { return container_.front(); }
  const_reference front() const { return container_.front(); }
  reference back() { return container_.back(); }
  const_reference back() const { return container_.back(); }

  void swap(queue& other) noexcept { container_.swap(other.container_); }

};  // queue
}  // namespace lace
#endif  // queue_H_
