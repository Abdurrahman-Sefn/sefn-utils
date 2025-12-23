# Sefn Utils (C++ Library)

I built this repository for C++ tasks I found myself doing repeatedly. It provides a collection of lightweight, header-only utilities.

**Quick links:** [Overview](#overview) • [Installation](#installation) • [Integration](#integration) • [Trie](#trie) • [InputUtils](#inpututils) • [Examples](#building-examples) • [Tests](#running-tests) • [License](#license) • [Files](#directory-structure)

## Overview

This repository represents my C++ utilities and data structures. For now it contains 2 generic files: **Trie** and **InputUtils**.

**Key Features:**
- Header-only (easy integration)
- Zero external dependencies
- Requires C++17 or later

---

## Installation

### Option 1: System-wide Install (CMake)
Recommended for using the library across multiple projects.

```bash
# Clone the repository
git clone https://github.com/your-username/Sefn-Utils.git
cd Sefn-Utils

# Build and install
mkdir build && cd build
cmake ..
sudo make install
```

### Option 2: Manual Copy (Local)
Simply copy the [`include/`](include/) directory content into your project's source tree and add it to your include path.

```cpp
#include <Sefn.hpp> // Includes everything
// or
#include <Sefn/Trie.hpp>
```

---

## Integration

### 1. CMake `find_package` (If installed system-wide)
Add the following to your [`CMakeLists.txt`](CMakeLists.txt):

```cmake
find_package(SefnUtils REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Sefn::Utils)
```

### 2. CMake `add_subdirectory` (If using git submodule)
If you've added this repo as a submodule (e.g., in `external/Sefn-Utils`):

```cmake
add_subdirectory(external/Sefn-Utils)
target_link_libraries(my_app PRIVATE Sefn::Utils)
```

---

## Library Documentation

### Trie

This is a key-to-value data structure that maps from a string key to an object pointer.

**Note:** This Trie acts as a **non-owning index**. It stores pointers to your objects but does *not* manage their memory (lifetime). You must ensure the objects remain valid while they are in the Trie.

- I provided it with CRUD operations and **auto-completion**: you give it a prefix, and it retrieves all object pointers whose keys share this prefix, efficiently **SORTED** based on their key values.
- It can also accept a function as a parameter to apply to object pointers while traversing them.

**Key Methods:**
- `insert(T* obj, const std::string& word)`
- `wordExists(const std::string& word)`
- `autoComplete(const std::string& prefix)`
- `erase(const std::string& word)`
- `traverse(Func fn)`

**Basic usage:**
```cpp
Sefn::Trie<std::string> dict;

dict.insert(new std::string("Hello"), "hello");
dict.insert(new std::string("Help"), "help");

// Returns: [Help, Hello] (sorted)
auto results = dict.autoComplete("hel"); 
```

See [`examples/TrieExample.cpp`](examples/TrieExample.cpp) for a full demo.

### InputUtils

This contains a function that reads from the console, validates the input, and cleans the input buffer—preventing system crashes or infinite loops. It can also accept a function as an optional parameter to validate the input logic.

**Function Signature:**
```cpp
template<typename T>
T readValidatedInput(
    const std::string& prompt,
    int indentTabs = 0,
    std::function<bool(const T&)> validator = nullptr,
    const std::string& errorMessage = "Invalid value...\n",
    const std::string& formatErrorMessage = "Invalid format...\n"
);
```

**Parameters:**
| Parameter | Description | Default |
|-----------|-------------|---------|
| `prompt` | The message displayed to the user. | (Required) |
| `indentTabs` | Number of tabs to indent the prompt. | `0` |
| `validator` | A function/lambda returning `true` for valid input. | `nullptr` |
| `errorMessage` | Shown when the `validator` returns `false`. | "Invalid value..." |
| `formatErrorMessage`| Shown when input type parsing fails (e.g. text for int). | "Invalid format..." |

**Basic usage:**
```cpp
// Read an integer between 0 and 150
int age = Sefn::readValidatedInput<int>(
    "Enter your age: ",
    0, 
    [](const int& val) { return val >= 0 && val <= 150; },
    "Age must be 0-150.\n"
);
```

See [`examples/InputValidationExample.cpp`](examples/InputValidationExample.cpp) for more.

---

## Building Examples

To build and run the included example programs:

```bash
mkdir build && cd build
cmake ..
make

# Run demos
./trie_example
./input_validation_example
```

## Running Tests

This project uses `CTest` for unit testing. To run the test suite:

```bash
cd build
cmake ..
make
ctest --output-on-failure
```

---

## License

- This project is licensed under the MIT License.
- Use freely!
- See the [LICENSE](LICENSE) file for details.

## Directory Structure

```
include/
├── Sefn.hpp               # Master header
└── Sefn/
    ├── Trie.hpp           # Trie implementation
    └── InputUtils.hpp     # Input validation utility

examples/
├── TrieExample.cpp
└── InputValidationExample.cpp
```


