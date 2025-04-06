#include <gtest/gtest.h>

#include <climits>

#include "../s21_map.h"

namespace s21 {

TEST(RBTreeOtherTests, copy_constructor) {
  map<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree1.insert(3, "three");

  map<int, std::string> tree2(tree1);

  ASSERT_EQ(tree2.size(), 3);
  ASSERT_TRUE(tree2.contains(1));
  ASSERT_TRUE(tree2.contains(2));
  ASSERT_TRUE(tree2.contains(3));

  tree2.erase(2);
  ASSERT_EQ(tree2.size(), 2);
  ASSERT_EQ(tree1.size(), 3);
  ASSERT_TRUE(tree1.contains(2));
}

TEST(RBTreeOtherTests, default_constructor) {
  map<int, std::string> map;
  ASSERT_EQ(map.size(), 0);
  ASSERT_TRUE(map.empty());
}

TEST(RBTreeOtherTests, assignment) {
  map<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree1.insert(3, "three");

  map<int, std::string> tree2;
  tree2 = tree1;

  ASSERT_EQ(tree2.size(), 3);
  ASSERT_TRUE(tree2.contains(1));
  ASSERT_TRUE(tree2.contains(2));
  ASSERT_TRUE(tree2.contains(3));

  tree2.erase(2);
  ASSERT_EQ(tree2.size(), 2);
  ASSERT_EQ(tree1.size(), 3);
  ASSERT_TRUE(tree1.contains(2));
}

TEST(RBTreeOtherTests, assignment_to_self) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  size_t initial_size = map.size();

  map = map;

  ASSERT_EQ(map.size(), initial_size);
  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
}

TEST(RBTreeOtherTests, find_existing) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
}

TEST(RBTreeOtherTests, find_non_existing) {
  map<int, std::string> map;
  map.insert(1, "one");

  ASSERT_FALSE(map.contains(2));
}

TEST(RBTreeOtherTests, clear) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.insert(3, "three");

  map.clear();

  ASSERT_EQ(map.size(), 0);
  ASSERT_TRUE(map.empty());
  ASSERT_EQ(map.begin(), map.end());
}

TEST(RBTreeOtherTests, empty_not_empty) {
  map<int, std::string> map;

  ASSERT_TRUE(map.empty());
  ASSERT_EQ(map.size(), 0);

  map.insert(1, "one");
  ASSERT_FALSE(map.empty());
  ASSERT_EQ(map.size(), 1);

  map.erase(1);
  ASSERT_TRUE(map.empty());
  ASSERT_EQ(map.size(), 0);
}

TEST(RBTreeOtherTests, contains) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
  ASSERT_FALSE(map.contains(3));
}

TEST(RBTreeOtherTests, balance) {
  map<int, int> map;
  const int num_elements = 1000;
  for (int i = 0; i < num_elements; ++i) {
    map.insert(i, i);
  }
  ASSERT_EQ(map.size(), num_elements);
}

TEST(RBTreeOtherTests, extreme_values) {
  map<int, std::string> map;
  map.insert(INT_MIN, "min");
  map.insert(INT_MAX, "max");

  ASSERT_TRUE(map.contains(INT_MIN));
  ASSERT_TRUE(map.contains(INT_MAX));
  ASSERT_TRUE(map.contains(INT_MIN));
  ASSERT_TRUE(map.contains(INT_MAX));

  map.erase(INT_MIN);
  ASSERT_FALSE(map.contains(INT_MIN));
  map.erase(INT_MAX);
  ASSERT_FALSE(map.contains(INT_MAX));
}

TEST(RBTreeSwapTests, swap_empty_trees) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.swap(tree2);

  ASSERT_TRUE(tree1.empty());
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQ(tree1.size(), 0);
  ASSERT_EQ(tree2.size(), 0);
}

TEST(RBTreeSwapTests, swap_empty_with_non_empty) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree2.insert(1, "one");
  tree2.insert(2, "two");

  tree1.swap(tree2);

  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(2));
  ASSERT_FALSE(tree2.contains(1));
  ASSERT_FALSE(tree2.contains(2));
  ASSERT_EQ(tree1.size(), 2);
  ASSERT_EQ(tree2.size(), 0);
  ASSERT_TRUE(tree2.empty());
}

