#include <gtest/gtest.h>

#include <set>
#include <utility>

#include "../s21_set.h"

// заменить на s21::set
using SetInts = s21::set<int>;
using SetStrings = s21::set<std::string>;

// не менять на s21::set
using OriginalSetInts = std::set<int>;

bool checkSetsEqual(SetInts our_set, OriginalSetInts orig_set) {
  auto iterator_our = our_set.begin();
  auto iterator_orig = orig_set.begin();

  while (iterator_our != our_set.end()) {
    if (*iterator_orig != *iterator_our) return false;
    iterator_orig++;
    iterator_our++;
  }

  if (iterator_orig != orig_set.end()) return false;

  return true;
}

bool checkForwardIteratrion(SetInts set) {
  int key = *set.begin();
  for (auto item : set) {
    if (item < key) return false;
    key = item;
  }
  return true;
}

void IterateThrough(SetInts set) {
  auto start = std::chrono::steady_clock::now();
  for (auto item : set) {
    if (item == 0) {
    }
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
      throw std::runtime_error("Timeout exceeded");
    }
  }
}

TEST(SetIteratorTest, EmptySet) {
  SetInts set;
  ASSERT_EQ(set.begin(), set.end());
}

TEST(SetIteratorTest, OneElement) {
  SetInts set = {1};
  ASSERT_EQ(set.begin(), --set.end());
}

