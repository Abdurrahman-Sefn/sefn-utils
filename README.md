# C++ Utility Libraries

Two repo I built for tasks I found myself doing repeatedly.

## Overview

- **Trie**: A fast, generic prefix tree for auto-complete and prefix-based operations
- **InputUtils**: Type-safe console input with custom validation

Both are header-only, require C++17, and have zero external dependencies.

## Trie

A prefix tree implementation useful for auto-complete, spell-checking, and any prefix-based search.

**What it does:**
- Fast O(m) lookups where m is the string length
- Auto-complete with automatic lexicographic sorting
- Generic—works with any pointer type
- Memory-efficient through prefix sharing

**Basic usage:**
```cpp
Trie<std::string> dict;

auto hello = new std::string("Hello, World!");
auto help = new std::string("Ask for help");

dict.insert(hello, "hello");
dict.insert(help, "help");

auto results = dict.autoComplete("hel");  // [help, hello] - sorted

delete hello;
delete help;
```

**Methods:**
- `insert(T* obj, const std::string& word)` - Add a word
- `wordExists(const std::string& word)` - Find exact match
- `prefixExists(const std::string& prefix)` - Check if prefix exists
- `autoComplete(const std::string& prefix)` - Get all matches (sorted)
- `traverse(Func fn)` - Run a function on all objects
- `clear()` - Delete all nodes

**Performance:**
- Insert/lookup: O(m) where m is word length
- Auto-complete: O(m + n) where n is result count
- Space: O(N) where N is total characters stored

See `examples/trie_example.cpp` for more.

## InputUtils

Reads user input from the console with type checking and validation.

**What it does:**
- Parses input into any C++ type (int, double, string, etc.)
- Optional custom validation with lambdas
- Re-prompts on invalid input
- Handles errors gracefully

**Basic usage:**
```cpp
int age = readValidatedInput<int>(
    "Enter your age: ",
    0,
    [](const int& val) { return val >= 0 && val <= 150; },
    "Age must be 0-150.\n"
);
```

**Method signature:**
```cpp
template<typename T, typename Validator>
T readValidatedInput(
    const std::string& prompt,
    int indentTabs = 0,
    Validator validator = nullptr,
    const std::string& errorMessage = "Invalid value. Please try again.\n",
    const std::string& formatErrorMessage = "Invalid format. Please try again.\n"
)
```

No validator? Just use the first parameter:
```cpp
std::string name = readValidatedInput<std::string>("Your name: ");
```

See `examples/input_validation_example.cpp` for more.

## How to Use

### Copy headers
These are header-only. Just copy `Trie.hpp` and `InputUtils.hpp` into your project:

```cpp
#include "Trie.hpp"
#include "InputUtils.hpp"
```

### Build examples
```bash
mkdir build && cd build
cmake ..
make
./trie_example
./input_validation_example
```

## Notes

- You manage the memory of objects stored in Trie (it doesn't own them)
- Both are templates—no separate compilation
- Requires C++17 or later
- MIT licensed, use freely

## Files

```
include/
├── Trie.hpp           # The Trie implementation
└── InputUtils.hpp     # Input validation utility

examples/
├── trie_example.cpp           # Trie demo
└── input_validation_example.cpp  # Input validation demo
```

---

MIT License. See LICENSE for details.


