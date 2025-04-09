#ifndef array_H_
#define array_H_
#include <iostream>
#include <stdexcept>

namespace lace {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array() {
    for (size_t i = 0; i < N; ++i) {
      new (&data()[i]) value_type();
    }
  }

  array(std::initializer_list<value_type> const& items) {
    auto it = items.begin();
    size_t i = 0;
    try {
      for (; i < N && it != items.end(); ++i, ++it) {
        new (&data()[i]) value_type(std::move(*it));
      }

      for (; i < N; ++i) {
        new (&data()[i]) value_type(std::move(*items.begin()));
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) data()[j].~value_type();
      throw;
    }
  }

  ~array() {
    for (size_t i = 0; i < N; ++i) {
      data()[i].~value_type();
    }
  }

  array(const array& other) {
    size_t i = 0;
    try {
      for (; i < N; ++i) {
        new (&data()[i]) value_type(other.data()[i]);
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) data()[j].~value_type();
      throw;
    }
  }

  array(array&& other) noexcept {
    for (size_t i = 0; i < N; ++i) {
      new (&data()[i]) value_type(std::move(other.data()[i]));
    }
  }

  array& operator=(array other) noexcept {
    swap(other);
    return *this;
  }

  void swap(array& other) noexcept {
    for (size_type i = 0; i < N; ++i) std::swap(data()[i], other.data()[i]);
  }

  reference at(size_type index) {
    if (index >= N) throw std::out_of_range("Index out of range");
    return data()[index];
  }

  const_reference front() const {
    if (N == 0) throw std::out_of_range("Array is empty");
    return data()[0];
  }

  const_reference back() const {
    if (N == 0) throw std::out_of_range("Array is empty");
    return data()[N - 1];
  }

  const_reference at(size_type index) const {
    if (index >= N) throw std::out_of_range("Index out of range");
    return data()[index];
  }

  iterator begin() noexcept { return data(); }
  const_iterator begin() const noexcept { return data(); }
  iterator end() noexcept { return data() + N; }
  const_iterator end() const noexcept { return data() + N; }

  reference operator[](size_type index) { return data()[index]; }
  const_reference operator[](size_type index) const { return data()[index]; }

  const_reference front() {
    if (N == 0) throw std::out_of_range("Zero size array has no elements");
    return data()[0];
  }
  const_reference back() {
    if (N == 0) throw std::out_of_range("Zero size array has no elements");
    return data()[N - 1];
  }

  constexpr size_type size() const noexcept { return N; }
  constexpr size_type max_size() const noexcept { return N; }

  constexpr bool empty() const noexcept { return N == 0; }

  void fill(const_reference value) {
    for (size_t i = 0; i < N; ++i) {
      data()[i] = value;
    }
  }
  iterator data() { return reinterpret_cast<iterator>(storage_); }
  const_iterator data() const {
    return reinterpret_cast<const_iterator>(storage_);
  }

 private:
  alignas(alignof(value_type)) char storage_[sizeof(value_type) * N];

};  // class array
}  // namespace lace
#endif  // array_H_
