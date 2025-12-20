cmake_minimum_required(VERSION 3.10)
project(cpp_utilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only libraries
add_library(cpp_utilities INTERFACE)
target_include_directories(cpp_utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Example executable (optional)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_executable(example examples/example.cpp)
    target_link_libraries(example PRIVATE cpp_utilities)
endif()
