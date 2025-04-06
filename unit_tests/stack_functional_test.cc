#include <gtest/gtest.h>

#include <stack>
#include <string>

#include "../s21_stack.h"
#include "throw_on_copy.h"

TEST(Stack, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(Stack, ListConstructor) {
  s21::stack<int> my_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(Stack, CopyConstructor) {
  s21::stack<int> my_stack{1, 2, 3};
  s21::stack<int> my_stack2(my_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack2.top(), std_stack.top());
}

TEST(Stack, MoveConstructor) {
  s21::stack<int> my_stack{1, 2, 3};
  s21::stack<int> my_stack2(std::move(my_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack2.top(), std_stack.top());
}

TEST(Stack, CopyAssignment) {
  s21::stack<int> my_stack{1, 2, 3};
  s21::stack<int> my_stack2;
  my_stack2 = my_stack;
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack2.top(), std_stack.top());
}

TEST(Stack, MoveAssignment) {
  s21::stack<int> my_stack{1, 2, 3};
  s21::stack<int> my_stack2;
  my_stack2 = std::move(my_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack2.top(), std_stack.top());
}

TEST(Stack, Push) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  my_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(Stack, Pop) {
  s21::stack<int> my_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  my_stack.pop();
  std_stack.pop();
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(Stack, Swap) {
  s21::stack<int> my_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  s21::stack<int> my_stack2;
  std::stack<int> std_stack2;
  my_stack2.swap(my_stack);
  std_stack2.swap(std_stack);
  EXPECT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(Stack, Top) {
  s21::stack<int> my_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(Stack, ListConstructor2) {
  s21::stack<int> s = {};
  assert(s.size() == 0);
  assert(s.empty() == true);
}

TEST(Stack, InitializerListCompareWithStd) {
  s21::stack<int> s = {1, 2, 3};
  std::stack<int> std_s({1, 2, 3});
  EXPECT_EQ(s.size(), std_s.size());
  while (!s.empty() && !std_s.empty()) {
    EXPECT_EQ(s.top(), std_s.top());
    s.pop();
    std_s.pop();
  }
}

TEST(Stack, EmptyInitializerList) {
  s21::stack<int> s = {};
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
  if (!s.empty()) {  // Защита от UB
    s.pop();
    s.top();
  }
}

TEST(Stack, InitializerListThenPush) {
  s21::stack<int> s = {};
  s.push(42);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 42);
}

TEST(Stack, EmptyListAddElement) {
  s21::stack<int> s = {};
  s.push(100);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 100);
}

TEST(Stack, SingleElementList) {
  s21::stack<std::string> s = {"hello"};

  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), "hello");
}

TEST(Stack, MultipleElementList) {
  s21::stack<std::string> s = {"hello", "world"};
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), "world");
}

TEST(Stack, insert_many_back) {
  s21::stack<int> s = {1, 2, 3};
  s.insert_many_back(4, 5, 6);
  EXPECT_EQ(s.size(), 6);
  EXPECT_EQ(s.top(), 6);
  while (!s.empty()) {
    s.pop();
  }
  EXPECT_TRUE(s.empty());
}

TEST(StackString, DefaultConstructor) {
  s21::stack<std::string> my_stack;
  std::stack<std::string> std_stack;
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(StackString, ListConstructor) {
  s21::stack<std::string> my_stack{"1", "2", "3"};
  std::stack<std::string> std_stack;
  std_stack.push("1");
  std_stack.push("2");
  std_stack.push("3");
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(StackString, CopyConstructor) {
  s21::stack<std::string> my_stack{
      "Hello, this is a very long string la-la-la para-pa-pa",
      "i'm testing stack implementation la-la-la para-pa-pa",
      "senior developer skills required la-la-la para-pa-pa",
      "c++ is awesome but tricky la-la-la para-pa-pa",
      "developer, let's fix this bug la-la-la para-pa-pa",
      "not tomate, but debugging fun la-la-la para-pa-pa"};
  s21::stack<std::string> my_stack2(my_stack);
  std::stack<std::string> std_stack;
  std_stack.push("Hello, this is a very long string la-la-la para-pa-pa");
  std_stack.push("i'm testing stack implementation la-la-la para-pa-pa");
  std_stack.push("senior developer skills required la-la-la para-pa-pa");
  std_stack.push("c++ is awesome but tricky la-la-la para-pa-pa");
  std_stack.push("developer, let's fix this bug la-la-la para-pa-pa");
  std_stack.push("not tomate, but debugging fun la-la-la para-pa-pa");
  EXPECT_EQ(my_stack2.top(), std_stack.top());
  EXPECT_EQ(my_stack2.size(), std_stack.size());
}

TEST(StackString, CopyConstructor2) {
  s21::stack<s21::stack<std::string>> my_stack{
      s21::stack<std::string>{"1", "2", "3"},
      s21::stack<std::string>{"4", "5", "6"},
      s21::stack<std::string>{"7", "8", "9"}};
  s21::stack<s21::stack<std::string>> my_stack2(my_stack);
  std::stack<std::stack<std::string>> std_stack;
  std_stack.push(std::stack<std::string>({"1", "2", "3"}));
  std_stack.push(std::stack<std::string>({"4", "5", "6"}));
  std_stack.push(std::stack<std::string>({"7", "8", "9"}));
  while (!my_stack2.empty() && !std_stack.empty()) {
    EXPECT_EQ(my_stack2.top().top(), std_stack.top().top());
    my_stack2.pop();
    std_stack.pop();
  }
  EXPECT_TRUE(my_stack2.empty());
  EXPECT_TRUE(std_stack.empty());
}

TEST(StackExceptionSafety, PushWithCopyException) {
  s21::stack<ThrowOnCopy> my_stack;
  ThrowOnCopy obj(1);
  EXPECT_THROW(my_stack.push(obj), std::runtime_error);
  EXPECT_TRUE(my_stack.empty());
}

TEST(StackExceptionSafety, Initializerlist) {
  EXPECT_THROW(
      { s21::stack<ThrowOnCopy> my_stack{ThrowOnCopy(1)}; },
      std::runtime_error);
}