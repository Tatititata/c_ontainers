#include <gtest/gtest.h>

#include "../s21_queue.h"

TEST(queue_test, default_constructor) {
  s21::s21_queue<int> que;
  EXPECT_EQ(que.size(), 0);
  EXPECT_EQ(que.empty(), true);
}

class Test_count_obj {
 public:
  static int count;

  Test_count_obj() { ++count; }
  Test_count_obj(const Test_count_obj&) { ++count; }
  ~Test_count_obj() { --count; }
};
int Test_count_obj::count = 0;

TEST(queue_test, default_destructor) {
  {
    s21::s21_queue<Test_count_obj> que;
    que.push(Test_count_obj());
    que.push(Test_count_obj());
    EXPECT_GT(Test_count_obj::count, 0);
  }
  EXPECT_EQ(Test_count_obj::count, 0);
}

TEST(queue_test, initializer_list_constructor) {
  s21::s21_queue<int> q{1, 2, 3, 4};
  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}

TEST(queue_test, copy_constructor) {
  s21::s21_queue<int> orig{5, 6, 7};
  s21::s21_queue<int> copy(orig);

  EXPECT_EQ(orig.size(), copy.size());
  EXPECT_EQ(orig.front(), copy.front());
  EXPECT_EQ(orig.back(), copy.back());
}

TEST(queue_test, move_constructor) {
  s21::s21_queue<int> orig{10, 20, 30};
  s21::s21_queue<int> moved(std::move(orig));

  EXPECT_TRUE(orig.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 10);
  EXPECT_EQ(moved.back(), 30);
}

TEST(queue_test, move_assignment_operator) {
  s21::s21_queue<int> orig{100, 200};
  s21::s21_queue<int> target;
  target = std::move(orig);

  EXPECT_TRUE(orig.empty());
  EXPECT_EQ(target.size(), 2);
  EXPECT_EQ(target.front(), 100);
  EXPECT_EQ(target.back(), 200);
}

TEST(queue_test, push_pop) {
  s21::s21_queue<std::string> que;
  que.push("first");
  que.push("second");

  EXPECT_EQ(que.size(), 2);
  EXPECT_EQ(que.front(), "first");

  que.pop();
  EXPECT_EQ(que.size(), 1);
  EXPECT_EQ(que.front(), "second");
}

TEST(queue_test, front_back) {
  s21::s21_queue<char> que{'a', 'b', 'c'};
  EXPECT_EQ(que.front(), 'a');
  EXPECT_EQ(que.back(), 'c');

  que.front() = 'x';
  que.back() = 'z';
  EXPECT_EQ(que.front(), 'x');
  EXPECT_EQ(que.back(), 'z');
}

TEST(queue_test, large_data) {
  s21::s21_queue<int> que;
  for (int i = 0; i < 10000; ++i) {
    que.push(i);
  }

  EXPECT_EQ(que.size(), 10000);
  EXPECT_EQ(que.back(), 9999);

  for (int i = 0; i < 5000; ++i) {
    que.pop();
  }

  EXPECT_EQ(que.size(), 5000);
  EXPECT_EQ(que.front(), 5000);
}

TEST(QueueTest, Swap) {
  s21::s21_queue<int> q1{1, 2, 3};
  s21::s21_queue<int> q2{4, 5};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
}