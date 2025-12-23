# Changelog

All notable changes to this project will be documented in this file.

## [2.1.1] - 2025-12-23

### Documentation
- **README Structure Overhaul:**
  - Split integration guide into "Getting Started" (Quick Start) and detailed "Usage".
  - Defined 4 distinct integration methods (FetchContent, Manual Copy, Submodule, System-wide) with **Pros/Cons** analysis for each.
  - Added explicit memory management "Best Practices" (Good/Bad examples) for `Trie` to prevent leaks.
  - Added a "Minimal Example" section for quick library verification.
  - Improved cross-linking between sections and files.

## [2.1.0] - 2025-12-23

### Added
- **Installation Support:** Added `install()` rules to `CMakeLists.txt` for system-wide installation.
- **CMake Integration:** Generated `SefnUtilsConfig.cmake` to support `find_package(SefnUtils)` in external projects.
- **Unit Tests:** Added `tests/` directory with a custom lightweight test framework and `TrieTests`.
- **License:** Added `LICENSE` file (MIT License).

### Changed
- **Renaming:** Renamed example source files to PascalCase (`TrieExample.cpp`, `InputValidationExample.cpp`) to match project conventions.

### Documentation
- **README Enhancements:**
  - Clarified that `Trie` acts as a **non-owning index** to improve memory safety awareness.
  - Added "Running Tests" guide for `CTest`.
  - Expanded "Quick Links" to cover all major sections.
  - Added internal clickable links for files (e.g., `Sefn.hpp`, `CMakeLists.txt`) and directories.
  - Refined installation terminology (e.g., "Manual Copy") for better clarity.
  - Included a detailed parameter table for `InputUtils`.
  - Integrated custom technical descriptions into the "Overview" and library sections.

## [2.0.1] - 2025-12-22

### Added
- Master header `include/Sefn.hpp` for including all library components at once.

### Documentation
- Centralized `Sefn` namespace documentation in `Sefn.hpp`.
- Restored missing erase example in `examples/trie_example`.
- Clarified that `Trie::traverse` visits nodes in lexicographic order.
- Added usage note for `indentTabs` (must be non-negative) in `InputUtils.hpp`.
- Updated `README.md` to include the new master header and updated file structure.

## [2.0.0] - 2025-12-22

### Changed
- **Breaking:** Renamed project to `sefn-utils` (GitHub) / `sefn_utils` (CMake).
- **Breaking:** All code is now wrapped in `namespace Sefn`.
- **Breaking:** Header files moved to `include/Sefn/`. Usage: `#include <Sefn/Trie.hpp>`.
- **Breaking:** CMake target is now `Sefn::Utils`.
- Updated documentation and examples to reflect standard usage.

## [1.0.0] - 2025-12-21

### Added
- Initial release with Trie and InputUtils libraries
- Comprehensive documentation and examples

### Changed
- Refactored naming conventions for consistency
- Improved documentation across all headers
- Enhanced README with clearer structure

### Fixed
- Stream error handling in readValidatedInput
- Validator logic for null/empty validators
