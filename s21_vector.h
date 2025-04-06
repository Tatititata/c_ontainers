#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  // Constructors & assignment operators
  vector() {}

  vector(size_type n) : size_{n}, capacity_{n} {
    data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
    size_t index = 0;
    try {
      for (; index < size_; ++index) {
        new (&data_[index]) T();
      }
    } catch (...) {
      std::destroy_n(data_, index);
      operator delete(data_);
      throw;
    }
  }

  // TODO: initializer_list
  vector(std::initializer_list<value_type> const& items)
      : size_{items.size()}, capacity_{items.size()} {
    data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
    size_t index = 0;
    try {
      // for (auto&& item : items) { // было
      //   new (&data_[index++]) value_type(std::forward<value_type>(item));
      for (const auto& item : items) {
        new (&data_[index++]) value_type(item);
      }
    } catch (...) {
      std::destroy_n(data_, index);
      operator delete(data_);
      throw;
    }
  }

  vector(const vector<T>& other) : size_(other.size_), capacity_(other.size_) {
    data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
    size_t index = 0;
    try {
      for (; index < size_; ++index) {
        new (&data_[index]) T(other.data_[index]);
      }
    } catch (...) {
      std::destroy_n(data_, index);
      operator delete(data_);
      throw;
    }
  }

  vector& operator=(const vector<T>& other) {
    vector<T> copy = other;
    // ---noexcept after this line---
    copy.swap(*this);
    return *this;
  }

  vector(vector<T>&& other) noexcept {
    data_ = std::exchange(other.data_, nullptr);
    size_ = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 0);
  }

  vector& operator=(vector<T>&& other) noexcept {
    vector<T> copy = std::move(other);
    copy.swap(*this);
    return *this;
  }

  ~vector() {
    for (size_t index = 0; index < size_; ++index) {
      data_[index].~T();
    }
    operator delete(data_);
  }

  // Element access
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; };
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("pos is out of range");
    }
    return data_[pos];
  }
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("pos is out of range");
    }
    return data_[pos];
  };

  // Iterators
  iterator begin() { return data_; }
  const_iterator begin() const { return data_; }
  const_iterator cbegin() const { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator end() const { return data_ + size_; }
  const_iterator cend() const { return data_ + size_; }

  const_reference front() const { return data_[0]; }
  reference front() { return data_[0]; }

  const_reference back() const { return data_[size_ - 1]; }
  reference back() { return data_[size_ - 1]; }

  // Capacity
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  void reserve(size_type new_cap) {
    if (new_cap <= capacity_) {
      return;
    }

    T* new_data = static_cast<T*>(operator new(sizeof(T) * new_cap));
    size_t index = 0;
    try {
      for (; index < size_; ++index) {
        new (&new_data[index]) T(data_[index]);
      }
    } catch (...) {
      std::destroy_n(new_data, index);
      operator delete(new_data);
      throw;
    }

    // ---noexcept after this line---

    std::destroy_n(data_, size_);
    operator delete(data_);
    data_ = new_data;
    capacity_ = new_cap;
  }

  void clear() noexcept {
    // std::destroy_n not market as noexcept
    // but should not throw
    std::destroy_n(data_, size_);
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("pos is out of range");
    }
    size_type index = pos - begin();
    if (size_ == capacity_) {
      reserve(size_ == 0 ? 1 : size_ * 2);
    }
    iterator new_pos = begin() + index;
    // std::move_backward not marked as noexcept
    // but should not throw
    if (new_pos != end()) {
      std::move_backward(new_pos, end(), end() + 1);
    }
    try {
      new (new_pos) value_type(value);
    } catch (...) {
      if (new_pos != end()) {
        std::move_backward(new_pos + 1, end() + 1, end());
      }
      throw;
    }
    ++size_;
    return new_pos;
  }

  void erase(iterator pos) {
    if (pos < cbegin() || pos >= cend()) {
      throw std::out_of_range("pos is out of range");
    }
    pos->~T();
    iterator next = pos;
    if (next + 1 != end()) {
      std::move(next + 1, end(), next);
    }
    --size_;
    if (size_ > 0) {
      data_[size_].~T();
    }
  }

  void erase(const_iterator pos) { erase(begin() + (pos - cbegin())); }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (size_ == capacity_) {
      return;
    }

    T* new_data = static_cast<T*>(operator new(sizeof(T) * size_));

    // (assuming move contructor is noexcept)
    // ---noexcept after this line---
    // TODO: бла бла бла исключения бла бла бла думай!

    capacity_ = size_;
    for (size_t index = 0; index < size_; ++index) {
      new (&new_data[index]) T(std::move(data_[index]));
    }
    std::destroy_n(data_, size_);
    operator delete(data_);
    data_ = new_data;
  }

  // Modifiers
  void pop_back() { data_[--size_].~T(); }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      vector<T> tmp;
      tmp.reserve(size_ == 0 ? 1 : size_ * 2);
      while (tmp.size() < size_) {
        tmp.push_back(data_[tmp.size()]);
      }
      tmp.push_back(value);

      // ---noexcept after this line---

      swap(tmp);
      return;
    }

    new (&data_[size_]) T(value);
    ++size_;
  }

  void swap(vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  T* data_{nullptr};
  size_type size_{0};
  size_type capacity_{0};
};
}  // namespace s21

#endif  // S21_VECTOR_H_