TEST(SetIteratorTest, SwapTwoNonEmpty) {
  SetInts first = {1, 2};
  SetInts second = {10, 20};

  auto iterator = first.begin();
  first.swap(second);
  iterator++;

  ASSERT_EQ(2, *iterator);

  ASSERT_EQ(10, *first.begin());
  ASSERT_EQ(20, *(--first.end()));

  ASSERT_EQ(1, *second.begin());
  ASSERT_EQ(2, *(--second.end()));

  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(SetIteratorTest, OneEmptySetCheckNonEmpty) {
  SetInts first = {1};
  SetInts second;

  auto iterator = first.begin();
  first.swap(second);
  second.insert(2);

  ASSERT_EQ(*iterator, 1);
  ASSERT_EQ(*iterator, 1);

  iterator++;
  ASSERT_EQ(*iterator, 2);
  ASSERT_EQ(*iterator, 2);

  iterator++;
  ASSERT_EQ(iterator, second.end());

  ASSERT_EQ(first.begin(), first.end());
}

TEST(SetIteratorTest, OneEmptySetCheckFirstAndLoops) {
  SetInts first = {1};
  SetInts second;

  first.swap(second);
  second.insert(2);

  ASSERT_EQ(first.begin(), first.end());
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(SetIteratorTest, ForwardIteration) {
  SetInts set = {1, 100, 3, 22, 9, -5};
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(342);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(-10);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(21);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(20);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(-3);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(447);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.insert(0);
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(++(++(++set.begin())));
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(set.begin());
  ASSERT_TRUE(checkForwardIteratrion(set));
  set.erase(--set.end());
  ASSERT_TRUE(checkForwardIteratrion(set));
}

TEST(SetCapacityTest, OneEmptySize) {
  SetInts first = {1};
  SetInts second;

  first.swap(second);
  second.insert(2);

  ASSERT_EQ(2, second.size());
  ASSERT_EQ(0, first.size());
}

TEST(SetCapacityTest, OneEmptyIsEmpty) {
  SetInts first = {{1, 1}};
  SetInts second;

  first.swap(second);
  second.insert({2, 2});

  ASSERT_FALSE(second.empty());
  ASSERT_TRUE(first.empty());
}

TEST(SetGeneralTest, InsertEraseSwapIterate) {
  SetInts first = {1, 4, 2, 88};
  SetInts second = {1, 100, 11, 66, 3, 44};

  auto iterator = ++first.begin();
  first.swap(second);
  second.erase(iterator);
  auto second_iterator = --second.end();
  first.swap(second);
  first.erase(second_iterator);

  OriginalSetInts first_expected = {1, 4};
  OriginalSetInts second_expected = {1, 3, 11, 44, 66, 100};

  ASSERT_TRUE(checkForwardIteratrion(second));
  ASSERT_TRUE(checkSetsEqual(first, first_expected));
  ASSERT_TRUE(checkSetsEqual(second, second_expected));
}

TEST(SetGeneralTest, ExistingInsertTest) {
  SetInts set = {1};
  ASSERT_NO_THROW(set.insert(1));
  ASSERT_EQ(1, set.size());
  ASSERT_EQ(1, *set.begin());
}

TEST(SetConstructorsTest, CopyConstructor) {
  OriginalSetInts orig = {8, 1, 9};
  SetInts set = {8, 1, 9};
  SetInts copy(set);
  ASSERT_TRUE(checkSetsEqual(set, orig));
  ASSERT_TRUE(checkSetsEqual(copy, orig));
  ASSERT_EQ(3, set.size());
  ASSERT_EQ(3, copy.size());
}

TEST(SetConstructorsTest, MoveConstructor) {
  OriginalSetInts orig = {8, 1, 9};
  SetInts set = {8, 1, 9};
  SetInts copy = std::move(set);
  ASSERT_TRUE(checkSetsEqual(copy, orig));
  ASSERT_EQ(set.begin(), set.end());
  ASSERT_EQ(0, set.size());
  ASSERT_EQ(3, copy.size());
}

TEST(SetInsertTest, InsertNonEmptyExisting) {
  OriginalSetInts orig = {1, 2, 3, 4};
  SetInts set = {1, 2, 3, 4};
  auto iterator = --(--set.end());
  auto pair = set.insert(3);
  ASSERT_TRUE(checkSetsEqual(set, orig));
  ASSERT_EQ(iterator, pair.first);
  ASSERT_EQ(false, pair.second);
}

TEST(SetInsertTest, InsertEmpty) {
  SetInts set;
  auto pair = set.insert(1);
  ASSERT_EQ(1, set.size());
  ASSERT_EQ(1, *set.begin());
  ASSERT_EQ(true, pair.second);
  ASSERT_EQ(set.begin(), pair.first);
}

TEST(SetGeneralTest, ClearNonEmpty) {
  SetInts set = {1, 2, 3, 4};
  ASSERT_NO_THROW(set.clear());
  ASSERT_EQ(0, set.size());
  ASSERT_EQ(set.begin(), set.end());
}

TEST(SetGeneralTest, ClearEmpty) {
  SetInts set;
  ASSERT_NO_THROW(set.clear());
  ASSERT_EQ(0, set.size());
  ASSERT_EQ(set.begin(), set.end());
}

TEST(SetMergeTest, Overlapping) {
  SetInts first = {1, 8, 9, 11};
  SetInts second = {2, 3, 8, 12};

  OriginalSetInts first_expected = {1, 2, 3, 8, 9, 11, 12};
  OriginalSetInts second_expected = {8};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkSetsEqual(first, first_expected));
  ASSERT_TRUE(checkSetsEqual(second, second_expected));
}

TEST(SetMergeTest, NotOverlapping) {
  SetInts first = {1, 8, 9, 11};
  SetInts second = {2, 3, 12};

  OriginalSetInts first_expected = {1, 2, 3, 8, 9, 11, 12};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkSetsEqual(first, first_expected));
  ASSERT_TRUE(second.empty());
  ASSERT_EQ(second.begin(), second.end());
}

