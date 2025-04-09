#include <gtest/gtest.h>

#include "../lace_map.h"

TEST(RBTreeIteratorTest, increment_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  auto it = tree.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 2);
  ++it;
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ(it, tree.end());
}

TEST(RBTreeIteratorTest, decrement_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  auto it = tree.end();
  --it;
  EXPECT_EQ((*it).first, 3);
  --it;
  EXPECT_EQ((*it).first, 2);
  --it;
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ(it, tree.begin());
}

TEST(RBTreeIteratorTest, dereference_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  auto it = tree.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, "one");
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, "two");
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
}

TEST(RBTreeIteratorTest, comparison_operators) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  auto it1 = tree.begin();
  auto it2 = tree.begin();
  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
  it2 = tree.end();
  EXPECT_NE(it1, it2);
}

TEST(RBTreeConstIteratorTest, increment_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  const auto& const_tree = tree;
  auto it = const_tree.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 2);
  ++it;
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ(it, const_tree.end());
}

TEST(RBTreeConstIteratorTest, decrement_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  const auto& const_tree = tree;
  auto it = const_tree.end();
  --it;
  EXPECT_EQ((*it).first, 3);
  --it;
  EXPECT_EQ((*it).first, 2);
  --it;
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ(it, const_tree.begin());
}

TEST(RBTreeConstIteratorTest, dereference_operator) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  const auto& const_tree = tree;
  auto it = const_tree.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, "one");
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, "two");
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
}

TEST(RBTreeConstIteratorTest, comparison_operators) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  const auto& const_tree = tree;
  auto it1 = const_tree.begin();
  auto it2 = const_tree.begin();
  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
  it2 = const_tree.end();
  EXPECT_NE(it1, it2);
}

TEST(RBTreeIteratorTest, partial_reverse_1) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  tree.insert(4, "four");
  tree.insert(5, "five");
  auto it = tree.end();
  --it;
  EXPECT_EQ((*it).first, 5);
  EXPECT_EQ((*it).second, "five");
  --it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  --it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
}

TEST(RBTreeIteratorTest, partial_reverse_traversal_2) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  tree.insert(4, "four");
  tree.insert(5, "five");
  auto it = tree.end();
  --it;
  EXPECT_EQ((*it).first, 5);
  EXPECT_EQ((*it).second, "five");
  --it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  --it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
  --it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, "two");
}

TEST(RBTreeIteratorTest, partial_reverse_3) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  tree.insert(4, "four");
  tree.insert(5, "five");
  auto it = tree.end();
  --it;
  EXPECT_EQ((*it).first, 5);
  EXPECT_EQ((*it).second, "five");
  --it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  ++it;
  EXPECT_EQ((*it).first, 5);
  EXPECT_EQ((*it).second, "five");
  --it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  --it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
}

TEST(RBTreeIteratorTest, partial_reverse_4) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");
  tree.insert(4, "four");
  tree.insert(5, "five");
  auto it = tree.end();
  --it;
  EXPECT_EQ((*it).first, 5);
  EXPECT_EQ((*it).second, "five");
  --it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  --it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
  ++it;
  EXPECT_EQ((*it).first, 4);
  EXPECT_EQ((*it).second, "four");
  --it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
  --it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, "two");
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, "three");
}

TEST(RBTreeIteratorTest, erase_first_element) {
  lace::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");

  auto it = tree.begin();
  tree.erase(it);

  EXPECT_EQ(tree.begin()->first, 2);
  EXPECT_EQ(tree.size(), 1);
}

TEST(RBTreeIteratorTest, erase_last_element) {
  lace::map<int, std::string> tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});

  auto it = tree.begin();
  ++it;
  tree.erase(it);

  EXPECT_EQ(tree.begin()->first, 1);
  EXPECT_EQ(tree.size(), 1);
}

TEST(RBTreeIteratorTest, erase_by_iterator) {
  lace::map<int, std::string> tree;

  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({3, "three"});
  tree.insert({4, "four"});
  tree.insert({5, "five"});

  auto it1 = tree.begin();
  auto it2 = tree.begin();

  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it2).first, 1);

  ++it2;
  tree.erase(it2);

  EXPECT_EQ((*it1).first, 1);

  ++it1;
  EXPECT_EQ((*it1).first, 3);

  ++it2;
  tree.erase(it2);

  EXPECT_EQ((*it1).first, 3);

  ++it1;
  EXPECT_EQ((*it1).first, 5);

  ++it1;
  EXPECT_EQ(it1, tree.end());

  auto it = tree.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ((*it).first, 5);
  ++it;
  EXPECT_EQ(it, tree.end());
}

TEST(RBTreeIteratorTest, iterator_and_swap) {
  lace::map<int, int> first;
  lace::map<int, int> second;

  first.insert(1, 2);
  first.insert(3, 4);
  second.insert(5, 6);
  second.insert(7, 8);
  auto it = first.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 2);
  first.swap(second);
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, 4);
  ++it;
  EXPECT_EQ(it, second.end());
}

TEST(RBTreeIteratorTest, iterator_and_swap_denis) {
  lace::map<int, int> first;
  lace::map<int, int> second;

  first.insert(1, 1);
  auto it = first.begin();
  first.swap(second);

  second.insert(2, 2);

  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 1);

  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ(it, second.end());
}