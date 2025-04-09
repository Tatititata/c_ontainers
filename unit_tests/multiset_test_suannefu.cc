#include <gtest/gtest.h>

#include "../lace_multiset.h"

TEST(MultisetTest, default_constructor) {
  lace::multiset<int> ms;
  ASSERT_TRUE(ms.empty());
  ASSERT_EQ(ms.size(), 0);
}

TEST(MultisetTest, insert_and_count) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);

  ASSERT_EQ(ms.count(1), 1);
  ASSERT_EQ(ms.count(2), 2);
  ASSERT_EQ(ms.size(), 3);
}

TEST(MultisetTest, contains) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);

  ASSERT_TRUE(ms.contains(1));
  ASSERT_TRUE(ms.contains(2));
  ASSERT_FALSE(ms.contains(3));
}

TEST(MultisetTest, erase) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);

  ms.erase(ms.find(2));
  ASSERT_EQ(ms.count(2), 1);

  ms.erase(ms.find(2));
  ASSERT_EQ(ms.count(2), 0);
}

TEST(MultisetTest, clear) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);

  ms.clear();
  ASSERT_TRUE(ms.empty());
  ASSERT_EQ(ms.size(), 0);
}

TEST(MultisetTest, swap) {
  lace::multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);

  lace::multiset<int> ms2;
  ms2.insert(3);
  ms2.insert(4);

  ms1.swap(ms2);

  ASSERT_EQ(ms1.count(3), 1);
  ASSERT_EQ(ms1.count(4), 1);
  ASSERT_EQ(ms2.count(1), 1);
  ASSERT_EQ(ms2.count(2), 1);
}

TEST(MultisetTest, merge) {
  lace::multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);

  lace::multiset<int> ms2;
  ms2.insert(2);
  ms2.insert(3);

  ms1.merge(ms2);

  ASSERT_EQ(ms1.count(1), 1);
  ASSERT_EQ(ms1.count(2), 2);
  ASSERT_EQ(ms1.count(3), 1);
  ASSERT_TRUE(ms2.empty());
}

TEST(MultisetTest, equal_range) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);

  auto range = ms.equal_range(2);
  size_t count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    ++count;
  }
  ASSERT_EQ(count, 2);
}

TEST(MultisetTest, lower_bound) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);

  auto it = ms.lower_bound(2);
  ASSERT_EQ(*it, 2);
}

TEST(MultisetTest, upper_bound) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);

  auto it = ms.upper_bound(2);
  ASSERT_EQ(*it, 3);
}

TEST(MultisetTest, initializer_list_constructor) {
  lace::multiset<int> ms = {1, 2, 2, 3};

  ASSERT_EQ(ms.count(1), 1);
  ASSERT_EQ(ms.count(2), 2);
  ASSERT_EQ(ms.count(3), 1);
  ASSERT_EQ(ms.size(), 4);
}

TEST(MultisetTest, copy_constructor) {
  lace::multiset<int> ms1 = {1, 2, 2, 3};
  lace::multiset<int> ms2(ms1);

  ASSERT_EQ(ms2.count(1), 1);
  ASSERT_EQ(ms2.count(2), 2);
  ASSERT_EQ(ms2.count(3), 1);
  ASSERT_EQ(ms2.size(), 4);
}

TEST(MultisetTest, move_constructor) {
  lace::multiset<int> ms1 = {1, 2, 2, 3};
  lace::multiset<int> ms2(std::move(ms1));

  ASSERT_EQ(ms2.count(1), 1);
  ASSERT_EQ(ms2.count(2), 2);
  ASSERT_EQ(ms2.count(3), 1);
  ASSERT_EQ(ms2.size(), 4);
  ASSERT_TRUE(ms1.empty());
}

TEST(MultisetTest, move_assignment_operator) {
  lace::multiset<int> ms1 = {1, 2, 2, 3};
  lace::multiset<int> ms2;
  ms2 = std::move(ms1);

  ASSERT_EQ(ms2.count(1), 1);
  ASSERT_EQ(ms2.count(2), 2);
  ASSERT_EQ(ms2.count(3), 1);
  ASSERT_EQ(ms2.size(), 4);
  ASSERT_TRUE(ms1.empty());
}

TEST(MultisetTest, max_size) {
  lace::multiset<int> ms;
  ASSERT_GT(ms.max_size(), 0);
}

TEST(MultisetTest, iterator) {
  lace::multiset<int> ms = {1, 2, 2, 3};

  size_t count = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    ++count;
  }
  ASSERT_EQ(count, 4);
}

TEST(MultisetTest, const_iterator) {
  const lace::multiset<int> ms = {1, 2, 2, 3};

  size_t count = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    ++count;
  }
  ASSERT_EQ(count, 4);
}

