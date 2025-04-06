#ifndef UNIT_TESTS_THROW_ON_COPY_H_
#define UNIT_TESTS_THROW_ON_COPY_H_

#include <stdexcept>

class ThrowOnNumberCreated {
 public:
  ThrowOnNumberCreated() {
    if (ShouldItThrow()) {
      throw std::runtime_error("NO MORE");
    }
  }

  ThrowOnNumberCreated(const ThrowOnNumberCreated&) {
    if (ShouldItThrow()) {
      throw std::runtime_error("NO MORE");
    }
  }
  ThrowOnNumberCreated& operator=(const ThrowOnNumberCreated&) {
    if (ShouldItThrow()) {
      throw std::runtime_error("NO MORE");
    }
    return *this;
  }

  // Call this before each test!!!!!!!
  static void Reset(size_t maximum_number_of_objects) {
    GetCurrent() = 0;
    GetMaximum() = maximum_number_of_objects;
  }

 private:
  static bool ShouldItThrow() {
    GetCurrent() += 1;
    return GetCurrent() == GetMaximum();
  }

  static size_t& GetMaximum() {
    static size_t maximum_number_of_objects = 0;
    return maximum_number_of_objects;
  }

  static size_t& GetCurrent() {
    static size_t current_number_of_objects = 0;
    return current_number_of_objects;
  }

 private:
  int data{};
};

#endif  // UNIT_TESTS_THROW_ON_COPY_H_
