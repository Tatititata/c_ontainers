#include <gtest/gtest.h>

#include "../s21_map.h"

class RBTreeOfTreesTest : public ::testing::Test {
 protected:
  s21::map<int, s21::map<int, int>> tree;

  void SetUp() override {
    s21::map<int, int> inner_tree_10;
    inner_tree_10.insert(100, 1000);
    inner_tree_10.insert(200, 2000);

    s21::map<int, int> inner_tree_20;
    inner_tree_20.insert(150, 1500);
    inner_tree_20.insert(250, 2500);

    s21::map<int, int> inner_tree_30;
    inner_tree_30.insert(300, 3000);
    inner_tree_30.insert(350, 3500);

    s21::map<int, int> inner_tree_15;
    inner_tree_15.insert(120, 1200);
    inner_tree_15.insert(220, 2200);

    s21::map<int, int> inner_tree_25;
    inner_tree_25.insert(180, 1800);
    inner_tree_25.insert(280, 2800);

    tree.insert(10, inner_tree_10);
    tree.insert(20, inner_tree_20);
    tree.insert(30, inner_tree_30);
    tree.insert(15, inner_tree_15);
    tree.insert(25, inner_tree_25);
  }

  void TearDown() override { tree.clear(); }
};

TEST_F(RBTreeOfTreesTest, insert_and_find_tree_value) {
  auto found_tree = tree[10];
  EXPECT_EQ(found_tree[100], 1000);
  EXPECT_EQ(found_tree[200], 2000);

  EXPECT_THROW(found_tree.at(300), std::out_of_range);
}
