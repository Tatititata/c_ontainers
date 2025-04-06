#include <gtest/gtest.h>

#include <cstdlib>
#include <list>
#include <string>

#include "../s21_list.h"
#include "throw_on_number_created.h"

template <typename T>
bool CheckListsEqual(std::list<T>& orig, s21::list<T>& s21) {
  bool is_equal = orig.size() == s21.size();
  auto s21_iterator = s21.begin();
  auto orig_iterator = orig.begin();

  while (s21_iterator != s21.end() && orig_iterator != orig.end() && is_equal) {
    if (*orig_iterator != *s21_iterator) is_equal = false;
    s21_iterator++;
    orig_iterator++;
  }
  return is_equal;
}

void FillListsWithRandomInts(std::list<int>& orig, s21::list<int>& s21,
                             int size) {
  for (int i = 0; i < size; i++) {
    int random = rand();
    orig.push_back(random);
    s21.push_back(random);
  }
}

void FillListsWithRandomStrings(std::list<std::string>& orig,
                                s21::list<std::string>& s21, int size) {
  for (int i = 0; i < size; i++) {
    std::string random = std::to_string(rand());
    orig.push_back(random);
    s21.push_back(random);
  }
}

TEST(ListPushBackTest, RandomIntTest) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_back(random);
    orig_list.push_back(random);
    ASSERT_EQ(CheckListsEqual<int>(orig_list, my_list), true);
  }
}

TEST(ListPushFrontTest, RandomIntTest) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_front(random);
    orig_list.push_front(random);
    ASSERT_EQ(CheckListsEqual<int>(orig_list, my_list), true);
  }
}

TEST(ListPopBackTest, RandomIntTest) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_back(random);
    orig_list.push_back(random);
  }

  for (int j = 0; j < 100; j++) {
    my_list.pop_back();
    orig_list.pop_back();
    ASSERT_EQ(CheckListsEqual<int>(orig_list, my_list), true);
  }
}

TEST(ListPopFrontTest, RandomIntTest) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_back(random);
    orig_list.push_back(random);
  }

  for (int j = 0; j < 100; j++) {
    my_list.pop_front();
    orig_list.pop_front();
    ASSERT_EQ(CheckListsEqual<int>(orig_list, my_list), true);
  }
}

TEST(ListIteratorTest, ConstBegin) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_front(random);
    orig_list.push_front(random);

    s21::list<int>::ListConstIterator<int> my_iterator = my_list.begin();
    std::_List_const_iterator<int> orig_iterator = orig_list.begin();

    ASSERT_EQ(*orig_iterator, *my_iterator);
  }
}

TEST(ListIteratorTest, ConstEnd) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_back(random);
    orig_list.push_back(random);

    s21::list<int>::ListConstIterator<int> my_iterator = --my_list.end();
    std::_List_const_iterator<int> orig_iterator = --orig_list.end();

    ASSERT_EQ(*orig_iterator, *my_iterator);
  }
}

TEST(ListIteratorTest, End) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_back(random);
    orig_list.push_back(random);

    auto my_iterator = my_list.end();
    auto orig_iterator = orig_list.end();
    my_iterator--;
    orig_iterator--;

    ASSERT_EQ(*orig_iterator, *my_iterator);
  }
}

TEST(ListIteratorTest, HappyUB) {
  s21::list<int> my_list;
  std::list<int> orig_list;

  for (int i = 0; i < 100; i++) {
    int random = rand();
    my_list.push_front(random);
    orig_list.push_front(random);

    auto my_iterator = ++my_list.end();
    auto orig_iterator = ++orig_list.end();

    ASSERT_EQ(*orig_iterator, *my_iterator);
  }
}

TEST(ListIteratorTest, EqualityWithInt) {
  s21::list<int> list = {4, 4, 4};
  auto iterator = list.begin();
  iterator++;
  iterator++;
  auto end_iterator = --list.end();
  ASSERT_EQ(iterator, end_iterator);
}

TEST(ListIteratorTest, EqualityWithString) {
  s21::list<std::string> list = {"a", "b"};
  auto iterator = ++list.begin();
  auto end_iterator = --list.end();
  ASSERT_EQ(iterator, end_iterator);
}

