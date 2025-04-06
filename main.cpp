// #include "s21_array.h"
#include <iostream>
#include <array>

class ThrowOnCopy {
    public:
     int data;
   
     ThrowOnCopy(int d) : data(d) {}
   
     ThrowOnCopy(const ThrowOnCopy&) {
       throw std::runtime_error("Ошибка!");
     }
   };
   int main() {
     std::array<ThrowOnCopy, 2> a = {ThrowOnCopy(1), ThrowOnCopy(2)};
     std::cout << a.size() << '\n';
   }