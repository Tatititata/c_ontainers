#include <gtest/gtest.h>

#include <climits>

#include "../lace_map.h"

namespace lace {

TEST(RBTreeOtherTests, CopyConstructor) {
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

TEST(RBTreeOtherTests, DefaultConstructor) {
  map<int, std::string> map;
  ASSERT_EQ(map.size(), 0);
  ASSERT_TRUE(map.empty());
}

TEST(RBTreeOtherTests, Assignment) {
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

TEST(RBTreeOtherTests, AssignmentToSelf) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  size_t initial_size = map.size();

  map = map;

  ASSERT_EQ(map.size(), initial_size);
  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
}

TEST(RBTreeOtherTests, FindExisting) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
}

TEST(RBTreeOtherTests, FindNonExisting) {
  map<int, std::string> map;
  map.insert(1, "one");

  ASSERT_FALSE(map.contains(2));
}

TEST(RBTreeOtherTests, Clear) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.insert(3, "three");

  map.clear();

  ASSERT_EQ(map.size(), 0);
  ASSERT_TRUE(map.empty());
  ASSERT_EQ(map.begin(), map.end());
}

TEST(RBTreeOtherTests, EmptyNotEmpty) {
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

TEST(RBTreeOtherTests, Contains) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
  ASSERT_FALSE(map.contains(3));
}

TEST(RBTreeOtherTests, Balance) {
  map<int, int> map;
  const int num_elements = 1000;
  for (int i = 0; i < num_elements; ++i) {
    map.insert(i, i);
  }
  ASSERT_EQ(map.size(), num_elements);
}

TEST(RBTreeOtherTests, ExtremeValues) {
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

TEST(RBTreeSwapTests, SwapEmptyTrees) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.swap(tree2);

  ASSERT_TRUE(tree1.empty());
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQ(tree1.size(), 0);
  ASSERT_EQ(tree2.size(), 0);
}