TEST(ListConstructorsTest, SizeOnlyConstructorWithInt) {
  s21::list<int> list(10);
  std::list<int> list_original(10);
  ASSERT_EQ(list.size(), list_original.size());

  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListConstructorsTest, SizeOnlyConstructorWithString) {
  s21::list<std::string> list(10);
  std::list<std::string> list_original(10);
  ASSERT_EQ(list.size(), list_original.size());

  CheckListsEqual<std::string>(list_original, list);
}

TEST(ListSort, SortInts) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 1000);
  list_original.sort();
  list.sort();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListSort, SortStrings) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  FillListsWithRandomStrings(list_original, list, 1000);
  list_original.sort();
  list.sort();
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListSort, EmptyList) {
  s21::list<int> list;
  std::list<int> list_original;
  list_original.sort();
  list.sort();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListClearTest, ClearTestWithInts) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 1000);
  list.clear();
  list_original.clear();
  ASSERT_EQ(list.size(), list_original.size());
  ASSERT_EQ(list.begin() == list.end(), true);
}

TEST(ListClearTest, ClearTestWithStrings) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  FillListsWithRandomStrings(list_original, list, 1000);
  list.clear();
  list_original.clear();
  ASSERT_EQ(list.size(), list_original.size());
  ASSERT_EQ(list.begin() == list.end(), true);
}

TEST(ListInsertTest, BeginInsertTestWithInts) {
  s21::list<int> list;
  std::list<int> list_original;
  auto iterator = list.begin();
  auto iterator_original = list_original.begin();
  for (int i = 0; i < 100; i++) {
    int random = rand();
    list.insert(iterator, random);
    list_original.insert(iterator_original, random);
  }
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertTest, EndInsertTestWithInts) {
  s21::list<int> list;
  std::list<int> list_original;
  auto iterator = list.end();
  auto iterator_original = list_original.end();
  for (int i = 0; i < 100; i++) {
    int random = rand();
    list.insert(iterator, random);
    list_original.insert(iterator_original, random);
  }
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertTest, BeginInsertTestWithStrings) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  auto iterator = list.begin();
  auto iterator_original = list_original.begin();
  for (int i = 0; i < 100; i++) {
    std::string random = std::to_string(rand());
    list.insert(iterator, random);
    list_original.insert(iterator_original, random);
  }
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListInsertTest, EndInsertTestWithStrings) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  auto iterator = list.end();
  auto iterator_original = list_original.end();
  for (int i = 0; i < 100; i++) {
    std::string random = std::to_string(rand());
    list.insert(iterator, random);
    list_original.insert(iterator_original, random);
  }
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListEraseTest, RandomIntsTest) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 1000);

  auto iterator = list.begin();
  auto iterator_original = list_original.begin();
  while (iterator != list.end() && iterator_original != list_original.end()) {
    list_original.erase(iterator_original++);
    list.erase(iterator++);
    ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  }
}

TEST(ListEraseTest, RandomStringsTest) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  FillListsWithRandomStrings(list_original, list, 1000);

  auto iterator = list.begin();
  auto iterator_original = list_original.begin();
  while (iterator != list.end() && iterator_original != list_original.end()) {
    list_original.erase(iterator_original++);
    list.erase(iterator++);
    ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
  }
}

TEST(ListSwapTest, TwoIntFilledLists) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);
  FillListsWithRandomInts(list_original_second, list_second, 55);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSwapTest, SecondIntsListIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSwapTest, FirstIntsListIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original_second, list_second, 100);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSwapTest, TwoStringFilledLists) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  s21::list<std::string> list_second;
  std::list<std::string> list_original_second;
  FillListsWithRandomStrings(list_original, list, 100);
  FillListsWithRandomStrings(list_original_second, list_second, 55);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original_second, list_second),
            true);
}

TEST(ListSwapTest, SecondStringsListIsEmpty) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  s21::list<std::string> list_second;
  std::list<std::string> list_original_second;
  FillListsWithRandomStrings(list_original, list, 100);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original_second, list_second),
            true);
}

TEST(ListSwapTest, FirstStringsListIsEmpty) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  s21::list<std::string> list_second;
  std::list<std::string> list_original_second;
  FillListsWithRandomStrings(list_original_second, list_second, 100);
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original_second, list_second),
            true);
}

