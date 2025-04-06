#include <gtest/gtest.h>

#include <map>
#include <random>
#include <utility>
#include <vector>

#include "../s21_map.h"

class IncreaseOnCreate {
 public:
  IncreaseOnCreate() { count++; }
  inline static int count = 0;
};

// заменить на s21::map
using MapInts = s21::map<int, int>;
using MapOnCreationObj = s21::map<int, IncreaseOnCreate>;
using MapIntString = s21::map<int, std::string>;
using MapStringInt = s21::map<std::string, int>;

// не менять на s21::map
using OriginalMapInts = std::map<int, int>;

bool checkMapsEqual(MapInts our_map, OriginalMapInts orig_map) {
  for (auto item : orig_map) {
    if (our_map[item.first] != item.second) return false;
  }
  for (auto item : our_map) {
    if (orig_map[item.first] != item.second) return false;
  }
  return true;
}

bool checkForwardIteratrion(MapInts map) {
  int key = map.begin()->first;
  for (auto item : map) {
    if (item.first < key) return false;
    key = item.first;
  }
  return true;
}

void IterateThrough(MapInts map) {
  auto start = std::chrono::steady_clock::now();
  for (auto item : map) {
    if (item.first == item.second) {
    }
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
      throw std::runtime_error("Timeout exceeded");
    }
  }
}

TEST(MapAccesOperators, AtOperator) {
  MapInts map = {{6, 10}};
  ASSERT_EQ(map.at(6), 10);
}

TEST(MapAccesOperators, BracketsOperator) {
  MapInts map = {{6, 10}};
  ASSERT_EQ(map[6], 10);
}

TEST(MapAccesOperators, BracketsOperatorOnEmptyIntsMap) {
  MapInts map;
  int i{};
  ASSERT_EQ(i, map[1]);
}

TEST(MapAccesOperators, BracketsOperatorOnEmptyStringMap) {
  MapIntString map;
  std::string s;
  ASSERT_EQ(s, map[1]);
}

TEST(MapAccesOperators, AtOperatorOnEmptyMap) {
  MapInts map;
  ASSERT_ANY_THROW(map.at(1));
}

TEST(MapIteratorTest, EmptyMap) {
  MapInts map;
  ASSERT_EQ(map.begin(), map.end());
}

TEST(MapIteratorTest, OneElement) {
  MapInts map = {{1, 1}};
  ASSERT_EQ(map.begin(), --map.end());
}

