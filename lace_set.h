#ifndef _lace_SET_H_
#define _lace_SET_H_

#include "lace_map.h"

namespace lace {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  class iterator {
    using tree_iterator = typename map<Key, char>::iterator;
    tree_iterator it_;

   public:
    iterator(tree_iterator it) : it_(it) {}

    value_type operator*() const { return it_->first; }
    const value_type* operator->() const { return &it_->first; }

    iterator& operator++() {
      ++it_;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++it_;
      return tmp;
    }

    iterator& operator--() {
      --it_;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      --it_;
      return tmp;
    }

    bool operator==(const iterator& other) const { return it_ == other.it_; }
    bool operator!=(const iterator& other) const { return it_ != other.it_; }

    tree_iterator base() const { return it_; }
  };

  class const_iterator {
    using tree_const_iterator = typename map<Key, char>::const_iterator;
    tree_const_iterator it_;

   public:
    const_iterator(tree_const_iterator it) : it_(it) {}
    const_iterator(iterator it) : it_(it.base()) {}

    value_type operator*() const { return (*it_).first; }
    const value_type* operator->() const { return &it_->first; }

    const_iterator& operator++() {
      ++it_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++it_;
      return tmp;
    }

    const_iterator& operator--() {
      --it_;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --it_;
      return tmp;
    }

    bool operator==(const const_iterator& other) const {
      return it_ == other.it_;
    }
    bool operator!=(const const_iterator& other) const {
      return it_ != other.it_;
    }

    tree_const_iterator base() const { return it_; }
  };

 private:
  map<Key, char> tree_;

 public:
  set() = default;

  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  set(const set& other) = default;
  set(set&& other) noexcept = default;
  ~set() = default;

  set& operator=(const set& other) = default;
  set& operator=(set&& other) noexcept = default;

  iterator begin() noexcept { return iterator(tree_.begin()); }
  const_iterator begin() const noexcept {
    return const_iterator(tree_.begin());
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(tree_.begin());
  }
  iterator end() noexcept { return iterator(tree_.end()); }
  const_iterator end() const noexcept { return const_iterator(tree_.end()); }
  const_iterator cend() const noexcept { return const_iterator(tree_.end()); }

  bool empty() const noexcept { return tree_.empty(); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree_.insert(value, char());
    return {iterator(result.first), result.second};
  }

  void insert(std::initializer_list<value_type> ilist) {
    for (const auto& value : ilist) {
      insert(value);
    }
  }
  void erase(iterator pos) {
    typename map<Key, char>::iterator it = pos.base();
    tree_.erase(it);
  }

  void erase(const key_type& key) { tree_.erase(key); }
  void swap(set& other) noexcept { tree_.swap(other.tree_); }
  void merge(set& other) { tree_.merge(other.tree_); }

  iterator find(const key_type& key) { return iterator(tree_.find(key)); }
  const_iterator find(const key_type& key) const {
    return const_iterator(tree_.find(key));
  }
  bool contains(const key_type& key) const { return tree_.contains(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    static_assert((std::is_convertible_v<Args, Key> && ...),
                  "All arguments must be convertible to Key type");

    std::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));
    (results.push_back(insert(std::forward<Args>(args))), ...);

    return results;
  }
};

}  // namespace lace

#endif  // _lace_SET_H_