TEST(RBTreeSwapTests, SwapEmptyWithNonEmpty) {
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

TEST(RBTreeSwapTests, SwapNonEmptyEmptyWith) {
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

TEST(RBTreeSwapTests, SwapNonEmpty) {
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

TEST(RBTreeSwapTests, SwapSelf) {
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

TEST(RBTreeOtherTests, erase_by_key) {
  map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");

  EXPECT_EQ(tree.size(), 3);
  tree.erase(2);
  EXPECT_EQ(tree.size(), 2);

  auto it = tree.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 3);
}

TEST(RBTreeOtherTests, IteratorDecrementCoversPrevNode) {
  map<int, int> tree;
  tree.insert(50, 0);
  tree.insert(30, 0);
  tree.insert(40, 0);
  tree.insert(20, 0);

  const map<int, int> const_tree = tree;

  auto it = tree.find(40);
  --it;
  EXPECT_EQ(it->first, 30);
  it = tree.find(20);
  --it;
  EXPECT_EQ(it, tree.end());
  it = tree.find(30);
  --it;
  EXPECT_EQ(it->first, 20);

  auto const_it = const_tree.find(40);
  --const_it;
  EXPECT_EQ(const_it->first, 30);
  const_it = tree.find(20);
  --const_it;
  EXPECT_EQ(const_it, tree.end());
  const_it = tree.find(30);
  --const_it;
  EXPECT_EQ(const_it->first, 20);
}

TEST(RBTreeOtherTests, EraseEndIterator) {
  map<int, int> tree;
  tree.insert(10, 100);
  auto it = tree.end();
  auto result = tree.erase(it);
  EXPECT_EQ(result, tree.end());
  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(tree.at(10), 100);
}

TEST(RBTreeOtherTests, IteratorDecrementComplexCases) {
  map<int, int> tree;

  tree.insert(50, 0);
  tree.insert(30, 0);
  tree.insert(70, 0);
  tree.insert(20, 0);
  tree.insert(40, 0);
  tree.insert(35, 0);

  const map<int, int> const_tree = tree;

  auto it = tree.find(40);
  auto const_it = const_tree.find(40);
  --it;
  --const_it;
  EXPECT_EQ(it->first, 35);
  EXPECT_EQ(const_it->first, 35);
  it = tree.find(20);
  const_it = const_tree.find(20);
  --it;
  --const_it;
  EXPECT_EQ(it, tree.end());
  EXPECT_EQ(const_it, const_tree.end());
  it = tree.find(35);
  EXPECT_EQ(it->first, 35);
  const_it = const_tree.find(35);
  EXPECT_EQ(const_it->first, 35);
}

TEST(MapIteratorTest, PrevNodeInValidRBT) {
  map<int, int> m;

  m.insert(10, 0);
  m.insert(5, 0);
  m.insert(15, 0);
  m.insert(7, 0);

  const map<int, int> const_tree = m;
  auto it = m.find(10);
  --it;
  EXPECT_EQ(it->first, 7);

  auto const_it = const_tree.find(10);
  const_it--;
  EXPECT_EQ(const_it->first, 7);
}

TEST(MapIteratorTest, DereferenceEndIteratorThrows) {
  map<int, int> m;
  m.insert(1, 0);

  auto it = m.end();
  EXPECT_THROW(*it, std::runtime_error);
  EXPECT_THROW(it.operator->(), std::runtime_error);
}

TEST(MapIteratorTest, ConstDereference) {
  const map<int, int> m = {{1, 100}};
  const auto it1 = m.begin();
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 100);

  const auto it2 = m.end();
  EXPECT_THROW(*it2, std::runtime_error);
}

TEST(MapIteratorTest, ConstDereferenceEndIteratorThrows) {
  map<int, int> m;
  m.insert(1, 0);
  const auto it = m.end();
  EXPECT_THROW(*it, std::runtime_error);
}

TEST(MapAtTest, ExistingKeyReturnsValue) {
  map<int, int> m;
  m.insert(1, 0);

  EXPECT_EQ(m.at(1), 0);
}

TEST(MapAtTest, MissingKeyThrowsException) {
  map<int, int> m;
  EXPECT_THROW(m.at(42), std::out_of_range);
}

TEST(MapAtTest, ConstVersionThrowsOnMissingKey) {
  const map<int, int> m = {{1, 0}};
  EXPECT_EQ(m.at(1), 0);
  EXPECT_THROW(m.at(2), std::out_of_range);
}

TEST(MapIteratorTest, ConstIteratorDereference) {
  const map<int, int> m = {{1, 0}};
  const auto it = m.begin();
  const std::pair<const int, int> expected{1, 0};

  EXPECT_EQ(it->first, expected.first);
  EXPECT_EQ(it->second, expected.second);
}

TEST(MapLowerBoundTest, NotInLeftSubtree) {
  map<int, int> m = {{5, 0}, {3, 0}, {7, 0}};
  auto it = m.lower_bound(4);
  EXPECT_EQ(it->first, 5);
}

TEST(MapLowerBoundTest, NotInRightSubtree) {
  map<int, int> m = {{5, 0}, {3, 0}, {7, 0}};
  auto it = m.lower_bound(6);
  EXPECT_EQ(it->first, 7);
}

TEST(MapLowerBoundTest, KeyGreater) {
  map<int, int> m = {{5, 0}, {3, 0}, {7, 0}};
  auto it = m.lower_bound(10);
  EXPECT_EQ(it, m.end());
}

TEST(MapConstIteratorTest, RightSubtreeLeftChild) {
  const map<int, int> m = {{5, 0}, {3, 0}, {7, 0}, {6, 0}};
  auto it = m.find(5);
  ++it;
  EXPECT_EQ(it->first, 6);
}

TEST(MapConstIteratorTest, LeftSubtreeRightChild) {
  const map<int, int> m = {{5, 0}, {3, 0}, {4, 0}, {7, 0}};
  auto it = m.find(5);
  --it;
  EXPECT_EQ(it->first, 4);
}

TEST(MapAtTest, ConstAtReturnsCorrectValue) {
  const map<int, int> m = {{1, 0}};
  EXPECT_EQ(m.at(1), 0);
}

TEST(MapIteratorTest, DecrementNullIteratorThrows) {
  map<int, int> m;
  auto it = m.end();
  EXPECT_THROW(--it, std::runtime_error);
}

TEST(MapLowerBoundTest, ConstLowerBoundFullCoverage) {
  const map<int, int> m = {{10, 1}, {5, 2}, {15, 3}, {12, 4}};
  auto it1 = m.lower_bound(7);
  EXPECT_EQ(it1->first, 10);
  auto it2 = m.lower_bound(13);
  EXPECT_EQ(it2->first, 15);
  auto it3 = m.lower_bound(20);
  EXPECT_EQ(it3, m.end());
}

TEST(MapIteratorTest, ConstIteratorGetCurrent) {
  const map<int, int> m = {{1, 10}};

  const auto it1 = m.begin();
  EXPECT_NE(it1.get_current(), nullptr);

  const auto it2 = m.end();
  EXPECT_EQ(it2.get_current(), nullptr);
}

TEST(MapIteratorTest, ConstIteratorPrevNodeWithRightSubtree) {
  const map<int, int> m = {{5, 0}, {3, 0}, {7, 0}, {4, 0}};
  auto it = m.find(5);
  --it;

  EXPECT_EQ(it->first, 4);
}

TEST(MapConstIteratorTest, NextNodeWithParentClimb) {
  const map<int, int> m = {{5, 0}, {3, 0}, {7, 0}, {8, 0}};
  auto it = m.find(8);
  EXPECT_EQ(it->first, 8);
  ++it;
  EXPECT_EQ(it, m.end());
}

TEST(MapIteratorTest, ConstNextNodeFullCoverage) {
  const lace::map<int, int> m = {{30, 0}, {20, 0}, {40, 0}, {25, 0}};
  lace::map<int, int>::const_iterator it = m.find(25);
  const auto& value = *it;
  EXPECT_EQ(value.first, 25);

  ++it;
  EXPECT_EQ(it->first, 30);
}

}  // namespace lace
