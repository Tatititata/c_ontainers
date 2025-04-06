#ifndef UNIT_TESTS_THROW_ON_COPY_H_
#define UNIT_TESTS_THROW_ON_COPY_H_

#include <initializer_list>
#include <stdexcept>

class ThrowOnCopy {
 public:
  ThrowOnCopy(int d) : data(d) {}

  ThrowOnCopy(const ThrowOnCopy&) { throw std::runtime_error("Ошибка!"); }
  ThrowOnCopy& operator=(const ThrowOnCopy&) {
    throw std::runtime_error("Ошибка!");
    return *this;
  }

  ThrowOnCopy(std::initializer_list<int>) {
    throw std::runtime_error("Ошибка!");
  }

 private:
  int data;
};

#endif  // UNIT_TESTS_THROW_ON_COPY_H_
