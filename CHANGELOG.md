# Changelog

All notable changes to this project will be documented in this file.

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
