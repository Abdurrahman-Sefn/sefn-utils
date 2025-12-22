# Sefn Utils (C++ Library)

I built this repository for tasks I found myself doing repeatedly.

**Quick links:** [Trie](#trie) • [InputUtils](#inpututils) • [How to Use](#how-to-use) • [Examples](#examples)

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
Sefn::Trie<std::string> dict;

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
- `erase(const std::string& word)` - Remove a word, returns bool (true if found)
- `traverse(Func fn)` - Run a function on all objects
- `clear()` - Delete all nodes

**Performance:**
- Insert/lookup: O(m) where m is word length
- Auto-complete: O(m + n) where n is result count
- Space: O(N) where N is total characters stored

See [`examples/trie_example.cpp`](examples/trie_example.cpp) for more.

---

## InputUtils

Reads user input from the console with type checking and validation.

**What it does:**
- Parses input into any C++ type (int, double, string, etc.)
- Optional custom validation with lambdas
- Re-prompts on invalid input
- Handles errors gracefully

**Basic usage:**
```cpp
int age = Sefn::readValidatedInput<int>(
    "Enter your age: ",
    0,
    [](const int& val) { return val >= 0 && val <= 150; },
    "Age must be 0-150.\n"
);
```

**Method signature:**
```cpp
template<typename T>
T Sefn::readValidatedInput(
    const std::string& prompt,
    int indentTabs = 0,
    std::function<bool(const T&)> validator = nullptr,
    const std::string& errorMessage = "Invalid value. Please try again.\n",
    const std::string& formatErrorMessage = "Invalid format. Please try again.\n"
)
```

No validator? Just use the first parameter:
```cpp
std::string name = Sefn::readValidatedInput<std::string>("Your name: ");
```

See [`examples/input_validation_example.cpp`](examples/input_validation_example.cpp) for more.

---

## How to Use

### Copy headers
These are header-only. Copy the `include/Sefn.hpp` file and `include/Sefn` folder into your project's include path:

```cpp
// Include everything
#include <Sefn.hpp>

// Or include individual parts
#include <Sefn/Trie.hpp>
#include <Sefn/InputUtils.hpp>
```

### CMake Integration (Recommended)
If you use CMake, you can add this repository as a subdirectory or fetch content:

```cmake
add_subdirectory(sefn-utils)
target_link_libraries(your_app PRIVATE Sefn::Utils)
```

### Build examples
```bash
mkdir build && cd build
cmake ..
make
./trie_example
./input_validation_example
```

Check the [examples](#examples) section below for what each demo does.

---

## Examples

Two example programs demonstrate each library:

- **[`trie_example.cpp`](examples/trie_example.cpp)** - Insert, search, auto-complete, and traversal
- **[`input_validation_example.cpp`](examples/input_validation_example.cpp)** - Read integers, doubles, and strings with validation

Build them with the commands in [How to Use](#how-to-use) above.

## Notes

- You manage the memory of objects stored in Trie (it doesn't own them)
- Both are templates—no separate compilation
- Requires C++17 or later
- Use freely!

```
include/
├── Sefn.hpp               # Master header (includes everything)
└── Sefn/
    ├── Trie.hpp           # The Trie implementation
    └── InputUtils.hpp     # Input validation utility

examples/
├── trie_example.cpp           # [Trie demo](examples/trie_example.cpp)
└── input_validation_example.cpp  # [Input validation demo](examples/input_validation_example.cpp)
```