TEST(MultisetTest, insert_duplicate) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(1);

  ASSERT_EQ(ms.count(1), 2);
  ASSERT_EQ(ms.size(), 2);
}

TEST(MultisetTest, erase_non_existent_element) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);

  auto it = ms.find(3);
  ASSERT_EQ(it, ms.end());
}

TEST(MultisetTest, erase_all_elements) {
  lace::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);

  ms.erase(ms.find(2));
  ms.erase(ms.find(2));
  ms.erase(ms.find(1));

  ASSERT_TRUE(ms.empty());
  ASSERT_EQ(ms.size(), 0);
}

TEST(MultisetTest, string_type) {
  lace::multiset<std::string> ms;
  ms.insert("apple");
  ms.insert("banana");
  ms.insert("apple");

  ASSERT_EQ(ms.count("apple"), 2);
  ASSERT_EQ(ms.count("banana"), 1);
}

TEST(MultisetTest, large_number_of_elements) {
  lace::multiset<int> ms;
  for (int i = 0; i < 10000; ++i) {
    ms.insert(i);
  }
  ASSERT_EQ(ms.size(), 10000);

  for (int i = 0; i < 10000; ++i) {
    ASSERT_TRUE(ms.contains(i));
  }
}

TEST(MultisetTest, merge_identical) {
  lace::multiset<int> ms1 = {1, 2, 2, 3, 4, 4, 4};
  lace::multiset<int> ms2 = {1, 2, 2, 3, 4, 4, 4};
  size_t s = ms1.size() + ms2.size();
  ms1.merge(ms2);

  lace::multiset<int> expected_ms = {1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 4, 4};

  ASSERT_EQ(ms1.size(), expected_ms.size());
  ASSERT_EQ(ms1.size(), s);
  ASSERT_TRUE(ms2.empty());
}

TEST(MultisetTest, merge_non_identical) {
  lace::multiset<int> ms1 = {1, 2, 3, 4, 5};
  lace::multiset<int> ms2 = {3, 4, 5, 6, 7, 7};
  size_t s = ms1.size() + ms2.size();
  ms1.merge(ms2);

  lace::multiset<int> expected_ms = {1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 7};

  ASSERT_EQ(ms1.size(), expected_ms.size());
  ASSERT_EQ(ms1.size(), s);
  ASSERT_TRUE(ms2.empty());
}

TEST(MultisetTest, lower_bound_test) {
  lace::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5, 5};

  auto it1 = ms.lower_bound(3);
  ASSERT_EQ(*it1, 3);

  auto it2 = ms.lower_bound(4);
  ASSERT_EQ(*it2, 4);

  auto it3 = ms.lower_bound(1);
  ASSERT_EQ(*it3, 1);

  auto it4 = ms.lower_bound(6);
  ASSERT_EQ(it4, ms.end());
  auto it5 = ms.lower_bound(0);
  ASSERT_EQ(*ms.begin(), *it5);
}

TEST(MultisetTest, upper_bound_test) {
  lace::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5, 5};

  auto it1 = ms.upper_bound(3);
  ASSERT_EQ(*it1, 4);

  auto it2 = ms.upper_bound(4);
  ASSERT_EQ(*it2, 5);

  auto it3 = ms.upper_bound(1);
  ASSERT_EQ(*it3, 2);

  auto it4 = ms.upper_bound(5);
  ASSERT_EQ(it4, ms.end());

  auto it5 = ms.upper_bound(0);
  ASSERT_EQ(*ms.begin(), *it5);
}

TEST(MultisetTest, equal_range_test) {
  lace::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5, 5};

  auto range1 = ms.equal_range(3);
  auto it_begin1 = range1.first;
  auto it_end1 = range1.second;

  std::vector<int> expected1 = {3, 3, 3};
  std::vector<int> actual1;
  while (it_begin1 != it_end1) {
    actual1.push_back(*it_begin1);
    ++it_begin1;
  }
  ASSERT_EQ(actual1, expected1);

  auto range2 = ms.equal_range(2);
  auto it_begin2 = range2.first;
  auto it_end2 = range2.second;

  std::vector<int> expected2 = {2, 2};
  std::vector<int> actual2;
  while (it_begin2 != it_end2) {
    actual2.push_back(*it_begin2);
    ++it_begin2;
  }
  ASSERT_EQ(actual2, expected2);

  auto range3 = ms.equal_range(6);
  ASSERT_EQ(range3.first, ms.end());
  ASSERT_EQ(range3.second, ms.end());
}

