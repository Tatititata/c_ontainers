<p align="center">
  <img src="logo.png" width="150" alt="lace logo">
</p>

# 🧵 lace_c_ontainers

Набор к_онтейнеров C++ с пространством имён `lace::`. Проект создан с целью понимания структуры и логики стандартных к_онтейнеров.

## 📦 Реализованные к_онтейнеры

- `lace::array<T, N>` — статический массив (аналог `std::array`)
- `lace::queue<T>` — очередь на базе двусвязного списка std::list (аналог `std::queue`)
- `lace::map<Key, Value>` — ассоциативный к_онтейнер на основе красно-чёрного дерева
- `lace::set<Key>` — множество, реализованное через красно-чёрное дерево
- `lace::multiset<Key>` — мультимножество с поддержкой дубликатов, также на основе красно-чёрного дерева

## 🔧 Особенности

- Собственная реализация итераторов.
- Поддержка базовых и расширенных операций: вставка, удаление, поиск, сравнение и др.

## 📁 Структура проекта

```
src/ 
├── unit_tests.h/
│       └── *.cc 
├── lace_array.h 
├── lace_queue.h 
├── lace_map.h 
├── lace_set.h 
├── lace_multiset.h 
├── README.md 
├── README_rus.md 
└── Makefile 
```

## 🧪 Тестирование

Все к_онтейнеры покрыты модульными тестами.

### Запуск тестов

```make test```

## 🧹 Очистка проекта

Для удаления сгенерированных файлов:

```make clean```


## 💡  Примеp использования

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

### 🖥️ Вывод

<p align="left">
  <img src="output.png" width="150" alt="tree output">
</p>


## 🚧 В планах

- Добавить `lace::vector`
- Добавить `lace::list`
- Добавить `lace::stack`
- Добавить `lace::multimap`


