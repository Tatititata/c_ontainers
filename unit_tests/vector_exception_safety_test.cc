#include <gtest/gtest.h>

#include <vector>

#include "../s21_vector.h"
#include "throw_on_number_created.h"

template <typename T>
using Vector = s21::vector<T>;

TEST(VectorExcpetionSafetyTest, SizedConstructor) {
  ThrowOnNumberCreated::Reset(5);

  ASSERT_ANY_THROW(Vector<ThrowOnNumberCreated> vec(10));
}

TEST(VectorExcpetionSafetyTest, PushBack) {
  // 7
  // -> 1 to create insert_value
  // -> 5 to push
  // -> 1 to throw
  ThrowOnNumberCreated::Reset(7);

  Vector<ThrowOnNumberCreated> vec;
  vec.reserve(10);
  ThrowOnNumberCreated insert_value;
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_NO_THROW(vec.push_back(insert_value));
  }
  ASSERT_ANY_THROW(vec.push_back(insert_value));
}

TEST(VectorExcpetionSafetyTest, Reserve) {
  ThrowOnNumberCreated::Reset(3);

  ThrowOnNumberCreated insert_value;
  Vector<ThrowOnNumberCreated> vec;
  vec.reserve(1);
  vec.push_back(insert_value);

  ASSERT_ANY_THROW(vec.push_back(insert_value));
}