TEST(MultisetInsertManyTest, insert_multiple_elements) {
  lace::multiset<int> ms;
  auto results = ms.insert_many(5, 3, 5, 2, 3, 3);

  ASSERT_EQ(ms.size(), 6);
  ASSERT_EQ(results.size(), 6);

  ASSERT_EQ(ms.count(5), 2);
  ASSERT_EQ(ms.count(3), 3);
  ASSERT_EQ(ms.count(2), 1);

  for (const auto& result : results) {
    ASSERT_TRUE(result.second);
  }
}

TEST(MultisetInsertManyTest, insert_empty) {
  lace::multiset<std::string> ms = {"apple", "banana"};
  auto results = ms.insert_many();

  ASSERT_TRUE(results.empty());
  ASSERT_EQ(ms.size(), 2);
}

TEST(MultisetInsertManyTest, iterator_validity) {
  lace::multiset<int> ms = {10, 20};
  auto it_before = ms.begin();

  auto results = ms.insert_many(15, 10, 25);

  ASSERT_EQ(*it_before, 10);
  ++it_before;
  ASSERT_EQ(*it_before, 10);

  ASSERT_EQ(*results[0].first, 15);
  ASSERT_EQ(*results[1].first, 10);
  ASSERT_EQ(*results[2].first, 25);
}

TEST(MultisetInsertManyTest, mixed_types_conversion) {
  lace::multiset<double> ms;
  auto results = ms.insert_many(1, 2.5f, 3u, 4.0);

  ASSERT_EQ(ms.size(), 4);
  ASSERT_TRUE(ms.contains(1.0));
  ASSERT_TRUE(ms.contains(2.5));
  ASSERT_TRUE(ms.contains(3.0));
  ASSERT_TRUE(ms.contains(4.0));
}

TEST(MultisetInsertManyTest, order_preservation) {
  lace::multiset<int> ms = {1, 3, 5};
  ms.insert_many(2, 4, 6);

  std::vector<int> expected = {1, 2, 3, 4, 5, 6};
  std::vector<int> actual;

  for (const auto& item : ms) {
    actual.push_back(item);
  }

  ASSERT_EQ(actual, expected);
}

TEST(MultisetInsertManyTest, performance_test) {
  const int kCount = 10000;
  lace::multiset<int> ms;

  std::vector<int> values;
  for (int i = 0; i < kCount; ++i) {
    values.push_back(i % 100);
  }
  for (int val : values) {
    ms.insert(val);
  }
}

TEST(MultisetInsertManyTest, return_value_check) {
  lace::multiset<int> ms = {1, 2, 2, 3};
  auto results = ms.insert_many(2, 4, 2, 5);

  ASSERT_EQ(results.size(), 4);

  ASSERT_EQ(*results[0].first, 2);
  ASSERT_EQ(*results[1].first, 4);
  ASSERT_EQ(*results[2].first, 2);
  ASSERT_EQ(*results[3].first, 5);

  ASSERT_NE(ms.find(2), ms.end());
  ASSERT_NE(ms.find(4), ms.end());
  ASSERT_NE(ms.find(5), ms.end());

  ASSERT_TRUE(results[0].second);
  ASSERT_TRUE(results[1].second);
  ASSERT_TRUE(results[2].second);
  ASSERT_TRUE(results[3].second);
}

TEST(MultisetBoundsTest, lower_bound_test) {
  lace::multiset<int> ms = {10, 20, 20, 30, 40};

  auto lb1 = ms.lower_bound(20);
  ASSERT_NE(lb1, ms.end());
  ASSERT_EQ(*lb1, 20);
  auto lb2 = ms.lower_bound(25);
  ASSERT_NE(lb2, ms.end());
  ASSERT_EQ(*lb2, 30);
  auto lb3 = ms.lower_bound(50);
  ASSERT_EQ(lb3, ms.end());
}

TEST(MultisetBoundsTest, upper_bound_test) {
  lace::multiset<int> ms = {10, 20, 20, 30, 40};
  auto ub1 = ms.upper_bound(20);
  ASSERT_NE(ub1, ms.end());
  ASSERT_EQ(*ub1, 30);
  auto ub2 = ms.upper_bound(25);
  ASSERT_NE(ub2, ms.end());
  ASSERT_EQ(*ub2, 30);
  auto ub3 = ms.upper_bound(50);
  ASSERT_EQ(ub3, ms.end());
}

TEST(MultisetBoundsTest, equal_range_test) {
  lace::multiset<int> ms = {10, 20, 20, 30, 40};
  auto range1 = ms.equal_range(20);
  ASSERT_NE(range1.first, ms.end());
  ASSERT_NE(range1.second, ms.end());
  ASSERT_EQ(*range1.first, 20);
  ASSERT_EQ(*range1.second, 30);

  ASSERT_EQ(std::distance(range1.first, range1.second), 2);
  int count = 0;
  for (auto it = range1.first; it != range1.second; ++it) {
    ASSERT_EQ(*it, 20);
    ++count;
  }
  ASSERT_EQ(count, 2);

  auto range2 = ms.equal_range(25);
  ASSERT_EQ(*range2.first, 30);
  ASSERT_EQ(*range2.second, 30);
  ASSERT_EQ(range2.first, range2.second);

  auto range3 = ms.equal_range(50);
  ASSERT_EQ(range3.first, ms.end());
  ASSERT_EQ(range3.second, ms.end());
}