TEST(ListSwapTest, TwoEmptyLists) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  list_original.swap(list_original_second);
  list.swap(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListReverseTest, RandomIntTest) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 100);
  list.reverse();
  list_original.reverse();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListReverseTest, RandomStringTest) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  FillListsWithRandomStrings(list_original, list, 100);
  list.reverse();
  list_original.reverse();
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListMergeTest, TwoRandomIntsFilled) {
  s21::list<std::string> list;
  std::list<std::string> list_original;
  s21::list<std::string> list_second;
  std::list<std::string> list_original_second;
  FillListsWithRandomStrings(list_original, list, 10000);
  FillListsWithRandomStrings(list_original_second, list_second, 10055);
  list_original.merge(list_original_second);
  list.merge(list_second);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<std::string>(list_original_second, list_second),
            true);
}

TEST(ListMergeTest, SecondIntsListIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);
  list_original.merge(list_original_second);
  list.merge(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListMergeTest, FirstIntsListIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original_second, list_second, 100);
  list_original.merge(list_original_second);
  list.merge(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListMergeTest, TwoEmptyLists) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  list_original.merge(list_original_second);
  list.merge(list_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListUniqueTest, TwoEmptyLists) {
  s21::list<int> list;
  std::list<int> list_original;
  list.unique();
  list_original.unique();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListUniqueTest, IntListsWithUnique) {
  s21::list<int> list = {1, 1, 2, 2, 3, 3, 3, 3};
  std::list<int> list_original = {1, 1, 2, 2, 3, 3, 3, 3};
  list.unique();
  list_original.unique();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListUniqueTest, IntListsWithoutUnique) {
  s21::list<int> list = {1, 2, 3};
  std::list<int> list_original = {1, 2, 3};
  list.unique();
  list_original.unique();
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListUniqueTest, StringListsWithUnique) {
  s21::list<std::string> list = {"a", "a", "b", "c", "d", "d"};
  std::list<std::string> list_original = {"a", "a", "b", "c", "d", "d"};
  list.unique();
  list_original.unique();
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListUniqueTest, StringListsWithoutUnique) {
  s21::list<std::string> list = {"a", "b", "c"};
  std::list<std::string> list_original = {"a", "b", "c"};
  list.unique();
  list_original.unique();
  ASSERT_EQ(CheckListsEqual<std::string>(list_original, list), true);
}

