#include <gtest/gtest.h>

#include <set>
#include <utility>

#include "../lace_multiset.h"

// заменить на lace::multiset
using MultisetInts = lace::multiset<int>;
using MultisetStrings = lace::multiset<std::string>;

// не менять на lace::multiset
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

// /* РАСКОММЕНТИРОВАТЬ ПОСЛЕ ПОДСТАНОВКИ lace::multiset в MultisetInts */

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

TEST(MultiSetIteratorTest, ConstAndNormalIterator) {
  MultisetInts set = {1};
  lace::multiset<int>::const_iterator i = set.begin();
  lace::multiset<int>::iterator ci = set.begin();
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

TEST(MultisetAssignmentTest, CopyAssignment) {
  lace::multiset<int> first = {1, 2, 3, 4, 5, 5, 6};
  lace::multiset<int> second;
  second = first;
  ASSERT_EQ(first.size(), second.size());
  ASSERT_TRUE(std::equal(first.begin(), first.end(), second.begin()));
}

TEST(MultisetAssignmentTest, SelfAssignmentCopy) {
  lace::multiset<int> first = {7, 8, 9};
  first = first;
  ASSERT_EQ(first.size(), 3);
  ASSERT_TRUE(first.contains(7));
  ASSERT_TRUE(first.contains(8));
  ASSERT_TRUE(first.contains(9));
}

TEST(MultisetAssignmentTest, ExceptionSafety) {
  MultisetInts source = {1, 2, 3};
  MultisetInts target;
  EXPECT_NO_THROW(target = source);
}

TEST(MultisetAssignmentTest, MoveAssignment) {
  lace::multiset<int> first = {10, 20, 30, 40};
  lace::multiset<int> second = {1, 2, 3};

  second = std::move(first);

  ASSERT_TRUE(first.empty());
  ASSERT_EQ(second.size(), 4);
  ASSERT_TRUE(second.contains(10));
  ASSERT_TRUE(second.contains(20));
  ASSERT_TRUE(second.contains(30));
  ASSERT_TRUE(second.contains(40));
}

TEST(MultisetAssignmentTest, MoveAssignment2) {
  lace::multiset<int> first = {10, 20, 30, 40};
  lace::multiset<int> second;

  second = std::move(first);

  ASSERT_TRUE(first.empty());
  ASSERT_EQ(second.size(), 4);
  ASSERT_TRUE(second.contains(10));
  ASSERT_TRUE(second.contains(20));
}

struct ThrowOnCopy {
  int id;  // Уникальный идентификатор для сравнения

  ThrowOnCopy(int id = 0) : id(id) {}
  ThrowOnCopy(const ThrowOnCopy& other) : id(other.id) {
    throw std::runtime_error("Copy failed");
  }
  ThrowOnCopy(ThrowOnCopy&&) = default;

  // Добавляем operator<
  bool operator<(const ThrowOnCopy& other) const { return id < other.id; }
  bool operator==(const ThrowOnCopy& other) const { return id == other.id; }
  bool operator>(const ThrowOnCopy& other) const { return id > other.id; }
  bool operator!=(const ThrowOnCopy& other) const { return id != other.id; }
};

TEST(MultisetTest, InsertThrowsOnAllocationFailure) {
  lace::multiset<ThrowOnCopy> s;
  ThrowOnCopy value(42);  // Указываем id для сравнения

  EXPECT_THROW(s.insert(value), std::runtime_error);
  EXPECT_TRUE(s.empty());
}

struct ThrowOnMove {
  int id;

  ThrowOnMove(int id = 0) : id(id) {}
  ThrowOnMove(const ThrowOnMove&) = default;
  ThrowOnMove(ThrowOnMove&& other) : id(other.id) {
    throw std::runtime_error("Move failed");
  }

  bool operator<(const ThrowOnMove& other) const { return id < other.id; }
  bool operator==(const ThrowOnMove& other) const { return id == other.id; }
  bool operator>(const ThrowOnMove& other) const { return id > other.id; }
  bool operator!=(const ThrowOnMove& other) const { return id != other.id; }
};

TEST(MultisetTest, MoveInsertThrows) {
  lace::multiset<ThrowOnMove> s;
  ThrowOnMove value(42);

  EXPECT_THROW(s.insert(std::move(value)), std::runtime_error);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(value.id, 42);
}

TEST(MultisetTest, InsertMany) {
  lace::multiset<int> s;
  s.insert_many(1, 2, 3);
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
}

TEST(MultisetTest, EqualRange_KeyNotFound) {
  lace::multiset<int> ms = {10, 20, 30};

  auto [first1, last1] = ms.equal_range(5);
  EXPECT_EQ(first1, ms.begin());
  EXPECT_EQ(last1, ms.begin());

  auto [first2, last2] = ms.equal_range(25);
  EXPECT_EQ(*first2, 30);
  EXPECT_EQ(first2, last2);

  auto [first3, last3] = ms.equal_range(35);
  EXPECT_EQ(first3, ms.end());
  EXPECT_EQ(last3, ms.end());
}

TEST(MultisetTest, EqualRange_SingleMatch) {
  lace::multiset<int> ms = {10, 20, 30};

  auto [first, last] = ms.equal_range(20);
  EXPECT_EQ(first, ms.find(20));
  EXPECT_EQ(last, ms.find(30));
}

TEST(MultisetTest, EqualRange_MultipleMatches) {
  lace::multiset<int> ms = {10, 20, 20, 20, 30};

  auto [first, last] = ms.equal_range(20);
  EXPECT_EQ(*first, 20);
  EXPECT_EQ(*last, 30);
  EXPECT_EQ(std::distance(first, last), 3);
}

TEST(MultisetTest, EqualRange_AllElementsMatch) {
  lace::multiset<int> ms = {15, 15, 15};

  auto [first, last] = ms.equal_range(15);
  EXPECT_EQ(first, ms.begin());
  EXPECT_EQ(last, ms.end());
}

TEST(MultisetTest, EqualRange_EmptyContainer) {
  lace::multiset<int> ms;

  auto [first, last] = ms.equal_range(10);
  EXPECT_EQ(first, ms.end());
  EXPECT_EQ(last, ms.end());
}

TEST(MultisetTest, EqualRange_FirstElement) {
  lace::multiset<int> ms = {5, 10, 15};
  auto [first, last] = ms.equal_range(5);
  EXPECT_EQ(first, ms.begin());
  EXPECT_EQ(last, std::next(ms.begin()));
}

TEST(MultisetTest, EqualRange_LastElement) {
  lace::multiset<int> ms = {5, 10, 15};
  auto [first, last] = ms.equal_range(15);
  EXPECT_EQ(first, std::prev(ms.end()));
  EXPECT_EQ(last, ms.end());
}

TEST(MultisetTest, ConstMethods) {
  const lace::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.begin();
  EXPECT_EQ(*it, 1);

  auto cit = ms.find(2);
  EXPECT_EQ(*cit, 2);

  auto [first, last] = ms.equal_range(2);
  EXPECT_EQ(std::distance(first, last), 2);
}

TEST(MultisetTest, EqualRangeFullCoverage) {
  lace::multiset<int> ms = {10, 20, 20, 30};

  auto [first1, last1] = ms.equal_range(5);
  EXPECT_EQ(first1, ms.begin());
  EXPECT_EQ(last1, ms.begin());

  auto [first2, last2] = ms.equal_range(25);
  EXPECT_EQ(*first2, 30);
  EXPECT_EQ(first2, last2);

  auto [first3, last3] = ms.equal_range(35);
  EXPECT_EQ(first3, ms.end());
  EXPECT_EQ(last3, ms.end());
}

TEST(MultisetTest, BoundaryCases) {
  lace::multiset<int> empty_ms;
  EXPECT_TRUE(empty_ms.empty());
  EXPECT_EQ(empty_ms.begin(), empty_ms.end());

  EXPECT_GT(empty_ms.max_size(), 0);

  lace::multiset<int> same_ms = {5, 5, 5};
  EXPECT_EQ(same_ms.count(5), 3);
}