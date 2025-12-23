cmake_minimum_required(VERSION 3.10)
project(sefn_utils VERSION 2.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only libraries
add_library(sefn_utils INTERFACE)
target_include_directories(sefn_utils INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Create an alias target that matches the namespace style
add_library(Sefn::Utils ALIAS sefn_utils)

include(GNUInstallDirs)

# Installation rules
install(TARGETS sefn_utils
    EXPORT SefnUtilsTargets
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT SefnUtilsTargets
    FILE SefnUtilsTargets.cmake
    NAMESPACE Sefn::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SefnUtils
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/SefnUtilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SefnUtilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SefnUtils
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    # Build examples
    add_executable(trie_example examples/TrieExample.cpp)
    target_link_libraries(trie_example PRIVATE Sefn::Utils)

    add_executable(input_validation_example examples/InputValidationExample.cpp)
    target_link_libraries(input_validation_example PRIVATE Sefn::Utils)

    # Unit Tests
    enable_testing()
    
    add_executable(trie_tests tests/TrieTests.cpp)
    target_link_libraries(trie_tests PRIVATE Sefn::Utils)
    
    add_test(NAME TrieTests COMMAND trie_tests)

endif()
