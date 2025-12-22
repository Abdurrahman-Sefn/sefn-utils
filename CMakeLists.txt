cmake_minimum_required(VERSION 3.10)
project(cpp_utilities VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only libraries
add_library(cpp_utilities INTERFACE)
target_include_directories(cpp_utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    # Build examples
    add_executable(trie_example examples/trie_example.cpp)
    target_link_libraries(trie_example PRIVATE cpp_utilities)

    add_executable(input_validation_example examples/input_validation_example.cpp)
    target_link_libraries(input_validation_example PRIVATE cpp_utilities)

endif()
