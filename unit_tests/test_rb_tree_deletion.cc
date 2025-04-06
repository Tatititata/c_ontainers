#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../s21_map.h"

TEST(RBTreeTestErase, erase_non_existent_key) {
  s21::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");

  EXPECT_EQ(tree.size(), 3);
  tree.erase(4);
  EXPECT_EQ(tree.size(), 3);

  auto it = tree.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 2);
  ++it;
  EXPECT_EQ((*it).first, 3);
}

TEST(RBTreeTestErase, erase_all_elements) {
  s21::map<int, std::string> tree;
  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");

  EXPECT_EQ(tree.size(), 3);
  tree.erase(1);
  EXPECT_EQ(tree.size(), 2);
  tree.erase(2);
  EXPECT_EQ(tree.size(), 1);
  tree.erase(3);
  EXPECT_EQ(tree.size(), 0);

  EXPECT_EQ(tree.begin(), tree.end());
}

TEST(RBTreeTestErase, erase_from_empty_tree) {
  s21::map<int, std::string> tree;

  EXPECT_EQ(tree.size(), 0);
  tree.erase(1);
  EXPECT_EQ(tree.size(), 0);

  EXPECT_EQ(tree.begin(), tree.end());
}

TEST(RBTreeTestErase, big_insert_erase) {
  s21::map<int, int> tree;
  for (size_t i = 0; i < 1000; i++) tree.insert(i, i);
  EXPECT_EQ(tree.size(), 1000);
  for (size_t i = 0; i < 1000; i++) tree.erase(i);
  EXPECT_EQ(tree.size(), 0);

  EXPECT_EQ(tree.begin(), tree.end());
}

TEST(RBTreeMergeTests, max_size) {
  s21::map<int, int> tree;
  s21::map<int, int> std_tree;
  EXPECT_GE(tree.max_size(), std_tree.max_size());
}

TEST(RBTree, force_fix_right_child) {
  s21::map<int, int> tree;
  tree.insert({5000, 0});
  tree.insert({2000, 0});
  tree.insert({3000, 0});
  tree.insert({4000, 0});
  tree.insert({8000, 0});
  tree.insert({7000, 0});
  tree.insert({6000, 0});
  tree.insert({8700, 0});
  tree.insert({8500, 0});
  tree.insert({8900, 0});
  tree.insert({9000, 0});

  tree.erase(8500);
  tree.erase(8700);
  tree.erase(8900);
  tree.erase(9000);
  tree.erase(7000);
  tree.erase(8000);

  ASSERT_TRUE(tree.contains(2000));
}

TEST(RBTree, huge_deletion) {
  s21::map<int, int> tree;
  std::vector<int> vec;
  for (size_t i = 0; i < 10000; ++i) {
    vec.push_back(i);
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(vec.begin(), vec.end(), gen);

  for (int num : vec) {
    tree.insert({num, num});
    ASSERT_TRUE(tree.is_valid_rb_tree());
  }
  std::shuffle(vec.begin(), vec.end(), gen);
  for (int num : vec) {
    tree.erase(num);
    ASSERT_TRUE(tree.is_valid_rb_tree());
  }

  ASSERT_TRUE(tree.empty());
}

TEST(RBTree, complex_deletion_case_3_and_4) {
  s21::map<int, int> tree;

  tree.insert({10, 10});
  tree.insert({5, 5});
  tree.insert({15, 15});
  tree.insert({3, 3});
  tree.insert({7, 7});
  tree.insert({12, 12});
  tree.insert({20, 20});
  tree.insert({1, 1});

  tree.erase(1);
  tree.erase(3);
  tree.erase(7);
  tree.erase(5);

  ASSERT_TRUE(tree.size() == 4);
}

TEST(RBTree, fix_deletion_case_3_1) {
  s21::map<int, int> tree;

  tree.insert({30, 30});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({35, 35});
  tree.insert({45, 45});
  tree.insert({25, 25});

  tree.erase(20);

  ASSERT_TRUE(tree.size() == 5);
}

TEST(RBTree, fix_deletion_case_3_2) {
  s21::map<int, int> tree;

  tree.insert({30, 30});
  tree.insert({40, 40});
  tree.insert({20, 20});
  tree.insert({15, 15});
  tree.insert({25, 25});
  tree.insert({35, 35});

  tree.erase(40);

  ASSERT_TRUE(tree.size() == 5);
}

TEST(RBTree, fix_deletion_case_3_3) {
  s21::map<int, int> tree;

  tree.insert({30, 30});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({10, 10});
  tree.insert({25, 25});
  tree.insert({35, 35});
  tree.insert({50, 50});
  tree.insert({23, 23});

  tree.erase(10);

  ASSERT_TRUE(tree.size() == 7);
}
TEST(RBTree, fix_deletion_case_3_4) {
  s21::map<int, int> tree;
  tree.insert({30, 30});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({10, 10});
  tree.insert({25, 25});
  tree.insert({35, 35});
  tree.insert({50, 50});
  tree.insert({23, 23});

  tree.erase(35);

  ASSERT_TRUE(tree.size() == 7);
}

TEST(RBTree, fix_deletion_case_3_5) {
  s21::map<int, int> tree;
  tree.insert({50, 50});
  tree.insert({30, 30});
  tree.insert({70, 70});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({60, 60});
  tree.insert({80, 80});
  tree.insert({35, 35});
  tree.insert({45, 45});
  tree.erase(20);

  ASSERT_TRUE(tree.size() == 8);
}

TEST(RBTree, fix_deletion_case_3_6) {
  s21::map<int, int> tree;
  tree.insert({50, 50});
  tree.insert({30, 30});
  tree.insert({70, 70});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({60, 60});
  tree.insert({80, 80});
  tree.insert({35, 35});
  tree.insert({45, 45});
  tree.erase(20);
  ASSERT_TRUE(tree.size() == 8);
}

TEST(RBTree, fix_deletion_case_3_7) {
  s21::map<int, int> tree;
  tree.insert({30, 30});
  tree.insert({20, 20});
  tree.insert({40, 40});
  tree.insert({10, 10});
  tree.insert({25, 25});
  tree.insert({35, 35});
  tree.insert({50, 50});
  tree.insert({23, 23});
  tree.insert({28, 28});
  tree.erase(10);
  ASSERT_TRUE(tree.size() == 8);
}

TEST(RBTree, huge_clear) {
  s21::map<int, int> tree;
  std::vector<int> vec;
  for (size_t i = 0; i < 10000; ++i) {
    tree.insert({i, i});
  }
  tree.clear();
  ASSERT_TRUE(tree.empty());
}
