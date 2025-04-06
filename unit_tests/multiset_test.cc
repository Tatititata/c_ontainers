#include <gtest/gtest.h>

#include <set>
#include <utility>

#include "../s21_multiset.h"

// заменить на s21::multiset
using MultisetInts = s21::multiset<int>;
using MultisetStrings = s21::multiset<std::string>;

// не менять на s21::multiset
using OriginalMultisetInts = std::multiset<int>;

bool checkMultisetsEqual(MultisetInts our_multiset,
                         OriginalMultisetInts orig_multiset) {
  auto iterator_our = our_multiset.begin();
  auto iterator_orig = orig_multiset.begin();

  while (iterator_our != our_multiset.end()) {
    if (*iterator_orig != *iterator_our) return false;
    iterator_orig++;
    iterator_our++;
  }

  if (iterator_orig != orig_multiset.end()) return false;

  return true;
}

bool checkForwardIteratrion(MultisetInts multiset) {
  int key = *multiset.begin();
  for (auto item : multiset) {
    if (item < key) return false;
    key = item;
  }
  return true;
}

void IterateThrough(MultisetInts multiset) {
  auto start = std::chrono::steady_clock::now();
  for (auto item : multiset) {
    if (item == 0) {
    }
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
      throw std::runtime_error("Timeout exceeded");
    }
  }
}

TEST(MultisetIteratorTest, EmptyMultiset) {
  MultisetInts multiset;
  ASSERT_EQ(multiset.begin(), multiset.end());
}

TEST(MultisetIteratorTest, OneElement) {
  MultisetInts multiset = {1};
  ASSERT_EQ(multiset.begin(), --multiset.end());
}

