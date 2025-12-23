# Sefn Utils (C++ Library)

I built this repository for C++ tasks I found myself doing repeatedly. It provides a collection of lightweight, header-only utilities.

**Quick links:** [Overview](#overview) • [Getting Started](#getting-started) • [Usage](#usage) • [Trie](#trie) • [InputUtils](#inpututils) • [Examples](#building-examples) • [Tests](#running-tests) • [Contributing](#contributing) • [License](#license)

## Overview

This repository represents my C++ utilities and data structures. For now it contains 2 generic files: **[Trie](include/Sefn/Trie.hpp)** and **[InputUtils](include/Sefn/InputUtils.hpp)**.

**Key Features:**
- Header-only (easy integration)
- Zero external dependencies
- Requires C++17 or later

**What's included:**
- 📁 [**Master header**](include/Sefn.hpp) - Include everything at once
- 🌲 [**Trie**](include/Sefn/Trie.hpp) - Autocomplete-ready prefix tree
- ⌨️ [**InputUtils**](include/Sefn/InputUtils.hpp) - Validated console input
- 📚 [**Examples**](examples/) - Working demonstrations
- ✅ [**Tests**](tests/) - Unit test suite

---

## Getting Started

### Quick Start (Try It First)

The easiest way to see this library in action:

```bash
# Clone and build the examples
git clone https://github.com/Abdurrahman-Sefn/sefn-utils.git
cd sefn-utils
mkdir build && cd build
cmake ..
make

# Run the demos
./trie_example
./input_validation_example
```

If the examples run successfully, you're ready to integrate into your own project!

---

## Usage

This is a header-only library. Choose the integration method that fits your workflow:

### Method 1: CMake FetchContent (Recommended)
**Best for:** Modern CMake projects (CMake 3.14+), automatic updates, CI/CD pipelines

**Your CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.14)
project(MyProject)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    SefnUtils
    GIT_REPOSITORY https://github.com/Abdurrahman-Sefn/sefn-utils.git
    GIT_TAG main  # or use a specific version tag like v2.0.0
)

FetchContent_MakeAvailable(SefnUtils)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Sefn::Utils)
```

**In your code:**
```cpp
#include <Sefn.hpp>  // Includes everything
// or
#include <Sefn/Trie.hpp>
#include <Sefn/InputUtils.hpp>
```

**Build:**
```bash
mkdir build && cd build
cmake ..  # Automatically downloads the library
make
```

**Pros:** No manual downloads, easy version updates, CMake-native, works great with CI/CD  
**Cons:** Requires CMake 3.14+, needs internet on first configure

**To update to latest version:** Just re-run `cmake ..` or change `GIT_TAG` to a specific version

---

### Method 2: Manual Copy (Simplest)
**Best for:** Small projects, learning, no CMake, quick prototyping

Copy the [`include/`](include/) directory into your project:

```bash
# From your project directory
cp -r /path/to/sefn-utils/include/Sefn /path/to/your-project/include/
cp /path/to/sefn-utils/include/Sefn.hpp /path/to/your-project/include/
```

**Your CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(my_app main.cpp)
```

**Or compile directly:**
```bash
g++ -std=c++17 -I./include main.cpp -o my_app
```

**In your code:**
```cpp
#include "Sefn.hpp"  // Use quotes for local headers
// or
#include "Sefn/Trie.hpp"
```

**Pros:** No dependencies, portable, works anywhere  
**Cons:** Manual updates, one copy per project

---

### Method 3: Git Submodule
**Best for:** Explicit version control, working offline, examining library source

```bash
# Add as submodule in your project
cd your-project
git submodule add https://github.com/Abdurrahman-Sefn/sefn-utils.git external/sefn-utils
git submodule update --init --recursive
```

**Your CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)
set(CMAKE_CXX_STANDARD 17)

