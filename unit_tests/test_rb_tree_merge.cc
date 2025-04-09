#include <gtest/gtest.h>

#include "../lace_map.h"

using namespace lace;
TEST(RBTreeMergeTests, merge_empty_with_empty) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;

  tree1.merge(tree2);

  ASSERT_TRUE(tree1.empty());
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQ(tree1.size(), 0);
  ASSERT_EQ(tree2.size(), 0);
}

TEST(RBTreeMergeTests, merge_non_empty_with_empty) {
  map<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  map<int, std::string> tree2;

  tree1.merge(tree2);

  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQ(tree1.size(), 2);
  ASSERT_EQ(tree2.size(), 0);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(2));
}

TEST(RBTreeMergeTests, merge_self) {
  map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");

  map.merge(map);

  ASSERT_EQ(map.size(), 2);
  ASSERT_TRUE(map.contains(1));
  ASSERT_TRUE(map.contains(2));
}

TEST(RBTreeMergeTests, merge_empty_with_non_empty) {
  map<int, std::string> tree1;
  map<int, std::string> tree2;
  tree2.insert(1, "one");
  tree2.insert(2, "two");

  tree1.merge(tree2);

  ASSERT_FALSE(tree1.empty());
  ASSERT_TRUE(tree2.empty());
  ASSERT_EQ(tree1.size(), 2);
  ASSERT_EQ(tree2.size(), 0);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(2));
}

TEST(RBTreeMergeTests, merge_non_overlapping_trees) {
  map<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  map<int, std::string> tree2;
  tree2.insert(3, "three");
  tree2.insert(4, "four");

  tree1.merge(tree2);

  ASSERT_EQ(tree1.size(), 4);
  ASSERT_EQ(tree2.size(), 0);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(2));
  ASSERT_TRUE(tree1.contains(3));
  ASSERT_TRUE(tree1.contains(4));
}

TEST(RBTreeMergeTests, merge_overlapping_trees) {
  map<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree1.insert(3, "three");

  map<int, std::string> tree2;
  tree2.insert(2, "new_two");
  tree2.insert(4, "four");

  tree1.merge(tree2);

  ASSERT_EQ(tree1.size(), 4);
  ASSERT_EQ(tree2.size(), 1);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(3));
  ASSERT_TRUE(tree1.contains(4));
}

TEST(RBTreeMergeTests, merge_big_trees) {
  map<int, int> tree1;
  for (size_t i = 0; i < 1000; i += 2) tree1.insert(i, i);

  map<int, int> tree2;
  for (size_t i = 0; i < 1000; i += 2) tree2.insert(i + 1, i + 1);

  tree1.merge(tree2);

  ASSERT_EQ(tree1.size(), 1000);
  ASSERT_EQ(tree2.size(), 0);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree1.contains(999));
  ASSERT_TRUE(tree1.contains(998));
}

TEST(RBTreeMergeTests, merge_big_full_overlapping) {
  map<int, int> tree1;
  map<int, int> tree2;
  for (size_t i = 0; i < 1000; i++) {
    tree1.insert(i, i);
    tree2.insert(i, i);
  }

  tree1.merge(tree2);

  ASSERT_EQ(tree1.size(), 1000);
  ASSERT_EQ(tree2.size(), 1000);
  ASSERT_TRUE(tree1.contains(1));
  ASSERT_TRUE(tree2.contains(1));
  ASSERT_TRUE(tree1.contains(999));
  ASSERT_TRUE(tree2.contains(999));
  ASSERT_FALSE(tree1.contains(1000));
  ASSERT_FALSE(tree2.contains(1000));
}