TEST(ListSpliceTest, IntsListsBegin) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);
  FillListsWithRandomInts(list_original_second, list_second, 55);

  auto iterator = list.begin();
  auto iterator_original = list_original.begin();

  list.splice(iterator, list_second);
  list_original.splice(iterator_original, list_original_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSpliceTest, IntsListsEnd) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);
  FillListsWithRandomInts(list_original_second, list_second, 55);

  auto iterator = list.end();
  auto iterator_original = list_original.end();

  list.splice(iterator, list_second);
  list_original.splice(iterator_original, list_original_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSpliceTest, IntsListsSecondIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original, list, 100);

  auto iterator = list.begin();
  auto iterator_original = list_original.begin();

  list.splice(iterator, list_second);
  list_original.splice(iterator_original, list_original_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListSpliceTest, IntsListsBeginFirstIsEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  FillListsWithRandomInts(list_original_second, list_second, 55);

  auto iterator = list.begin();
  auto iterator_original = list_original.begin();

  list.splice(iterator, list_second);
  list_original.splice(iterator_original, list_original_second);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListInsertManyTest, InsertManyIntsBackWithEmptyList) {
  s21::list<int> list;
  std::list<int> list_original;
  list.insert_many_back(1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsFrontWithEmptyList) {
  s21::list<int> list;
  std::list<int> list_original;
  list.insert_many_front(1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsWithEmptyListAndEndIterator) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int>::ListIterator<int> i = list.end();
  list.insert_many(i, 1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsWithEmptyListAndBeginIterator) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int>::ListIterator<int> i = list.begin();
  list.insert_many(i, 1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsBack) {
  s21::list<int> list{100, 200, 300};
  std::list<int> list_original{100, 200, 300};
  list.insert_many_back(1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsFront) {
  s21::list<int> list{100, 200, 300};
  std::list<int> list_original{1, 2, 3, 100, 200, 300};
  list.insert_many_front(1, 2, 3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsEndIterator) {
  s21::list<int> list{100, 200, 300};
  std::list<int> list_original{100, 200, 300};
  s21::list<int>::ListIterator<int> i = list.end();
  list.insert_many(i, 1, 2, 3);
  list_original.push_back(1);
  list_original.push_back(2);
  list_original.push_back(3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsBeginIterator) {
  s21::list<int> list{100, 200, 300};
  std::list<int> list_original{1, 2, 3, 100, 200, 300};
  s21::list<int>::ListIterator<int> i = list.begin();
  list.insert_many(i, 1, 2, 3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListInsertManyTest, InsertManyIntsMidIterator) {
  s21::list<int> list{100, 200, 300};
  std::list<int> list_original{100, 1, 2, 3, 200, 300};
  s21::list<int>::ListIterator<int> i = list.begin();
  i++;
  list.insert_many(i, 1, 2, 3);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
}

TEST(ListIsEmptyTest, IsEmpty) {
  s21::list<int> list;
  ASSERT_EQ(list.empty(), true);
}

TEST(ListIsEmptyTest, NotEmpty) {
  s21::list<int> list{0};
  ASSERT_EQ(list.empty(), false);
}

TEST(ListConstructorsTest, CopyConstructor) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 100);
  s21::list<int> list_second(list);
  std::list<int> list_original_second(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListConstructorsTest, CopyConstructorEmptyLists) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second(list);
  std::list<int> list_original_second(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListConstructorsTest, MoveConstructor) {
  s21::list<int> list;
  std::list<int> list_original;
  FillListsWithRandomInts(list_original, list, 100);
  s21::list<int> list_second = std::move(list);
  std::list<int> list_original_second = std::move(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListConstructorsTest, MoveConstructorEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second = std::move(list);
  std::list<int> list_original_second = std::move(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListOperatorTest, MoveOperator) {
  s21::list<int> list = {1, 2};
  std::list<int> list_original = {1, 2};
  s21::list<int> list_second = {5, 6};
  std::list<int> list_original_second = {5, 6};
  list_second = std::move(list);
  list_original_second = std::move(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListOperatorTest, MoveOperatorEmptyList) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second = {5, 6};
  std::list<int> list_original_second = {5, 6};
  list_second = std::move(list);
  list_original_second = std::move(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListOperatorTest, MoveOperatorBothListsAreEmpty) {
  s21::list<int> list;
  std::list<int> list_original;
  s21::list<int> list_second;
  std::list<int> list_original_second;
  list_second = std::move(list);
  list_original_second = std::move(list_original);
  ASSERT_EQ(CheckListsEqual<int>(list_original, list), true);
  ASSERT_EQ(CheckListsEqual<int>(list_original_second, list_second), true);
}

TEST(ListInsertManyTest, ReturningIteratorTest) {
  s21::list<int> list = {1, 2, 3};
  auto iterator = list.begin();
  iterator++;
  auto new_iterator = list.insert_many(iterator, 5, 6);
  ASSERT_EQ(*new_iterator, 5);
}

TEST(ListInsertManyTest, ReturningIteratorTestEmptyList) {
  s21::list<int> list;
  auto iterator = list.begin();
  iterator++;
  auto new_iterator = list.insert_many(iterator, 5, 6);
  ASSERT_EQ(*new_iterator, 5);
}

TEST(ListConstructorsTest, ExceptionOnNumberOfNodesConstructor) {
  ThrowOnNumberCreated::Reset(5);
  ASSERT_ANY_THROW(s21::list<ThrowOnNumberCreated> list(10));
}

TEST(ListConstructorsTest, SelfAssignmentShoultNoDeleteSelf) {
  s21::list<int> l;
  for (int i = 0; i < 10; ++i) {
    l.push_back(i);
  }

  ASSERT_EQ(l.size(), 10);
  l = l;
  // Это тоже вылидно, но так утечки не видно
  // ASSERT_EQ(l.size(), 10);

  auto it = l.begin();
  for (int i = 0; i < 10; ++i, ++it) {
    ASSERT_EQ(*it, i);
  }
}

TEST(ListInsertManyTest, EmptyInsertMany) {
  s21::list<int> list;
  list.insert_many_back();
  list.insert_many_front();
  list.insert_many(list.begin());
  list.insert_many(list.end());
  ASSERT_EQ(list.empty(), true);
  ASSERT_EQ(list.end(), list.begin());
}