# Add Sefn-Utils
add_subdirectory(external/sefn-utils)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Sefn::Utils)
```

**In your code:**
```cpp
#include <Sefn.hpp>
```

**Update the library:**
```bash
git submodule update --remote external/sefn-utils
git add external/sefn-utils
git commit -m "Update sefn-utils"
```

**Pros:** Explicit version tracking, works offline after initial clone, can examine source  
**Cons:** Extra git commands, committed to your repo

---

### Method 4: System-Wide Install (Advanced)
**Best for:** Using across multiple projects, system-level development

```bash
cd sefn-utils
mkdir build && cd build
cmake ..
sudo make install
```

This installs to `/usr/local/` by default.

**Verify installation:**
```bash
ls /usr/local/include/Sefn/  # Should show: Trie.hpp, InputUtils.hpp
```

**Your CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)
set(CMAKE_CXX_STANDARD 17)

find_package(SefnUtils REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Sefn::Utils)
```

**In your code:**
```cpp
#include <Sefn.hpp>
```

**To uninstall:**
```bash
# Manually remove installed files
sudo rm -rf /usr/local/include/Sefn
sudo rm /usr/local/include/Sefn.hpp
sudo rm -rf /usr/local/lib/cmake/SefnUtils
```

**Pros:** One installation for all projects, clean project structure  
**Cons:** Requires admin rights, affects system state, harder to have multiple versions

---

## Minimal Example

Once integrated, test with this minimal program:

**main.cpp:**
```cpp
#include <Sefn.hpp>
#include <iostream>

int main() {
    Sefn::Trie<std::string> dict;
    
    // Create strings that will outlive the Trie
    std::string hello = "Hello";
    std::string help = "Help";
    
    // Trie stores pointers, doesn't own the objects
    dict.insert(&hello, "hello");
    dict.insert(&help, "help");
    
    auto results = dict.autoComplete("hel");
    
    std::cout << "Found " << results.size() << " matches:\n";
    for (auto* str : results) {
        std::cout << "  - " << *str << "\n";
    }
    
    return 0;
    // Strings are automatically cleaned up here
}
```

**Expected output:**
```
Found 2 matches:
  - Help
  - Hello
```

---

## Library Documentation

### Trie

**Header:** [`include/Sefn/Trie.hpp`](include/Sefn/Trie.hpp)

This is a key-to-value data structure that maps from a string key to an object pointer.

**⚠️ Important:** This Trie acts as a **non-owning index**. It stores pointers to your objects but does *not* manage their memory (lifetime). You must ensure the objects remain valid while they are in the Trie.

**Memory Management Best Practices:**

```cpp
// ✅ GOOD: Stack-allocated objects
std::string word = "hello";
trie.insert(&word, "hello");
// word is automatically cleaned up when it goes out of scope

// ✅ GOOD: Manually managed heap objects
auto* word = new std::string("hello");
trie.insert(word, "hello");
// ... use trie ...
trie.erase("hello");  // Remove from trie first
delete word;          // Then delete the object

// ❌ BAD: Memory leak
trie.insert(new std::string("hello"), "hello");
// The pointer is lost! Memory is never freed.
```

**Features:**
- CRUD operations (insert, erase, wordExists)
- **Auto-completion**: Give it a prefix, get all matching objects **SORTED** by their keys
- **Traversal**: Apply functions to all stored object pointers

