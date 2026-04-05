# bitset

A lightweight, dynamically resizing bitset implementation in C++.

## Description

This project provides a custom `bitset` class that efficiently stores and manipulates individual bits using an underlying array of `uint64_t` blocks. Unlike `std::bitset`, which requires a compile-time size, this implementation dynamically resizes as needed, making it suitable for scenarios where the number of bits is unknown or grows at runtime.

Key features include:
- **Dynamic Capacity**: Automatically expands storage when setting bits beyond the current limit.
- **Efficient Bitwise Operations**: Leverages 64-bit blocks for fast union, intersection, and subset checks.
- **Full Value Semantics**: Implements copy/move constructors and assignment using the copy-and-swap idiom for exception safety and clean resource management.
- **Zero Dependencies**: Built entirely with standard C++ (`<cstdint>`, `<algorithm>`, `<cstring>`).

## Installation & Build

This project is a standalone C++ library with a built-in test suite. No external package managers or complex build systems are required.

### Prerequisites
- A C++11 (or newer) compatible compiler (GCC/MinGW, Clang, or MSVC)
- [Optional] Visual Studio Code with the C/C++ extension

### Build Instructions

**Using Visual Studio Code:**
1. Open the project folder in VS Code.
2. Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on macOS) to trigger the default build task.
3. The executable `test.exe` will be generated in the project directory.

**Using Command Line:**
```bash
g++ -std=c++11 -O2 -Wall bitset.cpp test.cpp -o test
```

## Usage

Include `bitset.h` in your source files and instantiate the `bitset` class. Below are common usage patterns:

### Basic Operations
```cpp
#include "bitset.h"
#include <iostream>

int main() {
    bitset bs; // Starts with 0 capacity, resizes automatically on first set()

    bs.set(10, true);  // Set bit at index 10
    bs.set(5, true);   // Set bit at index 5
    bs.set(10, false); // Clear bit at index 10

    std::cout << "Bit 5 is set: " << bs.test(5) << "\n";
    std::cout << "Bit 10 is set: " << bs.test(10) << "\n";
    std::cout << "Allocated capacity: " << bs.size() << "\n";
    std::cout << "Is empty: " << bs.empty() << "\n";

    return 0;
}
```

### Set Operations
The class supports union (`+`), intersection (`*`), and subset checking (`is_subnet`):
```cpp
bitset a, b;
a.set(1, true); a.set(3, true);
b.set(3, true); b.set(5, true);

bitset uni = a + b;      // Union: {1, 3, 5}
bitset inter = a * b;    // Intersection: {3}

// Subset check: returns true if all set bits in 'this' are also set in 'other'
bool is_sub = inter.is_subnet(a); // true
```

### Memory Management & Copying
The class handles memory automatically and supports standard C++ value semantics:
```cpp
bitset original;
original.set(100, true);

bitset copy = original;          // Deep copy
bitset moved = std::move(original); // Move semantics (original is now empty)
```

## Testing

The repository includes a comprehensive test suite in `test.cpp`. After building, run the executable to verify functionality:

```bash
./test.exe   # Windows
./test       # Linux/macOS
```

Expected output:
```
All tests passed successfully!
```

## API Reference

| Method | Description |
|--------|-------------|
| `bitset()` / `bitset(size_t)` | Default constructor or constructor with initial capacity |
| `~bitset()` | Destructor (releases allocated memory) |
| `set(int index, bool val)` | Sets or clears a bit at `index` |
| `test(int index)` | Returns `true` if the bit at `index` is set |
| `size() const` | Returns the current allocated capacity in bits |
| `empty()` | Returns `true` if no bits are currently set |
| `clear()` | Resets all bits to `0` |
| `operator+(const bitset&)` | Returns a new bitset representing the union |
| `operator*(const bitset&)` | Returns a new bitset representing the intersection |
| `is_subnet(const bitset&)` | Returns `true` if `this` is a subset of the argument |

## Notes
- Indexing is 0-based.
- `size()` returns the **allocated capacity**, not the logical number of set bits or the highest index.
- The `is_subnet` method checks if the calling object is a subset of the passed bitset.
- Designed for single-threaded use. External synchronization is required for concurrent access.