TEST(MultisetIteratorTest, SwapTwoNonEmpty) {
  MultisetInts first = {1, 2};
  MultisetInts second = {10, 20};

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

TEST(MultisetIteratorTest, OneEmptyMultisetCheckNonEmpty) {
  MultisetInts first = {1};
  MultisetInts second;

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

TEST(MultisetIteratorTest, OneEmptyMultisetCheckFirstAndLoops) {
  MultisetInts first = {1};
  MultisetInts second;

  first.swap(second);
  second.insert(2);

  ASSERT_EQ(first.begin(), first.end());
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

TEST(MultisetIteratorTest, ForwardIteration) {
  MultisetInts multiset = {1, 100, 3, 22, 9, -5};
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(342);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(-10);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(21);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(20);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(-3);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(447);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.insert(0);
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(++(++(++multiset.begin())));
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(multiset.begin());
  ASSERT_TRUE(checkForwardIteratrion(multiset));
  multiset.erase(--multiset.end());
  ASSERT_TRUE(checkForwardIteratrion(multiset));
}

TEST(MultisetCapacityTest, OneEmptySize) {
  MultisetInts first = {1};
  MultisetInts second;

  first.swap(second);
  second.insert(2);

  ASSERT_EQ(2, second.size());
  ASSERT_EQ(0, first.size());
}

TEST(MultisetCapacityTest, OneEmptyIsEmpty) {
  MultisetInts first = {{1, 1}};
  MultisetInts second;

  first.swap(second);
  second.insert({2, 2});

  ASSERT_FALSE(second.empty());
  ASSERT_TRUE(first.empty());
}

TEST(MultisetGeneralTest, InsertEraseSwapIterate) {
  MultisetInts first = {1, 4, 2, 88};
  MultisetInts second = {1, 100, 11, 66, 3, 44};

  auto iterator = ++first.begin();
  first.swap(second);
  second.erase(iterator);
  auto second_iterator = --second.end();
  first.swap(second);
  first.erase(second_iterator);

  OriginalMultisetInts first_expected = {1, 4};
  OriginalMultisetInts second_expected = {1, 3, 11, 44, 66, 100};

  ASSERT_TRUE(checkForwardIteratrion(second));
  ASSERT_TRUE(checkMultisetsEqual(first, first_expected));
  ASSERT_TRUE(checkMultisetsEqual(second, second_expected));
}

TEST(MultisetGeneralTest, ExistingInsertTest) {
  MultisetInts multiset = {1};
  ASSERT_NO_THROW(multiset.insert(1));
  ASSERT_EQ(2, multiset.size());
  ASSERT_EQ(1, *multiset.begin());
}

TEST(MultisetConstructorsTest, CopyConstructor) {
  OriginalMultisetInts orig = {8, 1, 9};
  MultisetInts multiset = {8, 1, 9};
  MultisetInts copy(multiset);
  ASSERT_TRUE(checkMultisetsEqual(multiset, orig));
  ASSERT_TRUE(checkMultisetsEqual(copy, orig));
  ASSERT_EQ(3, multiset.size());
  ASSERT_EQ(3, copy.size());
}

TEST(MultisetConstructorsTest, MoveConstructor) {
  OriginalMultisetInts orig = {8, 1, 9};
  MultisetInts multiset = {8, 1, 9};
  MultisetInts copy = std::move(multiset);
  ASSERT_TRUE(checkMultisetsEqual(copy, orig));
  ASSERT_EQ(multiset.begin(), multiset.end());
  ASSERT_EQ(0, multiset.size());
  ASSERT_EQ(3, copy.size());
}

TEST(MultisetInsertTest, InsertNonEmptyExisting) {
  OriginalMultisetInts orig = {1, 2, 3, 3, 4};
  MultisetInts multiset = {1, 2, 3, 4};
  auto ret = multiset.insert(3);
  ASSERT_TRUE(checkMultisetsEqual(multiset, orig));
  ASSERT_EQ(3, *ret);
}

TEST(MultisetInsertTest, InsertEmpty) {
  MultisetInts multiset;
  auto ret = multiset.insert(1);
  ASSERT_EQ(1, multiset.size());
  ASSERT_EQ(1, *multiset.begin());
  ASSERT_EQ(multiset.begin(), ret);
}

TEST(MultisetGeneralTest, ClearNonEmpty) {
  MultisetInts multiset = {1, 2, 3, 4};
  ASSERT_NO_THROW(multiset.clear());
  ASSERT_EQ(0, multiset.size());
  ASSERT_EQ(multiset.begin(), multiset.end());
}

TEST(MultisetGeneralTest, ClearEmpty) {
  MultisetInts multiset;
  ASSERT_NO_THROW(multiset.clear());
  ASSERT_EQ(0, multiset.size());
  ASSERT_EQ(multiset.begin(), multiset.end());
}

TEST(MultisetMergeTest, Overlapping) {
  MultisetInts first = {1, 8, 9, 11};
  MultisetInts second = {2, 3, 8, 12};

  OriginalMultisetInts first_expected = {1, 2, 3, 8, 8, 9, 11, 12};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkMultisetsEqual(first, first_expected));
  ASSERT_TRUE(second.empty());
  ASSERT_EQ(second.begin(), second.end());
}

TEST(MultisetMergeTest, NotOverlapping) {
  MultisetInts first = {1, 8, 9, 11};
  MultisetInts second = {2, 3, 12};

  OriginalMultisetInts first_expected = {1, 2, 3, 8, 9, 11, 12};

  ASSERT_NO_THROW(first.merge(second));
  ASSERT_TRUE(checkMultisetsEqual(first, first_expected));
  ASSERT_TRUE(second.empty());
  ASSERT_EQ(second.begin(), second.end());
}

TEST(MultisetMergeTest, IteratorOnNotOverlapping) {
  MultisetInts first = {1, 8, 9, 11};
  MultisetInts second = {2, 3, 12};

  auto first_iterator = first.begin();
  auto second_iterator = second.begin();

  ASSERT_NO_THROW(first.merge(second));

  ASSERT_EQ(++first_iterator, second_iterator);
  ASSERT_EQ(1, *(--second_iterator));
  ASSERT_EQ(2, *first_iterator);
  ASSERT_NO_THROW(IterateThrough(first));
  ASSERT_NO_THROW(IterateThrough(second));
}

// /* РАСКОММЕНТИРОВАТЬ ПОСЛЕ ПОДСТАНОВКИ s21::multiset в MultisetInts */

TEST(MultisetLookupTest, NonEmpty) {
  MultisetStrings first = {"a", "b"};
  MultisetInts second = {1};

  ASSERT_TRUE(first.contains("a"));
  ASSERT_TRUE(first.contains("b"));
  ASSERT_FALSE(first.contains("c"));
  ASSERT_TRUE(second.contains(1));
  ASSERT_FALSE(second.contains(2));
}

TEST(MultisetLookupTest, Empty) {
  MultisetStrings first;
  MultisetInts second;

  ASSERT_FALSE(first.contains("c"));
  ASSERT_FALSE(second.contains(2));
}

TEST(SetIteratorTest, ConstAndNormalIterator1) {
  MultisetInts set = {1};
  s21::multiset<int>::const_iterator i = set.begin();
  s21::multiset<int>::iterator ci = set.begin();
  ASSERT_EQ(i, ci);
}

TEST(MultisetLookupTest, CountNonEmpty) {
  MultisetStrings first = {"a", "b", "a", "a", "00fsoi3", "a"};
  MultisetInts second = {1, 343, 1, 3};

  ASSERT_EQ(4, first.count("a"));
  ASSERT_EQ(2, second.count(1));
}

TEST(MultisetLookupTest, CountEmpty) {
  MultisetStrings first;
  MultisetInts second;

  ASSERT_EQ(0, first.count("a"));
  ASSERT_EQ(0, second.count(1));
}

TEST(MultisetLookupTest, FindNonEmpty) {
  MultisetStrings first = {"a", "b", "a", "a", "00fsoi3", "d"};
  MultisetInts second = {1, 343, 1, 3};
  MultisetInts third = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2};

  ASSERT_EQ(++first.begin(), first.find("a"));
  ASSERT_EQ(second.begin(), second.find(1));
  ASSERT_EQ(first.end(), first.find("aaaaaa"));
  ASSERT_EQ(second.end(), second.find(11111));

  ASSERT_EQ(third.begin(), third.find(0));
  ASSERT_EQ(++(++(++(++third.begin()))), third.find(1));
}

TEST(MultisetLookupTest, FindEmpty) {
  MultisetStrings first;
  MultisetInts second;

  ASSERT_EQ(first.end(), first.find("aaaaaa"));
  ASSERT_EQ(second.end(), second.find(11111));
}

TEST(MultisetLookupTest, EqualRangeNonEmptyFound) {
  MultisetStrings first = {"a", "b", "a", "a", "00fsoi3", "d"};
  MultisetInts second = {1, 343, 1, 3};

  auto first_ret = first.equal_range("a");
  auto second_ret = second.equal_range(1);

  ASSERT_EQ(first_ret.first, ++first.begin());
  ASSERT_EQ(first_ret.second, --(--first.end()));
  ASSERT_EQ(second_ret.first, second.begin());
  ASSERT_EQ(second_ret.second, --(--second.end()));
}

TEST(MultisetLookupTest, EqualRangeNonEmptyNotFound) {
  MultisetStrings first = {"a", "b"};
  MultisetInts second = {1, 3, 4};

  auto first_ret = first.equal_range("aaaa");
  auto second_ret = second.equal_range(2);

  ASSERT_EQ(first_ret.first, --first.end());
  ASSERT_EQ(first_ret.second, --first.end());

  ASSERT_EQ(second_ret.first, ++second.begin());
  ASSERT_EQ(second_ret.second, ++second.begin());
}

TEST(MultisetLookupTest, LowerBoundNonEmpty) {
  MultisetStrings first = {"a", "b"};
  MultisetInts second = {1, 3, 4};

  ASSERT_EQ(first.end(), first.lower_bound("c"));
  ASSERT_EQ(second.begin(), second.lower_bound(0));
  ASSERT_EQ(second.begin(), second.lower_bound(1));
  ASSERT_EQ(++second.begin(), second.lower_bound(2));
  ASSERT_EQ(++second.begin(), second.lower_bound(3));
  ASSERT_EQ(++(++second.begin()), second.lower_bound(4));
  ASSERT_EQ(second.end(), second.lower_bound(5));
}

TEST(MultisetLookupTest, LowerBoundEmpty) {
  MultisetInts first;
  ASSERT_EQ(first.end(), first.lower_bound(10));
}

TEST(MultisetLookupTest, UpperBoundNonEmpty) {
  MultisetStrings first = {"a", "b"};
  MultisetInts second = {1, 3, 4};

  ASSERT_EQ(first.end(), first.upper_bound("c"));
  ASSERT_EQ(first.end(), first.upper_bound("b"));
  ASSERT_EQ(--first.end(), first.upper_bound("a"));
  ASSERT_EQ(first.begin(), first.upper_bound("0"));

  ASSERT_EQ(second.end(), second.upper_bound(5));
  ASSERT_EQ(second.end(), second.upper_bound(4));
  ASSERT_EQ(--second.end(), second.upper_bound(3));
  ASSERT_EQ(--(--second.end()), second.upper_bound(2));
  ASSERT_EQ(++second.begin(), second.upper_bound(1));
  ASSERT_EQ(second.begin(), second.upper_bound(0));
}

TEST(MultisetLookupTest, UpperBoundEmpty) {
  MultisetInts first;
  ASSERT_EQ(first.end(), first.lower_bound(10));
}
