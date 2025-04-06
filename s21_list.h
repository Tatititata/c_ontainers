#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct BaseNode {
    BaseNode* next;
    BaseNode* prev;
    BaseNode() : next(this), prev(this) {}
    BaseNode(BaseNode* prev_init, BaseNode* next_init)
        : next(next_init), prev(prev_init) {}
    virtual ~BaseNode() {}
  };

  struct Node : public BaseNode {
    T data;
    Node(const_reference value) : data(value) {}
    Node(BaseNode* prev, BaseNode* next, const_reference value)
        : BaseNode(prev, next), data{value} {}
  };

 public:
  template <typename iterator_type>
  class ListIterator {
    friend class list;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = iterator_type;
    using pointer = iterator_type*;
    using reference = iterator_type&;
    using iterator_category = std::bidirectional_iterator_tag;
    ListIterator(BaseNode* node) : current(node) {}
    reference operator*() const { return static_cast<Node*>(current)->data; }
    ListIterator<value_type>& operator++() {
      current = current->next;
      return *this;
    }
    ListIterator<value_type> operator++(int) {
      iterator temp = *this;
      current = current->next;
      return temp;
    }
    ListIterator<value_type>& operator--() {
      current = current->prev;
      return *this;
    }
    ListIterator<value_type> operator--(int) {
      iterator temp = *this;
      current = current->prev;
      return temp;
    }
    bool operator==(const ListIterator<value_type>& other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator<value_type>& other) const {
      return current != other.current;
    }

   private:
    BaseNode* current;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    using ListIterator<value_type>::current;
    // ListConstIterator(BaseNode* node) : ListIterator<value_type>(node) {}
    ListConstIterator(const BaseNode* node)
        : ListIterator<value_type>(const_cast<BaseNode*>(node)) {}
    ListConstIterator(const ListIterator<value_type>& other)
        : ListIterator<value_type>(other) {}
    const value_type& operator*() const {
      return static_cast<const Node*>(current)->data;
    }
  };

  using reference = T&;
  using value_type = T;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  list() : current_size(0), sentinel_node() {};

  list(size_type n) : current_size(0), sentinel_node() {
    try {
      while (n--) {
        push_back(value_type());
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  list(std::initializer_list<value_type> const& items)
      : current_size(0), sentinel_node() {
    try {
      for (const_reference item : items) {
        push_back(item);
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  list(const list& l) : current_size(0), sentinel_node() {
    try {
      BaseNode* current = l.sentinel_node.next;
      while (current != &l.sentinel_node) {
        BaseNode* next = current->next;
        push_back(static_cast<Node*>(current)->data);
        current = next;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  list(list&& l) {
    if (l.sentinel_node.next != &l.sentinel_node) {
      sentinel_node.next = l.sentinel_node.next;
      sentinel_node.prev = l.sentinel_node.prev;
      sentinel_node.next->prev = &sentinel_node;
      sentinel_node.prev->next = &sentinel_node;
      current_size = l.current_size;
      l.sentinel_node.prev = &l.sentinel_node;
      l.sentinel_node.next = &l.sentinel_node;
      l.current_size = 0;
    }
  }

  ~list() { clear(); }

  list& operator=(list&& l) {
    if (&sentinel_node != &l.sentinel_node) {
      swap(l);
      l.clear();
    }
    return *this;
  }

  list& operator=(const list& l) {
    if (&sentinel_node != &l.sentinel_node) {
      clear();
      BaseNode* current = l.sentinel_node.next;
      while (current != &l.sentinel_node) {
        BaseNode* next = current->next;
        push_back(static_cast<Node*>(current)->data);
        current = next;
      }
    }
    return *this;
  }

  const_reference front() const {
    return static_cast<const Node*>(sentinel_node.next)->data;
  }
  reference front() { return static_cast<Node*>(sentinel_node.next)->data; }
  const_reference back() const {
    return static_cast<const Node*>(sentinel_node.prev)->data;
  }
  reference back() { return static_cast<Node*>(sentinel_node.prev)->data; }

  iterator begin() { return iterator(sentinel_node.next); }
  iterator end() { return iterator(&sentinel_node); }

  const_iterator begin() const { return const_iterator(sentinel_node.next); }
  const_iterator end() const { return const_iterator(&sentinel_node); }

  bool empty() const { return current_size == 0; };
  size_type size() const { return current_size; }
  size_type max_size() const { /*TODO*/ return 0; }

  void push_back(const_reference value) {
    Node* new_node = new Node(sentinel_node.prev, &sentinel_node, value);
    sentinel_node.prev->next = new_node;
    sentinel_node.prev = new_node;
    current_size++;
  }

  void push_front(const_reference value) {
    Node* new_node = new Node(&sentinel_node, sentinel_node.next, value);
    sentinel_node.next->prev = new_node;
    sentinel_node.next = new_node;
    current_size++;
  }

  void pop_back() {
    BaseNode* old_tail = sentinel_node.prev;
    old_tail->prev->next = &sentinel_node;
    sentinel_node.prev = old_tail->prev;
    delete old_tail;
    current_size--;
  }

  void pop_front() {
    BaseNode* old_head = sentinel_node.next;
    old_head->next->prev = &sentinel_node;
    sentinel_node.next = old_head->next;
    delete old_head;
    current_size--;
  }

  void clear() {
    BaseNode* current = sentinel_node.next;
    while (current != &sentinel_node) {
      BaseNode* next = current->next;
      delete current;
      current = next;
    }
    sentinel_node.next = &sentinel_node;
    sentinel_node.prev = &sentinel_node;
    current_size = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(pos.current->prev, pos.current, value);
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    current_size++;
    iterator i(new_node);
    return i;
  }

  void erase(iterator pos) {
    BaseNode* target_node = pos.current;
    target_node->next->prev = target_node->prev;
    target_node->prev->next = target_node->next;
    delete target_node;
    current_size--;
  }

  void swap(list& other) {
    if (current_size == 0 && other.size() != 0) {
      sentinel_node.next = other.sentinel_node.next;
      sentinel_node.prev = other.sentinel_node.prev;
      sentinel_node.next->prev = &sentinel_node;
      sentinel_node.prev->next = &sentinel_node;
      other.sentinel_node.next = other.sentinel_node.prev =
          &other.sentinel_node;
    } else if (current_size != 0 && other.size() == 0) {
      other.sentinel_node.next = sentinel_node.next;
      other.sentinel_node.prev = sentinel_node.prev;
      other.sentinel_node.next->prev = &other.sentinel_node;
      other.sentinel_node.prev->next = &other.sentinel_node;
      sentinel_node.next = sentinel_node.prev = &sentinel_node;
    } else if (current_size != 0 && other.size() != 0) {
      std::swap(sentinel_node.next, other.sentinel_node.next);
      std::swap(sentinel_node.prev, other.sentinel_node.prev);
      sentinel_node.next->prev = &sentinel_node;
      sentinel_node.prev->next = &sentinel_node;
      other.sentinel_node.next->prev = &other.sentinel_node;
      other.sentinel_node.prev->next = &other.sentinel_node;
    }
    std::swap(current_size, other.current_size);
  }

  void reverse() {
    BaseNode* current = sentinel_node.next;
    while (current != &sentinel_node) {
      BaseNode* tmp = current->next;
      current->next = current->prev;
      current->prev = tmp;
      current = current->prev;
    }
    BaseNode* tmp = current->next;
    current->next = current->prev;
    current->prev = tmp;
  }

  void merge(list& other) {
    BaseNode* original = sentinel_node.next;
    BaseNode* foreign = other.sentinel_node.next;
    BaseNode fake;
    fake.next = &sentinel_node;
    BaseNode* tail = &fake;
    current_size += other.size();

    while (original != &sentinel_node && foreign != &other.sentinel_node) {
      if (static_cast<Node*>(original)->data <=
          static_cast<Node*>(foreign)->data) {
        tail->next = original;
        original->prev = tail;
        original = original->next;
      } else {
        tail->next = foreign;
        foreign->prev = tail;
        foreign = foreign->next;
      }
      tail = tail->next;
    }

    if (original != &sentinel_node) {
      tail->next = original;
      original->prev = tail;
    }
    if (foreign != &other.sentinel_node) {
      tail->next = foreign;
      foreign->prev = tail;
    }

    while (tail->next != &sentinel_node && tail->next != &other.sentinel_node) {
      tail = tail->next;
    }

    sentinel_node.next = fake.next;
    sentinel_node.prev = tail;
    tail->next = &sentinel_node;
    fake.next->prev = &sentinel_node;

    other.sentinel_node.next = &other.sentinel_node;
    other.sentinel_node.prev = &other.sentinel_node;
    other.current_size = 0;
  }

  void unique() {
    BaseNode* current = sentinel_node.next;
    BaseNode* next = current->next;
    while (next != &sentinel_node) {
      value_type curent_data = static_cast<Node*>(current)->data;
      value_type next_data = static_cast<Node*>(next)->data;
      if (curent_data == next_data) {
        next->next->prev = current;
        current->next = next->next;
        delete next;
        current_size--;
      } else {
        current = current->next;
      }
      next = current->next;
    }
  }

  void splice(const_iterator pos, list& other) {
    BaseNode* before = pos.current;
    other.sentinel_node.next->prev = before->prev;
    before->prev->next = other.sentinel_node.next;
    before->prev = other.sentinel_node.prev;
    other.sentinel_node.prev->next = before;

    current_size += other.current_size;
    other.current_size = 0;
    other.sentinel_node.next = &other.sentinel_node;
    other.sentinel_node.prev = &other.sentinel_node;
  }

  void sort() {
    BaseNode* sorted = merge_sort(sentinel_node.next, &sentinel_node);
    sentinel_node.next = sorted;
    sorted->prev = &sentinel_node;
    BaseNode* tail = sorted;
    while (tail->next != &sentinel_node) {
      tail = tail->next;
    }
    sentinel_node.prev = tail;
    tail->next = &sentinel_node;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    static_assert((std::is_same_v<value_type, Args> && ...), "Type mismatch");
    if constexpr (sizeof...(args) > 0) {
      for (const_reference item : {args...}) {
        push_back(item);
      }
    }
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    static_assert((std::is_same_v<value_type, Args> && ...), "Type mismatch");
    if constexpr (sizeof...(args) > 0) {
      iterator pos = (*this).begin();
      for (const_reference item : {args...}) {
        this->insert(pos, item);
      }
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    static_assert((std::is_same_v<value_type, Args> && ...), "Type mismatch");
    iterator start = pos;
    if constexpr (sizeof...(args) > 0) {
      start--;
      for (const_reference item : {args...}) {
        this->insert(pos, item);
      }
      start++;
    }
    return start;
  }

 private:
  BaseNode* merge(BaseNode* left, BaseNode* right, BaseNode* sentinel) {
    BaseNode fake;
    BaseNode* tail = &fake;

    while (left != sentinel && right != sentinel) {
      if (static_cast<Node*>(left)->data < static_cast<Node*>(right)->data) {
        tail->next = left;
        left->prev = tail;
        left = left->next;
      } else {
        tail->next = right;
        right->prev = tail;
        right = right->next;
      }
      tail = tail->next;
    }

    tail->next = (left == sentinel ? right : left);
    if (tail->next != sentinel) {
      tail->next->prev = tail;
    }

    BaseNode* result = fake.next;
    result->prev = sentinel;
    return result;
  }

  BaseNode* merge_sort(BaseNode* head, BaseNode* sentinel) {
    if (head == sentinel || head->next == sentinel) {
      return head;
    }

    BaseNode* middle = get_mid_point(head, sentinel);
    BaseNode* right_head = middle->next;
    middle->next = sentinel;
    right_head->prev = sentinel;

    BaseNode* left = merge_sort(head, sentinel);
    BaseNode* right = merge_sort(right_head, sentinel);
    return merge(left, right, sentinel);
  }

  BaseNode* get_mid_point(BaseNode* head, BaseNode* sentinel) {
    BaseNode* turtle = head;
    BaseNode* rabbit = head->next;
    while (rabbit != sentinel && rabbit->next != sentinel) {
      turtle = turtle->next;
      rabbit = rabbit->next->next;
    }
    return turtle;
  }

  size_type current_size;
  BaseNode sentinel_node;
};

}  // namespace s21

#endif
