#include <gtest/gtest.h>

#include <chrono>
#include <list>
#include <string>
#include <utility>

#include "../s21_list.h"

// using ListInt = std::list<int>;
// using ListString = std::list<std::string>;

using ListInt = s21::list<int>;
using ListString = s21::list<std::string>;

bool lists_equal(const ListInt& our_list, const std::list<int>& std_list) {
  if (our_list.size() != std_list.size()) return false;

  auto our_it = our_list.begin();
  auto std_it = std_list.begin();

  while (our_it != our_list.end()) {
    if (*our_it != *std_it) return false;
    ++our_it;
    ++std_it;
  }
  return true;
}

TEST(ListTest, default_constructor) {
  ListInt list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, initializer_list_constructor) {
  ListInt list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), 5);
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, copy_constructor) {
  ListInt original = {1, 2, 3};
  ListInt copy(original);
  std::list<int> std_original = {1, 2, 3};
  std::list<int> std_copy(std_original);
  EXPECT_TRUE(lists_equal(original, std_original));
  EXPECT_TRUE(lists_equal(copy, std_copy));
}

TEST(ListTest, move_constructor) {
  ListInt original = {1, 2, 3};
  ListInt moved(std::move(original));
  std::list<int> std_original = {1, 2, 3};
  std::list<int> std_moved(std::move(std_original));
  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(lists_equal(moved, std_moved));
}

TEST(ListTest, front_and_back) {
  ListInt list = {10, 20, 30};
  EXPECT_EQ(list.front(), 10);
  EXPECT_EQ(list.back(), 30);
}

TEST(ListTest, push_pop_operations) {
  ListInt list;
  list.push_back(1);
  list.push_back(2);
  list.push_front(0);

  std::list<int> std_list = {0, 1, 2};
  EXPECT_TRUE(lists_equal(list, std_list));

  list.pop_back();
  list.pop_front();
  std_list.pop_back();
  std_list.pop_front();
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, iterator_operations) {
  ListInt list = {1, 2, 3, 4, 5};
  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);

  auto end = list.end();
  --end;
  EXPECT_EQ(*end, 5);
}

TEST(ListTest, clear) {
  ListInt list = {1, 2, 3};
  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, swap) {
  ListInt a = {1, 2, 3};
  ListInt b = {4, 5};
  a.swap(b);

  std::list<int> std_a = {4, 5};
  std::list<int> std_b = {1, 2, 3};
  EXPECT_TRUE(lists_equal(a, std_a));
  EXPECT_TRUE(lists_equal(b, std_b));
}

TEST(ListTest, reverse) {
  ListInt list = {1, 2, 3, 4};
  list.reverse();
  std::list<int> std_list = {4, 3, 2, 1};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, unique) {
  ListInt list = {1, 1, 2, 3, 3, 3, 4, 5, 5};
  list.unique();
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, sort) {
  ListInt list = {3, 1, 4, 2, 5};
  list.sort();
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, merge) {
  ListInt a = {1, 3, 5};
  ListInt b = {2, 4, 6};
  a.merge(b);
  std::list<int> std_a = {1, 2, 3, 4, 5, 6};
  std::list<int> std_b;
  EXPECT_TRUE(lists_equal(a, std_a));
  EXPECT_TRUE(b.empty());
}

TEST(ListTest, insert_many) {
  ListInt list = {1, 5};
  auto it = list.begin();
  ++it;
  list.insert_many(it, 2, 3, 4);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, insert_many_back) {
  ListInt list = {1, 2};
  list.insert_many_back(3, 4, 5);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, insert_many_front) {
  ListInt list = {3, 4};
  list.insert_many_front(0, 1, 2);
  std::list<int> std_list = {0, 1, 2, 3, 4};
  EXPECT_TRUE(lists_equal(list, std_list));
}

TEST(ListTest, iterator_validity) {
  ListInt list = {1, 2, 3};
  auto it = list.begin();
  ++it;

  list.push_front(0);
  list.push_back(4);
  EXPECT_EQ(*it, 2);

  list.erase(list.begin());
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, performance) {
  ListInt list;
  for (int i = 0; i < 10000; ++i) {
    list.push_back(i);
  }

  auto start = std::chrono::steady_clock::now();
  for (auto it = list.begin(); it != list.end(); ++it) {
  }
  auto end = std::chrono::steady_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  EXPECT_LT(duration.count(), 100);
}

TEST(ListTest, range_based_for) {
  ListInt list = {1, 2, 3, 4, 5};
  int sum = 0;
  for (int x : list) {
    sum += x;
  }
  EXPECT_EQ(sum, 15);
}

TEST(ListTest, splice) {
  ListInt a = {1, 4};
  ListInt b = {2, 3};
  a.splice(++a.begin(), b);
  std::list<int> expected = {1, 2, 3, 4};
  EXPECT_TRUE(lists_equal(a, expected));
  EXPECT_TRUE(b.empty());
}
