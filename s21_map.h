#ifndef _S21_MAP_H_
#define _S21_MAP_H_

#include <limits>
#include <vector>

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using value_type = std::pair<const Key, T>;

 private:
  enum class Color { RED, BLACK };

  struct Node {
    value_type kv;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(const Key& k, const T& v, Color c = Color::RED,
         Node* parent_node = nullptr)
        : kv(std::make_pair(k, v)),
          color(c),
          parent(parent_node),
          left(nullptr),
          right(nullptr) {}
  };

 public:
  class iterator {
   public:
    iterator(Node* node = nullptr, Node* last = nullptr)
        : current_(node), tail_(last) {}

    value_type& operator*() {
      if (current_ == nullptr) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return current_->kv;
    }

    const value_type& operator*() const {
      if (!current_) throw std::runtime_error("Dereferencing end iterator");
      return current_->kv;
    }

    value_type* operator->() {
      if (current_ == nullptr) {
        throw std::runtime_error("Dereferencing an end iterator");
      }
      return &(current_->kv);
    }

    const value_type* operator->() const {
      if (!current_) throw std::runtime_error("Accessing end iterator");
      return &current_->kv;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator++() {
      update_tail();
      if (current_ == tail_) {
        current_ = nullptr;
      } else {
        current_ = next_node(current_);
      }
      return *this;
    }

    iterator& operator--() {
      if (current_ == nullptr) {
        if (tail_ == nullptr) {
          throw std::runtime_error("Decrementing a null iterator");
        }
        current_ = tail_;
      } else {
        current_ = prev_node(current_);
      }
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

    Node* get_current() const { return current_; }
    Node* get_tail() const { return tail_; }

   private:
    Node* current_;
    Node* tail_;

    void update_tail() {
      tail_ = current_;
      while (tail_->parent != nullptr) tail_ = tail_->parent;
      while (tail_->right != nullptr) tail_ = tail_->right;
    }

    Node* next_node(Node* node) const {
      if (node->right != nullptr) {
        node = node->right;
        while (node->left != nullptr) {
          node = node->left;
        }
      } else {
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
          node = parent;
          parent = parent->parent;
        }
        node = parent;
      }
      return node;
    }

    Node* prev_node(Node* node) const {
      if (node->left != nullptr) {
        node = node->left;
        while (node->right != nullptr) {
          node = node->right;
        }
      } else {
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
          node = parent;
          parent = parent->parent;
        }
        node = parent;
      }
      return node;
    }
  };

  class const_iterator {
   public:
    const_iterator(const Node* node = nullptr, const Node* last = nullptr)
        : current_(node), tail_(last) {}

    const_iterator(const iterator& other)
        : current_(other.get_current()), tail_(other.get_tail()) {}

    const value_type& operator*() const {
      if (!current_) throw std::runtime_error("Dereferencing end iterator");
      return current_->kv;
    }

    const value_type* operator->() const {
      if (!current_) throw std::runtime_error("Accessing end iterator");
      return &current_->kv;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator++() {
      if (current_ == tail_) {
        current_ = nullptr;
      } else if (current_ != nullptr) {
        current_ = next_node(current_);
      }
      return *this;
    }

    const_iterator& operator--() {
      if (current_ == nullptr) {
        current_ = tail_;
      } else {
        current_ = prev_node(current_);
      }
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }
    const Node* get_current() const { return current_ ? current_ : nullptr; }
  /////////////////////////////////////////////////////////////////////////////
  void draw() {
    if (!root_) return;
    int max_key_length = 0;
    std::vector<std::vector<Node*>> matrix;
    std::queue<std::tuple<Node*, size_t, size_t>> q;
    q.emplace(root_, 0, 0);

    while (!q.empty()) {
      auto [node, level, pos] = q.front();
      q.pop();
      if (level >= matrix.size()) matrix.resize(level + 1);
      if (pos >= matrix[level].size()) matrix[level].resize(pos + 1, nullptr);
      matrix[level][pos] = node;
      if (node) {
        max_key_length =  std::max(max_key_length, static_cast<int>(std::to_string(node->kv.first).length()));
        q.emplace(node->left, level + 1, 2 * pos);
        q.emplace(node->right, level + 1, 2 * pos + 1);
      }
    }
  //   if (!matrix.empty() && std::all_of(matrix.back().begin(), matrix.back().end(), [](Node* node) { return node == nullptr; })) {
  //     matrix.pop_back();
  // }
    std::vector<std::string> rows;
    for (auto it = matrix.rbegin(); it != matrix.rend(); ++it) {
      std::string row;
      std::string slash;
      std::string line;
      bool even = true;
      for (auto inner_it = it->begin(); inner_it != it->end(); ++inner_it) {
        auto [r, s, l] = center_number(*inner_it, max_key_length, even);
        row += r;
        slash += s;
        line += l;
        even = !even;
      }
      row += '\n';
      slash += '\n';
      line += '\n';
      rows.push_back(row);
      rows.push_back(slash);
      rows.push_back(line);
      max_key_length *= 2;
    }
    rows.pop_back();
    rows.pop_back();
    std::reverse(rows.begin(), rows.end());

    for (auto row : rows) std::cout << row;
  }

  std::tuple<std::string, std::string, std::string> center_number(Node* node, int width, bool even) {
    std::string num_str;
    std::string slash;
    std::string line;
    if (node) {
      num_str = std::to_string(node->kv.first);
      int padding = width - num_str.size();
      int left_pad = padding / 2;
      int right_pad = padding - left_pad;
      if (node->color == Color::BLACK)
        num_str = "\033[1;30m" + num_str + "\033[0m";
      else
        num_str = "\033[1;31m" + num_str + "\033[0m";

      num_str =
          std::string(left_pad, ' ') + num_str + std::string(right_pad, ' ');

      padding = width / 2;
      if (even) {
        slash = std::string(padding, ' ') + "/" + std::string(padding - 1, ' ');
        line = std::string(padding + 1, ' ') + std::string(padding - 1, '-');
      } else {
        slash =
            std::string(padding - 1, ' ') + "\\" + std::string(padding, ' ');
        line = std::string(padding - 1, '-') + std::string(padding + 1, ' ');
      }
    
    } else {
      num_str = slash = line = std::string(width, ' ');
    }
  
    return {num_str, slash, line};
  }
   private:
    const Node* current_;
    const Node* tail_;

    const Node* next_node(const Node* node) const {
      if (node->right != nullptr) {
        node = node->right;
        while (node->left != nullptr) {
          node = node->left;
        }
      } else {
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
          node = parent;
          parent = parent->parent;
        }
        node = parent;
      }
      return node;
    }

    const Node* prev_node(const Node* node) const {
      if (node->left != nullptr) {
        node = node->left;
        while (node->right != nullptr) {
          node = node->right;
        }
      } else {
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
          node = parent;
          parent = parent->parent;
        }
        node = parent;
      }
      return node;
    }
  };
  iterator begin() { return iterator(head_, tail_); }
  iterator end() { return iterator(nullptr, tail_); }

  const_iterator begin() const { return const_iterator(head_, tail_); }
  const_iterator end() const { return const_iterator(nullptr, tail_); }

 private:
  Node* root_;
  Node* head_;
  Node* tail_;
  size_t size_;

 public:
  map() : root_(nullptr), head_(nullptr), tail_(nullptr), size_(0) {}

  map(const map& other)
      : root_(nullptr), head_(nullptr), tail_(nullptr), size_(0) {
    copy_tree(other.root_);
  }

  map& operator=(map other) {
    swap(other);
    return *this;
  }

  map(map&& other) noexcept
      : root_(other.root_),
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_) {
    other.root_ = nullptr;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  map(std::initializer_list<std::pair<const Key, T>> init_list)
      : root_(nullptr), head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& item : init_list) {
      insert(item.first, item.second);
    }
  }

  ~map() { clear(); }

  void erase(const Key& key) {
    Node* node_to_delete = find_node(key);
    if (node_to_delete == nullptr) return;
    erase_node(node_to_delete);
  }

  iterator erase(iterator& pos) {
    if (pos == end()) {
      return pos;
    }
    Node* node_to_delete = pos.get_current();
    if (node_to_delete == nullptr) return end();
    ++pos;
    erase_node(node_to_delete);
    return pos;
  }

  void clear() {
    if (root_ == nullptr) return;

    iterator it = begin();
    while (it != end()) {
      Node* node = it.get_current();
      it++;
      extract_node(node);
      delete node;
    }
    root_ = nullptr;
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  size_t size() const { return size_; }
  size_t max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
  }

  bool empty() const { return size_ == 0; }
  bool contains(const Key& key) const { return find_node(key) != nullptr; }
  void swap(map& other) noexcept {
    if (this == &other) return;

    Node* temp_root_ = root_;
    root_ = other.root_;
    other.root_ = temp_root_;

    Node* temp_head = head_;
    head_ = other.head_;
    other.head_ = temp_head;

    Node* temp_tail = tail_;
    tail_ = other.tail_;
    other.tail_ = temp_tail;

    size_t temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;
  }

  void merge(map& other) {
    if (this == &other || other.empty())
      return;
    else if (this->empty())
      this->swap(other);
    else {
      map temp_tree;
      auto it = other.begin();
      while (it != other.end()) {
        Node* node = it.get_current();
        it++;
        extract_node(node);
        if (!insert_other_node(node)) {
          temp_tree.insert_other_node(node);
        }
      }
      other.size_ = 0;
      other.root_ = nullptr;
      other.head_ = other.tail_ = nullptr;
      other.swap(temp_tree);
    }
  }

  T& operator[](const Key& key) {
    Node* node = find_node(key);
    if (node == nullptr) {
      auto [it, _] = insert(key, T());
      node = it.get_current();
    }
    return node->kv.second;
  }

  T& at(const Key& key) {
    Node* node = find_node(key);
    if (node == nullptr) {
      throw std::out_of_range("Key not found");
    }
    return node->kv.second;
  }

  const T& at(const Key& key) const {
    const Node* node = find_node(key);
    if (node == nullptr) {
      throw std::out_of_range("Key not found");
    }
    return node->kv.second;
  }

  std::pair<iterator, bool> insert(const Key& key, const T& value) {
    Node* existing_node = find_node(key);
    if (existing_node != nullptr) {
      return std::make_pair(iterator(existing_node, tail_), false);
    }
    if (root_ == nullptr) {
      insert_root(key, value);
      return std::make_pair(iterator(root_, tail_), true);
    } else {
      auto [new_node, _] = insert_node(key, value);
      return std::make_pair(iterator(new_node, tail_), true);
    }
  }

  std::pair<iterator, bool> insert(const std::pair<Key, T>& pair) {
    return insert(pair.first, pair.second);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& value) {
    Node* node = find_node(key);
    if (node != nullptr) {
      node->kv.second = value;
      return std::make_pair(iterator(node, tail_), false);
    } else {
      insert(key, value);
      Node* new_node = find_node(key);
      return std::make_pair(iterator(new_node, tail_), true);
    }
  }

  iterator find(const Key& key) {
    Node* node = find_node(key);
    if (node != nullptr) {
      return iterator(node);
    }
    return end();
  }

  const_iterator find(const Key& key) const {
    const Node* node = find_node(key);
    if (node != nullptr) {
      return const_iterator(node);
    }
    return end();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    static_assert(
        (std::is_convertible_v<Args, std::pair<const Key, T>> && ...),
        "All arguments must be convertible to std::pair<const Key, T>");

    std::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

  bool is_valid_rb_tree() const {
    if (root_ == nullptr) return true;
    if (root_->color != Color::BLACK) {
      return false;
    }
    int black_count = -1;
    return check_rb_properties(root_, 0, black_count);
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto lower = lower_bound(key);
    auto upper = lower;
    if (upper != end() && upper->first == key) {
      ++upper;
    }
    return std::make_pair(lower, upper);
  }

  iterator lower_bound(const Key& key) {
    Node* current = root_;
    Node* result = nullptr;

    while (current != nullptr) {
      if (key < current->kv.first) {
        result = current;
        current = current->left;
      } else if (current->kv.first < key) {
        current = current->right;
      } else {
        return iterator(current);
      }
    }
    return result ? iterator(result) : end();
  }

  iterator upper_bound(const Key& key) {
    iterator lower = lower_bound(key);
    if (lower != end() && lower->first == key) {
      ++lower;
    }
    return lower;
  }

  //////////////////////////////////////////////////////////////////////////////////////////
  // void print() { print_tree(root_); }

  // void print_tree(Node* node, int depth = 0) {
  //   if (node != nullptr) {
  //     print_tree(node->right, depth + 1);
  //     for (int i = 0; i < depth; ++i) {
  //       std::cout << "  ";
  //     }
  //     if (node->color == Color::RED) {
  //       std::cout << "\033[1;31m";
  //     } else {
  //       std::cout << "\033[1;37m";
  //     }
  //     std::cout << node->kv.first << "("
  //               << (node->color == Color::RED ? "R" : "B") << ")"
  //               << "\033[0m";
  //     std::cout << std::endl;
  //     print_tree(node->left, depth + 1);
  //   }
  // }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

 private:
  bool check_rb_properties(Node* node, int current_black,
                           int& path_black_count) const {
    if (node == nullptr) {
      if (path_black_count == -1) {
        path_black_count = current_black;
        return true;
      }
      return current_black == path_black_count;
    }
    if (node->color == Color::RED) {
      if (node->left && node->left->color == Color::RED) return false;
      if (node->right && node->right->color == Color::RED) return false;
    }
    int new_black = current_black + (node->color == Color::BLACK ? 1 : 0);
    return check_rb_properties(node->left, new_black, path_black_count) &&
           check_rb_properties(node->right, new_black, path_black_count);
  }

  Node* extract_node(Node* node) {
    if (node->right != nullptr) {
      if (node->parent != nullptr) node->parent->left = node->right;
      node->right->parent = node->parent;
    }
    detach_node(node);
    return node;
  }

  void detach_node(Node* node) {
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->color = Color::RED;
  }

  void insert_root(const Key& key, const T& value) {
    Node* new_node = new Node(key, value, Color::BLACK, nullptr);
    root_ = new_node;
    head_ = new_node;
    tail_ = new_node;
    size_++;
  }

  void set_root_features() {
    root_->color = Color::BLACK;
    root_->left = nullptr;
    root_->right = nullptr;
    root_->parent = nullptr;
    head_ = tail_ = root_;
    size_++;
  }

  std::pair<Node*, bool> find_parent_for_insert(const Key& key) {
    Node* current = root_;
    Node* parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (key < current->kv.first) {
        current = current->left;
      } else if (key > current->kv.first) {
        current = current->right;
      } else {
        return {parent, false};
      }
    }
    return {parent, true};
  }

  std::pair<Node*, bool> insert_node(const Key& key, const T& value) {
    auto [parent, can_insert] = find_parent_for_insert(key);
    if (!can_insert) return {nullptr, false};

    Node* new_node = new Node(key, value, Color::RED, parent);
    insert_node_final(new_node, parent);
    return {new_node, true};
    ;
  }

  bool insert_other_node(Node* node) {
    if (root_ == nullptr) {
      root_ = node;
      set_root_features();
      return true;
    } else {
      return insert_ready_node(node);
    }
  }

  bool insert_ready_node(Node* node) {
    auto [parent, can_insert] = find_parent_for_insert(node->kv.first);
    if (!can_insert) return false;
    insert_node_final(node, parent);
    return true;
  }

  void insert_node_final(Node* new_node, Node* parent) {
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = parent;
    if (new_node->kv.first < parent->kv.first) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
    fix_insert(new_node);
    if (new_node->kv.first < head_->kv.first) {
      head_ = new_node;
    }
    if (new_node->kv.first > tail_->kv.first) {
      tail_ = new_node;
    }
    size_++;
  }

  void copy_tree(Node* src) {
    if (src != nullptr) {
      insert(src->kv.first, src->kv.second);
      copy_tree(src->left);
      copy_tree(src->right);
    }
    head_ = (root_ != nullptr) ? minimum(root_) : nullptr;
    tail_ = (root_ != nullptr) ? maximum(root_) : nullptr;
  }

  void fix_insert(Node* node) {
    while (is_red_parent(node)) {
      if (is_left_child(node->parent)) {
        handle_left_case(node);
      } else {
        handle_right_case(node);
      }
    }
    root_->color = Color::BLACK;
  }

  bool is_red_parent(Node* node) {
    return node->parent != nullptr && node->parent->color == Color::RED;
  }

  bool is_left_child(Node* node) { return node == node->parent->left; }

  void handle_left_case(Node*& node) {
    Node* uncle = node->parent->parent->right;
    if (is_red_uncle(uncle)) {
      handle_red_uncle_case(node, uncle);
    } else {
      handle_black_uncle_left_case(node);
    }
  }

  void handle_right_case(Node*& node) {
    Node* uncle = node->parent->parent->left;
    if (is_red_uncle(uncle)) {
      handle_red_uncle_case(node, uncle);
    } else {
      handle_black_uncle_right_case(node);
    }
  }

  bool is_red_uncle(Node* uncle) {
    return uncle != nullptr && uncle->color == Color::RED;
  }

  void handle_red_uncle_case(Node*& node, Node* uncle) {
    node->parent->color = Color::BLACK;
    uncle->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    node = node->parent->parent;
  }

  void handle_black_uncle_left_case(Node*& node) {
    if (is_right_child(node)) {
      node = node->parent;
      left_rotate(node);
    }
    recolor_and_rotate_left_parent(node);
  }

  void handle_black_uncle_right_case(Node*& node) {
    if (is_left_child(node)) {
      node = node->parent;
      right_rotate(node);
    }
    recolor_and_rotate_right_parent(node);
  }

  void recolor_and_rotate_left_parent(Node* node) {
    node->parent->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    right_rotate(node->parent->parent);
  }

  void recolor_and_rotate_right_parent(Node* node) {
    node->parent->color = Color::BLACK;
    node->parent->parent->color = Color::RED;
    left_rotate(node->parent->parent);
  }

  bool is_right_child(Node* node) { return node == node->parent->right; }

  void left_rotate(Node* parent) {
    Node* child = parent->right;
    parent->right = child->left;
    if (child->left != nullptr) child->left->parent = parent;
    child->parent = parent->parent;
    if (parent->parent == nullptr) {
      root_ = child;
    } else if (parent == parent->parent->left) {
      parent->parent->left = child;
    } else {
      parent->parent->right = child;
    }
    child->left = parent;
    parent->parent = child;
  }

  void right_rotate(Node* parent) {
    Node* child = parent->left;
    parent->left = child->right;
    if (child->right != nullptr) child->right->parent = parent;
    child->parent = parent->parent;
    if (parent->parent == nullptr) {
      root_ = child;
    } else if (parent == parent->parent->right) {
      parent->parent->right = child;
    } else {
      parent->parent->left = child;
    }
    child->right = parent;
    parent->parent = child;
  }

  Node* find_node(const Key& key) {
    Node* current = root_;
    while (current != nullptr) {
      if (key == current->kv.first) return current;
      current = (key < current->kv.first) ? current->left : current->right;
    }
    return nullptr;
  }

  const Node* find_node(const Key& key) const {
    const Node* current = root_;
    while (current != nullptr) {
      if (key == current->kv.first) return current;
      current = (key < current->kv.first) ? current->left : current->right;
    }
    return nullptr;
  }

  Node* minimum(Node* node) const {
    while (node->left != nullptr) node = node->left;
    return node;
  }

  Node* maximum(Node* node) const {
    while (node->right != nullptr) node = node->right;
    return node;
  }

  void transplant(Node* old_node, Node* new_node) {
    if (old_node->parent == nullptr) {
      root_ = new_node;
    } else if (old_node == old_node->parent->left) {
      old_node->parent->left = new_node;
    } else {
      old_node->parent->right = new_node;
    }
    if (new_node != nullptr) {
      new_node->parent = old_node->parent;
    }
  }

  void erase_node(Node* node_to_delete) {
    if (!node_to_delete) return;

    bool update_head = (node_to_delete == head_);
    bool update_tail = (node_to_delete == tail_);

    Node* replacement = node_to_delete;
    Color original_color = replacement->color;
    Node* child = nullptr;
    Node* parent_for_fix = nullptr;

    if (node_to_delete->left == nullptr) {
      child = node_to_delete->right;
      parent_for_fix = node_to_delete->parent;
      transplant(node_to_delete, node_to_delete->right);
    } else if (node_to_delete->right == nullptr) {
      child = node_to_delete->left;
      parent_for_fix = node_to_delete->parent;
      transplant(node_to_delete, node_to_delete->left);
    } else {
      replacement = minimum(node_to_delete->right);
      original_color = replacement->color;
      child = replacement->right;
      parent_for_fix = replacement;
      if (replacement->parent != node_to_delete) {
        parent_for_fix = replacement->parent;
        transplant(replacement, replacement->right);
        replacement->right = node_to_delete->right;
        if (replacement->right) replacement->right->parent = replacement;
      }
      transplant(node_to_delete, replacement);
      replacement->left = node_to_delete->left;
      if (replacement->left) replacement->left->parent = replacement;
      replacement->color = node_to_delete->color;
    }
    delete node_to_delete;
    size_--;
    if (original_color == Color::BLACK) {
      handle_black_case(child, parent_for_fix);
    }
    if (update_head) head_ = root_ ? minimum(root_) : nullptr;
    if (update_tail) tail_ = root_ ? maximum(root_) : nullptr;
  }

  void handle_black_case(Node* child, Node* parent_for_fix) {
    if (child) {
      fix_delete(child);
    } else if (parent_for_fix) {
      Node dummy(Key(), T(), Color::BLACK);
      dummy.parent = parent_for_fix;
      if (parent_for_fix->left == nullptr) {
        parent_for_fix->left = &dummy;
        fix_delete(&dummy);
        parent_for_fix->left = nullptr;
      } else {
        parent_for_fix->right = &dummy;
        fix_delete(&dummy);
        parent_for_fix->right = nullptr;
      }
    }
  }

  void fix_delete(Node* node) {
    while (node != root_ && node->color == Color::BLACK) {
      if (node == node->parent->left) {
        Node* brother = node->parent->right;
        if (brother && brother->color == Color::RED) {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          left_rotate(node->parent);
          brother = node->parent->right;
        }
        if (brother &&
            (!brother->left || brother->left->color == Color::BLACK) &&
            (!brother->right || brother->right->color == Color::BLACK)) {
          brother->color = Color::RED;
          node = node->parent;
        } else {
          if (brother &&
              (!brother->right || brother->right->color == Color::BLACK)) {
            if (brother->left) brother->left->color = Color::BLACK;
            brother->color = Color::RED;
            right_rotate(brother);
            brother = node->parent->right;
          }

          if (brother) {
            brother->color = node->parent->color;
            node->parent->color = Color::BLACK;
            if (brother->right) brother->right->color = Color::BLACK;
            left_rotate(node->parent);
          }
          node = root_;
        }
      } else {
        Node* brother = node->parent->left;
        if (brother && brother->color == Color::RED) {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          right_rotate(node->parent);
          brother = node->parent->left;
        }
        if (brother &&
            (!brother->right || brother->right->color == Color::BLACK) &&
            (!brother->left || brother->left->color == Color::BLACK)) {
          brother->color = Color::RED;
          node = node->parent;
        } else {
          if (brother &&
              (!brother->left || brother->left->color == Color::BLACK)) {
            if (brother->right) brother->right->color = Color::BLACK;
            brother->color = Color::RED;
            left_rotate(brother);
            brother = node->parent->left;
          }
          if (brother) {
            brother->color = node->parent->color;
            node->parent->color = Color::BLACK;
            if (brother->left) brother->left->color = Color::BLACK;
            right_rotate(node->parent);
          }
          node = root_;
        }
      }
    }
    node->color = Color::BLACK;
  }

};  // map
}  // namespace s21
#endif  // _S21_MAP_H_