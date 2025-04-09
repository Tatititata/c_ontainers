<p align="center">
  <img src="logo.png" width="150" alt="lace logo">
</p>

# 🧵 lace_c_ontainers

A set of C++ c_ontainers under the `lace::` namespace. This project was created to better understand the internal structure and logic of standard c_ontainers.

## 📦 Implemented c_ontainers

- `lace::array<T, N>` — static array (similar to `std::array`)
- `lace::queue<T>` — queue based on a doubly linked list (`std::list`) (similar to `std::queue`)
- `lace::map<Key, Value>` — associative c_ontainer using a red-black tree
- `lace::set<Key>` — set implemented with a red-black tree
- `lace::multiset<Key>` — multiset supporting duplicates, also based on a red-black tree

## 🔧 Features

- Custom iterator implementations
- Support for basic and advanced operations: insertion, deletion, search, comparison, and more

## 📁 Project Structure

```
├── src/ 
│    └── unit_tests.h 
│           └── *.cc 
├── lace_array.h 
├── lace_queue.h 
├── lace_map.h 
├── lace_set.h 
├── lace_multiset.h 
├── README.md 
├── README_rus.md 
└── Makefile 
```

## ⚙️ Build Instructions

Make sure you have a C++17+ compatible compiler and `make` installed.

To build and run tests:

```
make test
```

## 🧪 Testing

All c_ontainers are covered by unit tests.

### Run tests

```make test```

## 🧹 Clean up

To remove all generated files:

```make clean```

This will delete all compiled object files, executables, libraries, and distribution archives.

## 💡 Usage Example

```
#include "lace_map.h"
#include <iostream>

int main() {
    lace::map<int, std::string> my_map;
    my_map.insert({1, "one"});
    my_map.insert({2, "two"});

    for (auto it = my_map.begin(); it != my_map.end(); ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    return 0;
}
```

## 🚧 Planned

- Add `lace::vector`
- Add `lace::list`
- Add `lace::stack`
- Add `lace::multimap`