TEST(MultisetBoundsTest, empty_tree_test) {
  lace::multiset<int> ms;

  auto lb = ms.lower_bound(10);
  auto ub = ms.upper_bound(10);
  auto range = ms.equal_range(10);

  ASSERT_EQ(lb, ms.end());
  ASSERT_EQ(ub, ms.end());
  ASSERT_EQ(range.first, ms.end());
  ASSERT_EQ(range.second, ms.end());
}

TEST(MultisetBoundsTest, single_element_test) {
  lace::multiset<int> ms = {42};

  auto range = ms.equal_range(42);
  ASSERT_NE(range.first, ms.end());
  ASSERT_EQ(range.second, ms.end());
  ASSERT_EQ(*range.first, 42);
  ASSERT_EQ(std::distance(range.first, range.second), 1);
}

TEST(MultisetTest, IteratorArrowOperator) {
  struct Person {
    std::string name;
    int age;

    bool operator<(const Person& other) const { return age < other.age; }
    bool operator>(const Person& other) const { return age > other.age; }
    bool operator==(const Person& other) const { return age == other.age; }
  };

  lace::multiset<Person> people;
  people.insert({"Eug", 25});
  people.insert({"Eug", 25});
  people.insert({"Dan", 30});
  people.insert({"Dan", 30});

  auto it = people.begin();
  EXPECT_EQ(it->name, "Eug");
  EXPECT_EQ(it->age, 25);

  ++it;
  EXPECT_EQ(it->name, "Eug");
  EXPECT_EQ(it->age, 25);

  const lace::multiset<Person> const_people = people;
  lace::multiset<Person>::const_iterator const_it = const_people.begin();
  EXPECT_EQ(const_it->name, "Eug");
  EXPECT_EQ(const_it->age, 25);
  ++const_it;
  const_it++;
  EXPECT_EQ(const_it->name, "Dan");
  EXPECT_EQ(const_it->age, 30);
}

TEST(MultisetTest, IteratorDecrement) {
  lace::multiset<int> ms = {1, 2, 2, 3};
  auto it = ++ms.begin();
  --it;
  ASSERT_EQ(*it, 1);
  it = ++(++ms.begin());
  it--;
  --it;
  ASSERT_EQ(*it, 1);
}

TEST(MultisetTest, MergeTest) {
  lace::multiset<int> ms1 = {};
  lace::multiset<int> ms2 = {1, 2, 2, 2, 2, 2};
  ms1.merge(ms2);
  ASSERT_EQ(ms1.size(), 6);
  ASSERT_EQ(ms1.count(2), 5);
  ASSERT_EQ(ms2.size(), 0);
}

TEST(MultisetTest, MergeSelf) {
  lace::multiset<int> ms1 = {1, 2, 2, 2, 2, 2};
  ms1.merge(ms1);
  ASSERT_EQ(ms1.size(), 6);
  ASSERT_EQ(ms1.count(2), 5);
}

TEST(MultisetTest, ConstBounds) {
  const lace::multiset<int> ms = {1, 2, 2, 3};
  auto lb = ms.lower_bound(2);
  auto ub = ms.upper_bound(2);
  ASSERT_EQ(*lb, 2);
  ASSERT_EQ(*ub, 3);
}

TEST(MultisetTest, ConstIteratorDereferenceEndThrows) {
  const lace::multiset<int> ms = {1, 2};
  auto it = ms.end();
  EXPECT_THROW(*it, std::runtime_error);
  EXPECT_THROW(it.operator->(), std::runtime_error);
}

TEST(MultisetTest, ConstIteratorIncrementEndThrows) {
  const lace::multiset<int> ms = {1, 2};
  auto it = ms.end();
  EXPECT_THROW(++it, std::runtime_error);
}

TEST(MultisetTest, IteratorDereferenceEndThrows) {
  lace::multiset<int> ms = {1, 2};
  auto it = ms.end();

  EXPECT_THROW(*it, std::runtime_error);
  EXPECT_THROW(it.operator->(), std::runtime_error);
}

TEST(MultisetTest, IteratorIncrementEndThrows) {
  lace::multiset<int> ms = {1, 2};
  auto it = ms.end();

  EXPECT_THROW(++it, std::runtime_error);
}
