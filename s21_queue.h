#ifndef _S21_QUEUE_H_
#define _S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>

class s21_queue {
  Container container_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  s21_queue() = default;

  s21_queue(const s21_queue& other) : container_(other.container_) {}

  s21_queue(std::initializer_list<value_type> const& items)
      : container_(items) {}

  s21_queue(s21_queue&& other) noexcept
      : container_(std::move(other.container_)) {}

  void push(const_reference tail) { container_.push_back(tail); }

  void pop() { container_.pop_front(); }

  size_type size() const { return container_.size(); }
  bool empty() const { return container_.empty(); }

  ~s21_queue() = default;

  s21_queue& operator=(s21_queue&& other) noexcept {
    if (this != &other) {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  reference front() { return container_.front(); }
  const_reference front() const { return container_.front(); }
  reference back() { return container_.back(); }
  const_reference back() const { return container_.back(); }

  void swap(s21_queue& other) noexcept { container_.swap(other.container_); }

};  // s21_queue
}  // namespace s21
#endif  // S21_QUEUE_H_