TEST(MapIteratorTest, SwapTwoNonEmpty) {
  MapInts first = {{1, 1}, {2, 2}};
  MapInts second = {{10, 10}, {20, 20}};

  auto iterator = first.begin();
  first.swap(second);
  iterator++;

  ASSERT_EQ(2, iterator->first);
  ASSERT_EQ(2, iterator->second);

  ASSERT_EQ(10, first.begin()->first);
  ASSERT_EQ(20, (--first.end())->first);
  ASSERT_EQ(10, first.begin()->second);
  ASSERT_EQ(20, (--first.end())->second);

  ASSERT_EQ(1, second.begin()->first);
  ASSERT_EQ(2, (--second.end())->first);
  ASSERT_EQ(1, second.begin()->second);
  ASSERT_EQ(2, (--second.end())->second);

  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(MapIteratorTest, OneEmptyMapCheckNonEmpty) {
  MapInts first = {{1, 1}};
  MapInts second;

  auto iterator = first.begin();
  first.swap(second);
  second.insert({2, 2});

  ASSERT_EQ((*iterator).first, 1);
  ASSERT_EQ((*iterator).second, 1);

  iterator++;
  ASSERT_EQ((*iterator).first, 2);
  ASSERT_EQ((*iterator).second, 2);

  iterator++;
  ASSERT_EQ(iterator, second.end());

  ASSERT_EQ(first.begin(), first.end());
}

TEST(MapIteratorTest, OneEmptyMapCheckFirstAndLoops) {
  MapInts first = {{1, 1}};
  MapInts second;

  first.swap(second);
  second.insert({2, 2});

  ASSERT_EQ(first.begin(), first.end());
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(MapIteratorTest, ForwardIteration) {
  MapInts map = {{1, 1}, {100, 2}, {3, 3}, {22, 2}, {9, 1}, {-5, 11}};
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({342, 99});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({-10, 21});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({21, 21});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({20, 11});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({-3, 21});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({447, 0});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.insert({0, 1});
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++(++(++map.begin())));
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(++map.begin());
  ASSERT_TRUE(checkForwardIteratrion(map));
  map.erase(--map.end());
  ASSERT_TRUE(checkForwardIteratrion(map));
}

TEST(MapCapacityTest, OneEmptySize) {
  MapInts first = {{1, 1}};
  MapInts second;

  first.swap(second);
  second.insert({2, 2});

  ASSERT_EQ(2, second.size());
  ASSERT_EQ(0, first.size());
}

TEST(MapCapacityTest, OneEmptyIsEmpty) {
  MapInts first = {{1, 1}};
  MapInts second;

  first.swap(second);
  second.insert({2, 2});

  ASSERT_FALSE(second.empty());
  ASSERT_TRUE(first.empty());
}

TEST(MapGeneralTest, InsertEraseSwapIterate) {
  MapInts first = {{1, 100}, {4, 100}, {2, 100}, {88, 3}};
  MapInts second = {{1, 33}, {100, 2}, {11, 39}, {66, 100}, {3, 20}, {44, 33}};

  auto iterator = ++first.begin();
  first.swap(second);
  second.erase(iterator);
  auto second_iterator = --second.end();
  first.swap(second);
  first.erase(second_iterator);

  OriginalMapInts first_expected = {{1, 100}, {4, 100}};
  OriginalMapInts second_expected = {{1, 33},   {100, 2}, {11, 39},
                                     {66, 100}, {3, 20},  {44, 33}};

  ASSERT_TRUE(checkMapsEqual(first, first_expected));
  ASSERT_TRUE(checkMapsEqual(second, second_expected));
  ASSERT_TRUE(checkForwardIteratrion(second));
}

TEST(MapGeneralTest, ExistingInsertTest) {
  MapInts map = {{1, 3}};
  ASSERT_NO_THROW(map.insert({1, 1}));
  ASSERT_EQ(1, map.size());
  ASSERT_EQ(3, map.begin()->second);
}

TEST(MapGeneralTest, ObjCreationTest) {
  MapOnCreationObj map;
  auto a = map[10];
  auto b = map[10];
  ASSERT_EQ(1, b.count);
  ASSERT_EQ(1, a.count);
}

TEST(MapConstructorsTest, CopyConstructor) {
  OriginalMapInts orig = {{8, 2}, {1, 4}, {9, 1}};
  MapInts map = {{8, 2}, {1, 4}, {9, 1}};
  MapInts copy(map);
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_TRUE(checkMapsEqual(copy, orig));
  ASSERT_EQ(3, map.size());
  ASSERT_EQ(3, copy.size());
}

TEST(MapConstructorsTest, MoveConstructor) {
  OriginalMapInts orig = {{8, 2}, {1, 4}, {9, 1}};
  MapInts map = {{8, 2}, {1, 4}, {9, 1}};
  MapInts copy = std::move(map);
  ASSERT_TRUE(checkMapsEqual(copy, orig));
  ASSERT_EQ(map.begin(), map.end());
  ASSERT_EQ(0, map.size());
  ASSERT_EQ(3, copy.size());
}

TEST(MapInsertTest, InsertOrAssignEmpty) {
  MapInts map;
  auto pair = map.insert_or_assign(1, 1);
  ASSERT_EQ(1, map.size());
  ASSERT_EQ(1, map.begin()->second);
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(map.begin(), pair.first);
}

TEST(MapInsertTest, InsertOrAssignNonEmptyExisting) {
  MapInts map = {{1, 3}};
  auto pair = map.insert_or_assign(1, 1);
  ASSERT_EQ(1, map.size());
  ASSERT_EQ(1, map.begin()->second);
  ASSERT_EQ(false, pair.second);
  ASSERT_EQ(map.begin(), pair.first);
}

TEST(MapInsertTest, InsertOrAssignNonEmptyNonExisting) {
  OriginalMapInts orig = {{6, 3}, {1, 1}};
  MapInts map = {{6, 3}};
  auto pair = map.insert_or_assign(1, 1);
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(map.begin(), pair.first);
}

TEST(MapInsertTest, InsertOrAssignNonEmptyNonExisting2) {
  OriginalMapInts orig = {{1, 3}, {2, 2}, {3, 3}, {4, 4}};
  MapInts map = {{1, 3}, {2, 2}, {4, 4}};
  auto pair = map.insert_or_assign(3, 3);
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(++(++map.begin()), pair.first);
}

TEST(MapInsertTest, InsertOrAssignNonEmptyExisting2) {
  OriginalMapInts orig = {{1, 3}, {2, 2}, {3, 3}, {4, 4}};
  MapInts map = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  auto pair = map.insert_or_assign(3, 3);
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(false, pair.second);
  ASSERT_EQ(3, pair.first->second);
}

TEST(MapInsertTest, InsertPairNonEmptyExisting) {
  OriginalMapInts orig = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  MapInts map = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  auto pair = map.insert({3, 3});
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(false, pair.second);
  ASSERT_EQ(5, pair.first->second);
}

TEST(MapInsertTest, InsertPairEmpty) {
  MapInts map;
  auto pair = map.insert({1, 1});
  ASSERT_EQ(1, map.size());
  ASSERT_EQ(1, map.begin()->second);
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(map.begin(), pair.first);
}

/* РАСКОММЕНТИРОВАТЬ ПОСЛЕ ПОДСТАНОВКИ s21::map в MapInts */

TEST(MapInsertTest, InsertNonEmptyExisting) {
  OriginalMapInts orig = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  MapInts map = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  auto pair = map.insert(3, 3);
  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(false, pair.second);
  ASSERT_EQ(5, pair.first->second);
}

TEST(MapInsertTest, InsertEmpty) {
  MapInts map;
  auto pair = map.insert(1, 1);
  ASSERT_EQ(1, map.size());
  ASSERT_EQ(1, map.begin()->second);
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(map.begin(), pair.first);
}

TEST(MapGeneralTest, ClearNonEmpty) {
  MapInts map = {{1, 3}, {2, 2}, {3, 5}, {4, 4}};
  ASSERT_NO_THROW(map.clear());
  ASSERT_EQ(0, map.size());
  ASSERT_EQ(map.begin(), map.end());
}

TEST(MapGeneralTest, ClearEmpty) {
  MapInts map;
  ASSERT_NO_THROW(map.clear());
  ASSERT_EQ(0, map.size());
  ASSERT_EQ(map.begin(), map.end());
}

TEST(MapMergeTest, Overlapping) {
  MapInts first = {{1, 1}, {8, 8}, {9, 9}, {11, 11}};
  MapInts second = {{2, 2}, {3, 3}, {8, 8}, {12, 12}};

  OriginalMapInts first_expected = {{1, 1}, {9, 9}, {11, 11}, {2, 2},
                                    {3, 3}, {8, 8}, {12, 12}};
  OriginalMapInts second_expected = {{8, 8}};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkMapsEqual(first, first_expected));
  ASSERT_TRUE(checkMapsEqual(second, second_expected));
}

