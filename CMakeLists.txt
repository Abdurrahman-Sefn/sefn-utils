cmake_minimum_required(VERSION 3.10)
project(sefn_utils VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only libraries
add_library(sefn_utils INTERFACE)
target_include_directories(sefn_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create an alias target that matches the namespace style
add_library(Sefn::Utils ALIAS sefn_utils)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    # Build examples
    add_executable(trie_example examples/trie_example.cpp)
    target_link_libraries(trie_example PRIVATE Sefn::Utils)

    add_executable(input_validation_example examples/input_validation_example.cpp)
    target_link_libraries(input_validation_example PRIVATE Sefn::Utils)

endif()
