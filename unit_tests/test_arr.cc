#include <gtest/gtest.h>

#include "../s21_array.h"
#include "../s21_list.h"
#include "../s21_vector.h"

TEST(array_test, vector_inside_array) {
  s21::array<s21::vector<int>, 3> arr;
  arr[0].push_back(1);
  arr[1].push_back(2);
  arr[2].push_back(3);
  EXPECT_EQ(arr[0].at(0), 1);
  EXPECT_EQ(arr[1].at(0), 2);
  EXPECT_EQ(arr[2].at(0), 3);
}

TEST(array_test, list_inside_array) {
  s21::array<s21::list<int>, 2> arr;
  arr[0].push_back(42);
  arr[1].push_back(99);
  EXPECT_EQ(arr[0].front(), 42);
  EXPECT_EQ(arr[1].front(), 99);
}

TEST(array_test, default_constructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr.max_size(), 5);
  EXPECT_EQ(arr.empty(), false);
}

TEST(array_test, element_access) {
  s21::array<int, 3> arr;
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(array_test, out_of_bounds) {
  s21::array<int, 3> arr;
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(array_test, in_bounds) {
  s21::array<int, 3> arr;
  arr[2] = 532;
  EXPECT_EQ(arr.at(2), 532);
}

TEST(array_test, strings) {
  s21::array<std::string, 4> arr;
  arr[0] = "brucetor";
  arr[1] = "ardislor";
  arr[2] = "ronnelre";
  arr[3] = "suannefu";
  EXPECT_EQ(arr[0][0], 'b');
  EXPECT_EQ(arr[1], "ardislor");
  EXPECT_EQ(arr[2], "ronnelre");
  EXPECT_EQ(arr[3], "suannefu");
}

TEST(array_test, array) {
  s21::array<s21::array<double, 3>, 4> matrix;
  matrix[0][0] = 1.1;
  matrix[0][1] = 1.2;
  matrix[0][2] = 1.3;

  matrix[1][0] = 2.1;
  matrix[1][1] = 2.2;
  matrix[1][2] = 2.3;

  matrix[2][0] = 3.1;
  matrix[2][1] = 3.2;
  matrix[2][2] = 3.3;

  matrix[3][0] = 4.1;
  matrix[3][1] = 4.2;
  matrix[3][2] = 4.3;

  EXPECT_DOUBLE_EQ(matrix[0][0], 1.1);
  EXPECT_DOUBLE_EQ(matrix[0][1], 1.2);
  EXPECT_DOUBLE_EQ(matrix[0][2], 1.3);

  EXPECT_DOUBLE_EQ(matrix[1][0], 2.1);
  EXPECT_DOUBLE_EQ(matrix[1][1], 2.2);
  EXPECT_DOUBLE_EQ(matrix[1][2], 2.3);

  EXPECT_DOUBLE_EQ(matrix[2][0], 3.1);
  EXPECT_DOUBLE_EQ(matrix[2][1], 3.2);
  EXPECT_DOUBLE_EQ(matrix[2][2], 3.3);

  EXPECT_DOUBLE_EQ(matrix[3][0], 4.1);
  EXPECT_DOUBLE_EQ(matrix[3][1], 4.2);
  EXPECT_DOUBLE_EQ(matrix[3][2], 4.3);

  EXPECT_EQ(matrix.size(), 4);
  EXPECT_EQ(matrix[0].size(), 3);
}

TEST(array_test, std_map_int_string) {
  using MapType = std::map<int, std::string>;
  s21::array<MapType, 5> arr;

  for (int i = 0; i < 5; ++i) {
    MapType map;
    map[i] = "Value_" + std::to_string(i);
    arr[i] = map;
  }

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i].size(), 1);
    EXPECT_EQ(arr[i].at(i), "Value_" + std::to_string(i));
  }
}

TEST(array_test, initializer_list_constructor) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(array_test, initializer_small_list_constructor) {
  s21::array<int, 5> arr = {1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 1);
  EXPECT_EQ(arr[4], 1);
}

TEST(array_test, copy_constructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array_test, move_constructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array_test, move_assignment) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array_test, front_back) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 3);
}

TEST(array_test, iterators) {
  s21::array<int, 3> arr = {1, 2, 3};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  it = arr.end();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(array_test, swap) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(array_test, fill) {
  s21::array<int, 5> arr;
  arr.fill(7);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 7);
  }
}

TEST(array_test, data) {
  s21::array<int, 3> arr = {1, 2, 3};
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

TEST(array_test, front_back_empty) {
  s21::array<int, 0> arr;
  EXPECT_THROW(arr.front(), std::out_of_range);
  EXPECT_THROW(arr.back(), std::out_of_range);
}

class ThrowOnCopy {
 public:
  int data;

  ThrowOnCopy(int d) : data(d) {}

  ThrowOnCopy(const ThrowOnCopy&) { throw std::runtime_error("Ошибка!"); }
};

TEST(array_test, throw_on_copy) {
  EXPECT_THROW((s21::array<ThrowOnCopy, 2>{ThrowOnCopy(1), ThrowOnCopy(2)}),
               std::runtime_error);
}
