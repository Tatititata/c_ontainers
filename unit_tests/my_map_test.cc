#include <gtest/gtest.h>

#include "../lace_map.h"

using lace::map;
using MapType = map<int, std::string>;

TEST(laceMapTest, EmptyMap) {
  MapType my_map;
  EXPECT_EQ(my_map.size(), 0);
  EXPECT_TRUE(my_map.begin() == my_map.end());
}

TEST(laceMapTest, InsertValueType) {
  MapType my_map;
  auto [it, inserted] = my_map.insert({1, "one"});

  EXPECT_TRUE(inserted);
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  EXPECT_EQ(my_map.size(), 1);
}

TEST(laceMapTest, InsertKeyValue) {
  MapType my_map;
  auto [it, inserted] = my_map.insert(2, "two");

  EXPECT_TRUE(inserted);
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");
  EXPECT_EQ(my_map.size(), 1);
}

TEST(laceMapTest, InsertDuplicate) {
  MapType my_map;
  my_map.insert(1, "one");
  auto [it, inserted] = my_map.insert(1, "uno");

  EXPECT_FALSE(inserted);
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
  EXPECT_EQ(my_map.size(), 1);
}

TEST(laceMapTest, InsertOrAssign) {
  MapType my_map;
  my_map.insert(1, "one");
  auto [it, inserted] = my_map.insert_or_assign(1, "uno");

  EXPECT_FALSE(inserted);
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "uno");
  EXPECT_EQ(my_map.size(), 1);
}

TEST(laceMapTest, InsertOrAssignNewKey) {
  MapType my_map;
  auto [it, inserted] = my_map.insert_or_assign(3, "three");

  EXPECT_TRUE(inserted);
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");
  EXPECT_EQ(my_map.size(), 1);
}