TEST(SetMergeTest, IteratorOnNotOverlapping) {
  SetInts first = {1, 8, 9, 11};
  SetInts second = {2, 3, 12};

  auto first_iterator = first.begin();
  auto second_iterator = second.begin();

  ASSERT_NO_THROW(first.merge(second));

  ASSERT_EQ(++first_iterator, second_iterator);
  ASSERT_EQ(1, *(--second_iterator));
  ASSERT_EQ(2, *first_iterator);
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(SetMergeTest, IteratorOnOverlapping) {
  SetInts first = {1, 8, 9, 11};
  SetInts second = {2, 3, 8, 12};

  auto first_iterator = ++first.begin();
  auto second_iterator = --(--second.end());

  ASSERT_NO_THROW(first.merge(second));

  ASSERT_EQ(second.begin(), second_iterator);
  ASSERT_EQ(++second_iterator, second.end());
  ASSERT_EQ(9, *(++first_iterator));
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

// /* РАСКОММЕНТИРОВАТЬ ПОСЛЕ ПОДСТАНОВКИ s21::set в SetInts */

TEST(SetLookupTest, NonEmpty) {
  SetStrings first = {"a", "b"};
  SetInts second = {1};

  ASSERT_TRUE(first.contains("a"));
  ASSERT_TRUE(first.contains("b"));
  ASSERT_FALSE(first.contains("c"));
  ASSERT_TRUE(second.contains(1));
  ASSERT_FALSE(second.contains(2));
}

TEST(SetLookupTest, Empty) {
  SetStrings first;
  SetInts second;

  ASSERT_FALSE(first.contains("c"));
  ASSERT_FALSE(second.contains(2));
}

TEST(SetGeneralTest, InsertManySimpleTest) {
  SetInts set = {1, 4};
  OriginalSetInts orig = {1, 2, 3, 4};
  set.insert_many(2, 3, 3, 2);

  ASSERT_TRUE(checkSetsEqual(set, orig));
}

TEST(SetGeneralTest, InsertManyIteratorCheck) {
  SetInts set = {1, 4};
  OriginalSetInts orig = {1, 2, 3, 4};
  auto iterator = set.begin();

  set.insert_many(2, 3, 3, 2);
  iterator++;

  ASSERT_TRUE(checkSetsEqual(set, orig));
  ASSERT_EQ(2, *iterator);
  ASSERT_NO_THROW(IterateThrough(set));
}

TEST(SetGeneralTest, InsertManyReturnCheck) {
  SetInts set = {1, 4};
  auto iterator = set.begin();

  auto arr = set.insert_many(2, 3, 3, 2);

  ASSERT_EQ(++iterator, arr[0].first);
  ASSERT_EQ(true, arr[0].second);
  ASSERT_EQ(++iterator, arr[1].first);
  ASSERT_EQ(true, arr[0].second);
  ASSERT_EQ(iterator, arr[2].first);
  ASSERT_EQ(false, arr[2].second);
  ASSERT_EQ(--iterator, arr[3].first);
  ASSERT_EQ(false, arr[3].second);
}

TEST(SetIteratorTest, ConstAndNormalIterator) {
  SetInts set = {1};
  s21::set<int>::const_iterator i = set.begin();
  s21::set<int>::iterator ci = set.begin();
  ASSERT_EQ(i, ci);
}

TEST(SetIteratorTest, ConstIterator) {
  const SetInts set = {1, 2};
  auto iterator = set.begin();
  ASSERT_EQ(1, *iterator);
  iterator++;
  ASSERT_EQ(2, *iterator);
  iterator++;
  ASSERT_EQ(set.end(), iterator);
}

// TEST(StdSetTest, SwapMassiveSets) {
//   std::set<int> set1;
//   std::set<int> set2;

//   const int SIZE = 2'000'000;

//   for (int i = 1; i <= SIZE; ++i) {
//     set1.insert(i);
//   }
//   for (int i = SIZE + 1; i <= 2 * SIZE; ++i) {
//     set2.insert(i);
//   }
//   // Выводим время
//   std::cout << "std::set swap time: "
//             << "\n";
//   auto start = std::chrono::high_resolution_clock::now();

//   set1.swap(set2);

//   auto end = std::chrono::high_resolution_clock::now();

//   // Выводим время
//   std::cout << "std::set swap time: "
//             << std::chrono::duration_cast<std::chrono::milliseconds>(end -
//                                                                      start)
//                    .count()
//             << " ms\n";

//   for (int i = SIZE + 1; i <= 2 * SIZE; i += SIZE / 100) {
//     EXPECT_NE(set1.find(i), set1.end());  // Аналог contains()
//   }

//   for (int i = 1; i <= SIZE; i += SIZE / 100) {
//     EXPECT_NE(set2.find(i), set2.end());
//   }

//   EXPECT_EQ(set1.find(1), set1.end());
//   EXPECT_EQ(set2.find(SIZE + 1), set2.end());
// }
