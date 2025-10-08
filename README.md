# LiteVector

A minimal C++ implementation of a dynamic array container inspired by `std::vector`, built for learning purposes. `LiteVector` demonstrates manual memory management, placement new, copy/move semantics and basic container behavior.

## Features
- Dynamic memory allocation and reallocation
- Manual memory management using `operator new` and `placement new`
- Support for copy and move semantics
- `push_back`, `reserve`, `size` and `capacity` support
- Templated implementation (`LiteVector<T>`)

## 📚 Motivation

The purpose of this project is to **better understand how `std::vector` works under the hood** by implementing its core behavior from scratch:

- Memory layout and ownership
- Object lifetime and destruction
- Performance implication of copying vs moving
- Real-world usage of `placement new` and `operator delete`

This project serves as a learning excercise in low-level C++ and memory management.


## 🛠️ Build
To build the project using CMake:

``` bash
git clone https://github.com/TheSparrowsky/LiteVector.git
cd LiteVector
mkdir build && cd build
cmake ..
make
./LiteVector
```

## ✅ TODO
- [x] - Implement `emplace_back`
- [x] - Add `operator[]` support
- [x] - Add `begin()` and `end()` support
- [x] - Support `clear()` and `shrink_to_fit()`
- [ ] - Unit tests and benchmarks

# ⚠️  Disclaimer
This is **not** a production-ready replacement for `std::vector`. It is intentionally minimalistic, unsafe, and focused purely on illustrating C++ memory and object management concepts.

