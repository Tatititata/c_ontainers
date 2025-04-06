#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "../s21_vector.h"

TEST(VectorRuleOf5Test, IntCreateEmpty) {
  s21::vector<int> vec;
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0);
}

TEST(VectorRuleOf5Test, IntCreateSize10) {
  s21::vector<int> vec(10);
  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}

TEST(VectorRuleOf5Test, IntCreateByCopyFromOther) {
  s21::vector<int> other(10);
  s21::vector<int> vec(other);

  ASSERT_EQ(10, vec.size());
  ASSERT_EQ(10, other.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
    ASSERT_EQ(other[i], 0);
  }
}

TEST(VectorRuleOf5Test, IntCreateByMoveFromOther) {
  s21::vector<int> other(10);
  s21::vector<int> vec(std::move(other));

  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}

TEST(VectorRuleOf5Test, IntCopyByCopyFromOther) {
  s21::vector<int> other(10);
  s21::vector<int> vec(1);
  vec = other;

  ASSERT_EQ(10, other.size());
  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
    ASSERT_EQ(other[i], 0);
  }
}

TEST(VectorRuleOf5Test, IntCopyByCopyFromSelf) {
  s21::vector<int> vec(10);
  vec = vec;

  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}

TEST(VectorRuleOf5Test, IntCopyByMoveFromOther) {
  s21::vector<int> other(10);
  s21::vector<int> vec(1);
  vec = std::move(other);

  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}

/* be smart!
TEST(VectorRuleOf5Test, IntCopyByMoveFromSelf) {
  s21::vector<int> vec(10);

  vec = std::move(vec);

  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}
*/

TEST(VectorRuleOf5Test, StringCreateEmpty) {
  s21::vector<std::string> vec;
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0);
}

TEST(VectorRuleOf5Test, StringCreateSize240) {
  s21::vector<std::string> vec(240);
  ASSERT_EQ(240, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::string{});
  }
}

TEST(VectorRuleOf5Test, StringCreateByCopyFromOther) {
  s21::vector<std::string> other(240);
  for (size_t i = 0; i < other.size(); ++i) {
    other[i] = std::to_string(i);
  }

  s21::vector<std::string> vec(other);

  ASSERT_EQ(240, vec.size());
  ASSERT_EQ(240, other.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
    ASSERT_EQ(other[i], std::to_string(i));
  }
}

TEST(VectorRuleOf5Test, StringCreateByMoveFromOther) {
  s21::vector<std::string> other(240);
  for (size_t i = 0; i < other.size(); ++i) {
    other[i] = std::to_string(i);
  }

  s21::vector<std::string> vec(std::move(other));

  ASSERT_EQ(240, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
  }
}

TEST(VectorRuleOf5Test, StringCopyByCopyFromOther) {
  s21::vector<std::string> other(240);
  for (size_t i = 0; i < other.size(); ++i) {
    other[i] = std::to_string(i);
  }

  s21::vector<std::string> vec(1);
  vec = other;

  ASSERT_EQ(240, other.size());
  ASSERT_EQ(240, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
    ASSERT_EQ(other[i], std::to_string(i));
  }
}

TEST(VectorRuleOf5Test, StringCopyByCopyFromSelf) {
  s21::vector<std::string> vec(240);
  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i] = std::to_string(i);
  }

  vec = vec;

  ASSERT_EQ(240, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
  }
}

TEST(VectorRuleOf5Test, StringCopyByMoveFromOther) {
  s21::vector<std::string> other(240);
  for (size_t i = 0; i < other.size(); ++i) {
    other[i] = std::to_string(i);
  }

  s21::vector<std::string> vec(1);
  vec = std::move(other);

  ASSERT_EQ(240, vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
  }
}

TEST(VectorPushBackTest, PushManyIntsToEmpty) {
  size_t number_of_ints = 100;
  s21::vector<size_t> vec;
  for (size_t i = 0; i < number_of_ints; ++i) {
    vec.push_back(i);
  }

  ASSERT_EQ(number_of_ints, vec.size());
}

TEST(VectorPushBackTest, PushManyIntsToReserved) {
  size_t number_of_ints = 100;
  s21::vector<size_t> vec;
  vec.reserve(number_of_ints);

  ASSERT_TRUE(number_of_ints <= vec.capacity());
  ASSERT_EQ(0, vec.size());

  for (size_t i = 0; i < number_of_ints; ++i) {
    vec.push_back(i);
  }

  ASSERT_EQ(number_of_ints, vec.capacity());
  ASSERT_EQ(number_of_ints, vec.size());
}

TEST(VectorPushBackTest, PushManyStringsToEmpty) {
  size_t number_of_strings = 200;
  s21::vector<std::string> vec;
  vec.reserve(number_of_strings);

  ASSERT_TRUE(number_of_strings <= vec.capacity());
  ASSERT_EQ(0, vec.size());

  for (size_t i = 0; i < number_of_strings; ++i) {
    std::string value = std::to_string(i);
    vec.push_back(value);
  }

  ASSERT_EQ(number_of_strings, vec.capacity());
  ASSERT_EQ(number_of_strings, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], std::to_string(i));
  }
}