**Key Methods:**
- `insert(T* obj, const std::string& word)` - Add an object with a key
- `wordExists(const std::string& word)` - Check if a key exists
- `autoComplete(const std::string& prefix)` - Get all objects with keys starting with prefix (sorted)
- `erase(const std::string& word)` - Remove a key (doesn't delete the object)
- `traverse(Func fn)` - Apply a function to all stored objects

**Basic usage:**
```cpp
Sefn::Trie<std::string> dict;

std::string hello = "Hello";
std::string help = "Help";

dict.insert(&hello, "hello");
dict.insert(&help, "help");

// Returns: [&help, &hello] (sorted by key)
auto results = dict.autoComplete("hel"); 

for (auto* str : results) {
    std::cout << *str << "\n";  // Prints: Help, Hello
}
```

**Learn more:**
- 📖 [Full example](examples/TrieExample.cpp)
- ✅ [Test suite](tests/TrieTests.cpp)
- 💻 [Source code](include/Sefn/Trie.hpp)

---

### InputUtils

**Header:** [`include/Sefn/InputUtils.hpp`](include/Sefn/InputUtils.hpp)

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
#include <Sefn/InputUtils.hpp>

// Read an integer between 0 and 150
int age = Sefn::readValidatedInput<int>(
    "Enter your age: ",
    0, 
    [](const int& val) { return val >= 0 && val <= 150; },
    "Age must be between 0 and 150.\n"
);

// Read a non-empty string
std::string name = Sefn::readValidatedInput<std::string>(
    "Enter your name: ",
    0,
    [](const std::string& s) { return !s.empty(); },
    "Name cannot be empty.\n"
);
```

**How it handles errors:**
- **Format errors** (e.g., entering "abc" when expecting an integer): Clears input buffer, shows `formatErrorMessage`, prompts again
- **Validation errors** (e.g., age = 200): Shows `errorMessage`, prompts again
- **No infinite loops**: Properly clears `cin` error state and buffer

**Learn more:**
- 📖 [Full example](examples/InputValidationExample.cpp)
- 💻 [Source code](include/Sefn/InputUtils.hpp)

---

## Building Examples

To build and run the included example programs:

```bash
cd sefn-utils
mkdir build && cd build
cmake ..
make

# Run demos
./trie_example          # See examples/TrieExample.cpp
./input_validation_example  # See examples/InputValidationExample.cpp
```

**Available examples:**
- [`examples/TrieExample.cpp`](examples/TrieExample.cpp) - Demonstrates Trie autocomplete functionality
- [`examples/InputValidationExample.cpp`](examples/InputValidationExample.cpp) - Shows various input validation scenarios

---

## Running Tests

This project uses `CTest` for unit testing. To run the test suite:

```bash
cd build
cmake ..
make
ctest --output-on-failure
```

**Test files:**
- [`tests/TrieTests.cpp`](tests/TrieTests.cpp) - Comprehensive Trie tests
- [`tests/TestUtils.hpp`](tests/TestUtils.hpp) - Testing utilities

---

## Contributing

Contributions are welcome! Here's how you can help:

- 🐛 [Report bugs](https://github.com/Abdurrahman-Sefn/sefn-utils/issues/new)
- 💡 [Suggest features](https://github.com/Abdurrahman-Sefn/sefn-utils/issues/new)
- 🔧 Submit pull requests

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for detailed guidelines on:
- Code style and conventions
- How to submit changes
- Testing requirements
- Documentation standards

---

## License

This project is licensed under the MIT License. Use freely!

See the [LICENSE](LICENSE) file for full terms.

**TL;DR:** You can use, modify, and distribute this library freely, even for commercial purposes.

---

## Directory Structure

```
.
├── CMakeLists.txt           # Build configuration
├── README.md                # This file
├── LICENSE                  # MIT License
├── CHANGELOG.md             # Version history
├── CONTRIBUTING.md          # Contribution guidelines
├── include/
│   ├── Sefn.hpp            # Master header (includes all utilities)
│   └── Sefn/
│       ├── Trie.hpp        # Trie implementation
│       └── InputUtils.hpp  # Input validation utility
├── examples/
│   ├── TrieExample.cpp     # Trie usage demo
│   └── InputValidationExample.cpp  # Input validation demo
└── tests/
    ├── TestUtils.hpp       # Testing utilities
    └── TrieTests.cpp       # Trie unit tests
```

**Key files:**
- Start here: [`include/Sefn.hpp`](include/Sefn.hpp)
- Implementation: [`include/Sefn/`](include/Sefn/)
- Learn by example: [`examples/`](examples/)
- Build system: [`CMakeLists.txt`](CMakeLists.txt)

---

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history and updates.

---

## Support

- 📖 Read the docs above
- 💬 [Ask questions](https://github.com/Abdurrahman-Sefn/sefn-utils/discussions)
- 🐛 [Report issues](https://github.com/Abdurrahman-Sefn/sefn-utils/issues)
- ⭐ Star the repo if you find it useful!

---

**Made with ❤️ for the C++ community**