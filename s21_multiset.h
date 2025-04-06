#ifndef _S21_MULTISET_H_
#define _S21_MULTISET_H_

#include "s21_map.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;

 private:
  using tree_type = map<Key, size_t>;
  tree_type tree_;
  size_type size_ = 0;

 public:
  class MultisetIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Key;
    using pointer = const Key*;
    using reference = const Key&;

    MultisetIterator(
        typename tree_type::iterator it = typename tree_type::iterator(),
        size_t count = 0)
        : tree_it_(it), current_count_(count) {}

    reference operator*() {
      if (tree_it_ == typename tree_type::iterator()) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return tree_it_->first;
    }

    pointer operator->() {
      if (tree_it_ == typename tree_type::iterator()) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return &(tree_it_->first);
    }

    MultisetIterator& operator++() {
      if (tree_it_ == typename tree_type::iterator()) {
        throw std::runtime_error("Incrementing an end iterator");
      }
      if (current_count_ + 1 < tree_it_->second) {
        current_count_++;
      } else {
        ++tree_it_;
        current_count_ = 0;
      }
      return *this;
    }

    MultisetIterator operator++(int) {
      MultisetIterator temp = *this;
      ++(*this);
      return temp;
    }

    MultisetIterator& operator--() {
      if (tree_it_ == typename tree_type::iterator()) {
        --tree_it_;
        current_count_ = tree_it_->second - 1;
      } else if (current_count_ > 0) {
        current_count_--;
      } else {
        --tree_it_;
        current_count_ = tree_it_->second - 1;
      }
      return *this;
    }

    MultisetIterator operator--(int) {
      MultisetIterator temp = *this;
      --(*this);
      return temp;
    }

    typename tree_type::iterator base() const { return tree_it_; }

    bool operator==(const MultisetIterator& other) const {
      return tree_it_ == other.tree_it_ &&
             current_count_ == other.current_count_;
    }

    bool operator!=(const MultisetIterator& other) const {
      return !(*this == other);
    }

    size_t get_current_count() const { return current_count_; }

   private:
    typename tree_type::iterator tree_it_;
    size_t current_count_;
  };

  class MultisetConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Key;
    using pointer = const Key*;
    using reference = const Key&;

    MultisetConstIterator(typename tree_type::const_iterator it =
                              typename tree_type::const_iterator(),
                          size_t count = 0)
        : tree_it_(it), current_count_(count) {}

    MultisetConstIterator(const MultisetIterator& other)
        : tree_it_(other.base()), current_count_(other.get_current_count()) {}

    reference operator*() const {
      if (tree_it_ == typename tree_type::const_iterator()) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return tree_it_->first;
    }

    pointer operator->() const {
      if (tree_it_ == typename tree_type::const_iterator()) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return &(tree_it_->first);
    }

    MultisetConstIterator& operator++() {
      if (tree_it_ == typename tree_type::const_iterator()) {
        throw std::runtime_error("Incrementing an end iterator");
      }
      if (current_count_ + 1 < tree_it_->second) {
        current_count_++;
      } else {
        ++tree_it_;
        current_count_ = 0;
      }
      return *this;
    }

    MultisetConstIterator operator++(int) {
      MultisetConstIterator temp = *this;
      ++(*this);
      return temp;
    }
    typename tree_type::const_iterator base() const { return tree_it_; }

    bool operator==(const MultisetConstIterator& other) const {
      return tree_it_ == other.tree_it_ &&
             current_count_ == other.current_count_;
    }

    bool operator!=(const MultisetConstIterator& other) const {
      return !(*this == other);
    }

   private:
    typename tree_type::const_iterator tree_it_;
    size_t current_count_;
  };

  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;

  multiset() : tree_() {}

  multiset(std::initializer_list<value_type> const& items) : tree_() {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& ms) : tree_(ms.tree_), size_(ms.size_) {}

  multiset(multiset&& ms) noexcept : tree_(std::move(ms.tree_)) {
    size_ = ms.size_;
    ms.size_ = 0;
  }

  ~multiset() = default;

  multiset& operator=(const multiset& other) {
    if (this != &other) {
      tree_ = other.tree_;
      size_ = other.size_;
    }
    return *this;
  }

  multiset& operator=(multiset&& ms) noexcept {
    if (this != &ms) {
      tree_ = std::move(ms.tree_);
      size_ = ms.size_;
    }
    return *this;
  }

  iterator begin() noexcept { return iterator(tree_.begin(), 0); }

  iterator end() noexcept { return iterator(tree_.end(), 0); }

  const_iterator begin() const noexcept {
    return const_iterator(tree_.begin(), 0);
  }

  const_iterator end() const noexcept { return const_iterator(tree_.end(), 0); }

  bool empty() const noexcept { return tree_.empty(); }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept {
    tree_.clear();
    size_ = 0;
  }

  iterator insert(const value_type& value) {
    tree_[value]++;
    size_++;
    return iterator(tree_.find(value), 0);
  }

  void insert(std::initializer_list<Key> keys) {
    for (const auto& key : keys) {
      tree_[key]++;
      size_++;
    }
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    auto key = *pos;
    if (tree_[key] > 1) {
      tree_[key]--;
    } else {
      tree_.erase(key);
    }
    size_--;
  }

  void swap(multiset& other) noexcept {
    size_t temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;

    tree_.swap(other.tree_);
  }

  void merge(multiset& other) {
    if (this == &other || other.empty())
      return;
    else if (this->empty())
      this->swap(other);
    else {
      for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
        auto found_node = tree_.find(it->first);
        if (found_node != tree_.end()) {
          found_node->second += it->second;
          size_ += it->second;
          other.size_ -= it->second;
        }
      }
      tree_.merge(other.tree_);
      size_ += other.size_;
      other.clear();
      other.size_ = 0;
    }
  }

  size_type count(const key_type& key) const {
    auto it = tree_.find(key);
    if (it != tree_.end()) {
      return it->second;
    }
    return 0;
  }

  iterator find(const key_type& key) { return iterator(tree_.find(key), 0); }
  const_iterator find(const key_type& key) const {
    return const_iterator(tree_.find(key), 0);
  }

  bool contains(const key_type& key) const {
    return tree_.find(key) != tree_.end();
  }

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    auto tree_pair = tree_.equal_range(key);
    return {iterator(tree_pair.first), iterator(tree_pair.second)};
  }

  iterator lower_bound(const key_type& key) { return tree_.lower_bound(key); }

  iterator upper_bound(const key_type& key) { return tree_.upper_bound(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    static_assert((std::is_convertible_v<Args, Key> && ...),
                  "All arguments must be convertible to Key type");

    std::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));

    (results.emplace_back(insert(std::forward<Args>(args)), true), ...);

    return results;
  }

};  // multiset

}  // namespace s21

#endif  // _S21_MULTISET_H_