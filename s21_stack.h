#include <deque>

#include "s21_list.h"
#include "s21_vector.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class stack {
 public:
  // Member functions
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // Member functions
  stack() {}
  // noexcept?
  stack(std::initializer_list<value_type> const &items) : container_{items} {}
  // delete?
  stack(const stack &s) = default;
  stack(stack &&s) = default;
  ~stack() = default;
  stack &operator=(stack &&s) = default;
  stack &operator=(const stack &s) = default;

  // Element access
  const_reference top() const { return container_.back(); }
  reference top() { return container_.back(); }

  // Capacity
  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }

  // Modifiers
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    (container_.push_back(args), ...);
  }

  void swap(stack &other) { container_.swap(other.container_); }

 private:
  Container container_;
};
}  // namespace s21
