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
  lace::map<int, int> tree = {
      {5, 0}, {-1, 0}, {6, 0}, {10, 0}, {11, 0},
  };

  tree.draw();

  tree.erase(5);
  tree.draw();

  return 0;
}
```
### 🖥️ Output

```
        5        
     ------     
    /      \    
   -1      10   
           --   
          /  \  
         6   11 
                

       6        
     ------     
    /      \    
   -1      10   
            -   
             \  
             11 
```

## 🚧 Planned

- Add `lace::vector`
- Add `lace::list`
- Add `lace::stack`
- Add `lace::multimap`