TEST(VectorPushBackTest, PushManyStringThenReserveThenPush) {
  s21::vector<std::vector<std::string>> vec;

  ASSERT_EQ(0, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    std::vector<std::string> to_insert;
    vec.push_back(to_insert);
    for (size_t j = 0; j < 100; ++j) {
      vec[i].push_back(std::to_string(i * 1000));
    }
  }
  // no that this would be wrong
  // but no point to continue
  ASSERT_TRUE(vec.capacity() < 500);

  for (size_t i = 100; i <= 10000; i += 100) {
    vec.reserve(i);
  }

  ASSERT_TRUE(vec.capacity() >= 10000);
  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 500; ++i) {
    std::vector<std::string> to_insert;
    vec.push_back(to_insert);
    for (size_t j = 0; j < 100; ++j) {
      vec[i].push_back(std::to_string(i * 1000));
    }
  }

  ASSERT_EQ(500 + 10, vec.size());
}

TEST(VectorShrinkToFitTest, PushManyStringThenReserveThenShrinkToFit) {
  s21::vector<std::vector<std::string>> vec;

  ASSERT_EQ(0, vec.size());

  for (size_t i = 0; i < 10; ++i) {
    std::vector<std::string> to_insert;
    vec.push_back(to_insert);
    for (size_t j = 0; j < 100; ++j) {
      vec[i].push_back(std::to_string(i * 1000));
    }
  }
  // no that this would be wrong
  // but no point to continue
  ASSERT_TRUE(vec.capacity() < 500);

  for (size_t i = 100; i <= 10000; i += 100) {
    vec.reserve(i);
  }

  ASSERT_TRUE(vec.capacity() >= 10000);
  ASSERT_EQ(10, vec.size());

  for (size_t i = 0; i < 500; ++i) {
    std::vector<std::string> to_insert;
    vec.push_back(to_insert);
    for (size_t j = 0; j < 100; ++j) {
      vec[i].push_back(std::to_string(i * 1000));
    }
  }

  ASSERT_EQ(500 + 10, vec.size());

  vec.shrink_to_fit();
  ASSERT_EQ(vec.capacity(), vec.size());
}

TEST(VectorAccessTest, ConstAtOnEmptyVectorShouldThrow) {
  const s21::vector<std::vector<std::string>> vec;
  ASSERT_ANY_THROW(auto el = vec.at(0));
}

TEST(VectorAccessTest, ConstAtInBoundsShouldNotThrow) {
  const s21::vector<std::vector<std::string>> vec(10);
  ASSERT_NO_THROW(auto el = vec.at(0));
}

TEST(VectorAccessTest, ConstAtOutOfBoundsShouldThrow) {
  const s21::vector<std::vector<std::string>> vec(10);
  ASSERT_ANY_THROW(auto el = vec.at(12));
}

TEST(VectorAccessTest, ConstAtAtTheBoundShouldThrow) {
  const s21::vector<std::vector<std::string>> vec(10);
  ASSERT_ANY_THROW(auto el = vec.at(10));
}

TEST(VectorAccessTest, AtOnEmptyVectorShouldThrow) {
  s21::vector<std::vector<std::string>> vec;
  ASSERT_ANY_THROW(auto el = vec.at(0));
}

TEST(VectorAccessTest, AtInBoundsShouldNotThrow) {
  s21::vector<std::vector<std::string>> vec(10);
  std::string long_string = "hellow";
  for (size_t i = 0; i < 10; ++i) {
    long_string += long_string;
  }
  ASSERT_NO_THROW(auto el = vec.at(0) = {long_string});
  ASSERT_TRUE(vec.at(0) == std::vector<std::string>{long_string});
}

TEST(VectorAccessTest, AtOutOfBoundsShouldThrow) {
  s21::vector<std::vector<std::string>> vec(10);
  ASSERT_ANY_THROW(auto el = vec.at(12));
}

TEST(VectorAccessTest, AtAtTheBoundShouldThrow) {
  s21::vector<std::vector<std::string>> vec(10);
  ASSERT_ANY_THROW(auto el = vec.at(10));
}

TEST(VectorMemoryTest, ClearClearsEmptyVector) {
  s21::vector<std::vector<std::string>> vec;
  vec.clear();
  ASSERT_EQ(0, vec.size());
}

TEST(VectorMemoryTest, ClearClearsNonEmptyVectorButLeavesCapacity) {
  s21::vector<std::vector<std::string>> vec(100);
  ASSERT_EQ(100, vec.size());
  auto capacity = vec.capacity();
  ASSERT_TRUE(capacity >= 100);

  vec.clear();
  ASSERT_EQ(0, vec.size());
  // https://en.cppreference.com/w/cpp/container/vector/clear
  // `Leaves the capacity() of the vector unchanged` (c)
  ASSERT_EQ(capacity, vec.capacity());
}

TEST(VectorMemoryTest, STDReverseWorks) {
  using VecT = s21::vector<size_t>;

  VecT original(100);
  size_t x = 11;
  for (auto& el : original) {
    el = x;
    x = (x * 1213091ull + 1233ull) % 3120983ull;
  }
  ASSERT_EQ(original[0], 11);

  VecT reversed = original;
  std::reverse(reversed.begin(), reversed.end());

  VecT reversed_again;
  while (!reversed.empty()) {
    reversed_again.push_back(reversed.back());
    reversed.pop_back();
  }

  ASSERT_TRUE(
      std::equal(original.begin(), original.end(), reversed_again.begin()));
}
