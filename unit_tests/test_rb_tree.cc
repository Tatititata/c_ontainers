#include <gtest/gtest.h>

#include "../s21_map.h"

class RBTreeTest : public ::testing::Test {
 protected:
  s21::map<int, std::string> tree;

  void SetUp() override {
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");
    tree.insert(15, "fifteen");
    tree.insert(25, "twenty-five");
  }

  void TearDown() override { tree.clear(); }
};

TEST_F(RBTreeTest, erase_by_key) {
  s21::map<int, std::string> tree;
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