TEST(RBTreeSwapTests, swap_non_empty_empty_with) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.insert(1, "one");
  tree1.insert(2, "two");

  tree1.swap(tree2);

  ASSERT_TRUE(tree2.contains(1));
  ASSERT_TRUE(tree2.contains(2));
  ASSERT_FALSE(tree1.contains(1));
  ASSERT_FALSE(tree1.contains(2));
  ASSERT_EQ(tree2.size(), 2);
  ASSERT_EQ(tree1.size(), 0);
  ASSERT_TRUE(tree1.empty());
}

TEST(RBTreeSwapTests, swap_non_empty) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree2.insert(3, "three");
  tree2.insert(4, "four");

  tree1.swap(tree2);

  ASSERT_TRUE(tree1.contains(3));
  ASSERT_TRUE(tree1.contains(4));
  ASSERT_TRUE(tree2.contains(1));
  ASSERT_TRUE(tree2.contains(2));

  ASSERT_FALSE(tree1.contains(1));
  ASSERT_FALSE(tree1.contains(2));
  ASSERT_FALSE(tree2.contains(3));
  ASSERT_FALSE(tree2.contains(4));

  ASSERT_EQ(tree1.size(), 2);
  ASSERT_EQ(tree2.size(), 2);
}

//
TEST(RBTreeSwapTests, swap_self) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  size_t initial_size = map.size();
  bool contains_1_before = map.contains(1);
  bool contains_2_before = map.contains(2);

  auto begin_before = map.begin();
  auto end_before = map.end();

  map.swap(map);

  ASSERT_EQ(map.size(), initial_size);
  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
  ASSERT_EQ(map.contains(1), contains_1_before);
  ASSERT_EQ(map.contains(2), contains_2_before);

  auto begin_after = map.begin();
  auto end_after = map.end();

  ASSERT_EQ(begin_before == begin_after, true);
  ASSERT_EQ(end_before == end_after, true);
}

TEST(RBTreeSwapTests, SwapComplex) {
  map<int, int> tree1;
  map<int, int> tree2;

  // 1. Обмен пустых деревьев (ничего не должно сломаться)

  tree1.swap(tree2);

  EXPECT_TRUE(tree1.empty());
  EXPECT_TRUE(tree2.empty());

  // 2. Заполняем одно дерево, другое оставляем пустым
  std::vector<int> values1 = {50, 30, 70, 20, 40, 60, 80};
  for (int v : values1) tree1.insert(v, v);

  tree1.swap(tree2);

  EXPECT_TRUE(tree1.empty());
  for (int v : values1) EXPECT_TRUE(tree2.contains(v));

  // 3. Заполняем оба дерева разными значениями
  std::vector<int> values2 = {100, 90, 110};
  for (int v : values2) tree1.insert(v, v);

  tree1.swap(tree2);

  // 4. Проверка, что деревья обменялись значениями
  for (int v : values1) EXPECT_TRUE(tree1.contains(v));
  for (int v : values2) EXPECT_TRUE(tree2.contains(v));

  // 5. Проверяем итераторы
  auto it = tree1.begin();
  EXPECT_EQ(it->first, 20);
  ++it;
  EXPECT_EQ(it->first, 30);

  it = tree2.begin();
  EXPECT_EQ(it->first, 90);
  ++it;
  EXPECT_EQ(it->first, 100);
}

TEST(RBTreeSwapTests, swap_different) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree2.insert(3, "three");
  tree2.insert(4, "four");
  tree1.swap(tree2);

  map<int, std::string>::iterator it1 = tree1.begin();
  map<int, std::string>::iterator it2 = tree2.begin();
  ASSERT_EQ(it1->first, 3);
  ASSERT_EQ(it2->first, 1);
}

TEST(RBTreeSwapTests, check_after_swap) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.insert(2, "two");
  tree1.insert(1, "one");
  tree2.insert(4, "four");
  tree2.insert(3, "three");

  tree1.swap(tree2);

  ASSERT_EQ(tree1.begin()->first, 3);
  ASSERT_EQ(tree2.begin()->first, 1);

  auto it1 = tree1.end();
  auto it2 = tree2.end();
  it1--;
  it2--;

  ASSERT_EQ(it1->first, 4);
  ASSERT_EQ(it2->first, 2);
}

}  // namespace s21
