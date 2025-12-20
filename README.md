# C++ Utility Libraries

A collection of header-only C++ libraries for common tasks: fast prefix-based string searching and validated console input.

## Quick Start

These are header-only libraries—no compilation needed. Simply copy the headers into your project and include them:

```cpp
#include "Trie.hpp"
#include "InputUtils.hpp"
```

## Libraries

### Trie: Fast Prefix-Based Search

A generic, efficient Trie (prefix tree) implementation for lexicographically sorted string operations.

**Key Features:**
- O(m) prefix and word lookups (m = string length)
- Automatic lexicographic sorting of results
- Memory-efficient prefix sharing
- Template-based design for any object type

**Quick Example:**
```cpp
Trie<std::string> dictionary;

auto hello = new std::string("Hello, World!");
auto help = new std::string("Ask for help");

dictionary.insert(hello, "hello");
dictionary.insert(help, "help");

auto results = dictionary.autoComplete("hel");  // Returns [help, hello]

// Cleanup (Important!)
delete hello;
delete help;
```

**API:**
- `insert(T* object, const std::string& word)` - Add word with associated object
- `wordExists(const std::string& word)` - Search for exact word
- `prefixExists(const std::string& prefix)` - Check if prefix exists
- `autoComplete(const std::string& prefix)` - Returns vector of all words with prefix (sorted)
- `traverse(Func function)` - Apply function to all objects
- `clear()` - Deallocate all nodes

**Performance:**
- Insert: O(m × log k) where m = word length, k = alphabet size
- Lookup: O(m)
- Auto-complete: O(m + n) where n = matching words
- Space: O(N) where N = total characters in all words

---

### Input Validation: Type-Safe Console Input

A flexible template utility for reading and validating user input from the console.

**Key Features:**
- Type-safe parsing into any C++ type
- Custom validation with lambdas or functions
- Configurable error messages
- Automatic re-prompting on invalid input
- Formatted prompts with indentation support

**Quick Example:**
```cpp
int age = readValidatedInput<int>(
    "Enter your age (18-65): ",
    0,  // No indentation
    [](const int& val) { return val >= 18 && val <= 65; },
    "Invalid age. Please try again.\n"
);
```

**API:**
```cpp
template<typename T>
T readValidatedInput(
    const std::string& prompt,                                  // Message to display
    int indentTabs = 0,                                         // Tab indentation count
    std::function<bool(const T&)> validator = nullptr,          // Custom validation function
    const std::string& errorMessage = "...", 
    const std::string& formatErrorMessage = "..."
)
```

**Error Handling:**
- Validates parsing success
- Optionally validates parsed value
- Handles input stream errors gracefully
- Customizable error messages for each failure type

---

## Integration

### Basic Integration
```cpp
#include "Trie.hpp"
#include "InputUtils.hpp"

int main() {
    // Use Trie
    Trie<int> trie;
    
    // Use input validation
    std::string name = readValidatedInput<std::string>(
        "Enter your name: "
    );
    
    return 0;
}
```

## Building Examples

Examples are provided to demonstrate usage:

```bash
mkdir build
cd build
cmake ..
make

# Run examples
./trie_example
./input_validation_example
```

---

## Notes

- Both libraries are header-only and have no external dependencies
- Requires C++17 or later
- The Trie stores pointers to your objects—you manage their memory
- Templates are fully specialized at compile time with no runtime overhead

## File Structure

```
.
├── include/
│   ├── Trie.hpp              # Prefix tree for fast string searching
│   └── InputUtils.hpp        # Validated input from console
├── examples/
│   ├── trie_example.cpp      # Trie usage demonstration
│   └── input_validation_example.cpp  # Input validation examples
├── README.md
├── LICENSE
├── CHANGELOG.md
├── CONTRIBUTING.md
└── CMakeLists.txt
```

---

## License

MIT License - see LICENSE file for details.