TEST(MapMergeTest, NotOverlapping) {
  MapInts first = {{1, 1}, {8, 8}, {9, 9}, {11, 11}};
  MapInts second = {{2, 2}, {3, 3}, {12, 12}};

  OriginalMapInts first_expected = {{1, 1}, {9, 9}, {11, 11}, {2, 2},
                                    {3, 3}, {8, 8}, {12, 12}};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkMapsEqual(first, first_expected));
  ASSERT_TRUE(second.empty());
  ASSERT_EQ(second.begin(), second.end());
}

TEST(MapMergeTest, IteratorOnNotOverlapping) {
  MapInts first = {{1, 1}, {8, 8}, {9, 9}, {11, 11}};
  MapInts second = {{2, 2}, {3, 3}, {12, 12}};

  auto first_iterator = first.begin();
  auto second_iterator = second.begin();

  ASSERT_NO_THROW(first.merge(second));

  ASSERT_EQ(++first_iterator, second_iterator);
  ASSERT_EQ(1, (--second_iterator)->first);
  ASSERT_EQ(2, first_iterator->first);
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(MapMergeTest, IteratorOnOverlapping) {
  MapInts first = {{1, 1}, {8, 8}, {9, 9}, {11, 11}};
  MapInts second = {{2, 2}, {3, 3}, {8, 8}, {12, 12}};

  auto first_iterator = ++first.begin();
  auto second_iterator = --(--second.end());

  ASSERT_NO_THROW(first.merge(second));

  ASSERT_EQ(second.begin(), second_iterator);
  ASSERT_EQ(++second_iterator, second.end());
  ASSERT_EQ(9, (++first_iterator)->first);
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

/* РАСКОММЕНТИРОВАТЬ ПОСЛЕ ПОДСТАНОВКИ s21::map в MapInts */

TEST(MapLookupTest, NonEmpty) {
  MapStringInt first = {{"a", 1}, {"b", 2}};
  MapInts second = {{1, 1}};

  ASSERT_TRUE(first.contains("a"));
  ASSERT_TRUE(first.contains("b"));
  ASSERT_FALSE(first.contains("c"));
  ASSERT_TRUE(second.contains(1));
  ASSERT_FALSE(second.contains(2));
}

TEST(MapLookupTest, Empty) {
  MapStringInt first;
  MapInts second;

  ASSERT_FALSE(first.contains("c"));
  ASSERT_FALSE(second.contains(2));
}

TEST(MapGeneralTest, InsertManySimpleTest) {
  MapInts map = {{1, 0}, {4, 0}};
  OriginalMapInts orig = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};

  std::pair<int, int> pair1 = {2, 0};
  std::pair<int, int> pair2 = {3, 0};
  std::pair<int, int> pair3 = {3, 0};
  std::pair<int, int> pair4 = {2, 0};

  map.insert_many(pair1, pair2, pair3, pair4);

  ASSERT_TRUE(checkMapsEqual(map, orig));
}

TEST(MapGeneralTest, InsertManyIteratorCheck) {
  MapInts map = {{1, 0}, {4, 0}};
  OriginalMapInts orig = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
  auto iterator = map.begin();

  std::pair<int, int> pair1 = {2, 0};
  std::pair<int, int> pair2 = {3, 0};
  std::pair<int, int> pair3 = {3, 0};
  std::pair<int, int> pair4 = {2, 0};

  map.insert_many(pair1, pair2, pair3, pair4);

  iterator++;

  ASSERT_TRUE(checkMapsEqual(map, orig));
  ASSERT_EQ(2, iterator->first);
  ASSERT_NO_THROW(IterateThrough(map));
}

TEST(MapGeneralTest, InsertManyReturnCheck) {
  MapInts map = {{1, 0}, {4, 0}};
  auto iterator = map.begin();

  std::pair<int, int> pair1 = {2, 0};
  std::pair<int, int> pair2 = {3, 0};
  std::pair<int, int> pair3 = {3, 0};
  std::pair<int, int> pair4 = {2, 0};

  auto arr = map.insert_many(pair1, pair2, pair3, pair4);

  ASSERT_EQ(++iterator, arr[0].first);
  ASSERT_EQ(true, arr[0].second);
  ASSERT_EQ(++iterator, arr[1].first);
  ASSERT_EQ(true, arr[0].second);
  ASSERT_EQ(iterator, arr[2].first);
  ASSERT_EQ(false, arr[2].second);
  ASSERT_EQ(--iterator, arr[3].first);
  ASSERT_EQ(false, arr[3].second);
}

TEST(MapIteratorTest, ConstAndNormalIterator) {
  MapInts map = {{1, 1}};
  s21::map<int, int>::const_iterator i = map.begin();
  s21::map<int, int>::iterator ci = map.begin();
  ASSERT_EQ(i, ci);
}

TEST(MapIteratorTest, ConstIterator) {
  const MapInts map = {{1, 0}, {2, 0}};
  auto iterator = map.begin();
  ASSERT_EQ(1, iterator->first);
  iterator++;
  ASSERT_EQ(2, iterator->first);
  iterator++;
  ASSERT_EQ(map.end(), iterator);
}

TEST(MapEraseBalanceTest, EraseByIteratorRandom) {
  MapInts set;
  const int N = 10000;
  std::vector<int> values(N);
  std::iota(values.begin(), values.end(), 0);

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(values.begin(), values.end(), g);

  for (int v : values) {
    set.insert({v, 0});
  }

  for (int v : values) {
    auto it = set.find(v);
    if (it != set.end()) {
      set.erase(it);
    }
  }

  ASSERT_EQ(set.size(), 0);
  ASSERT_EQ(set.begin(), set.end());
}