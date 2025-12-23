#pragma once

#include <iostream>
#include <string>
#include <vector>

// Simple macro to assert conditions and report failures
#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << #condition << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            return 1; \
        } \
    } while (0)

#define ASSERT_EQUAL(a, b) \
    do { \
        if ((a) != (b)) { \
            std::cerr << "FAIL: " << #a << " != " << #b << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            std::cerr << "      Expected: " << (b) << ", Got: " << (a) << std::endl; \
            return 1; \
        } \
    } while (0)

void printTestHeader(const std::string& name) {
    std::cout << "[Running] " << name << "..." << std::endl;
}

void printTestFooter(const std::string& name) {
    std::cout << "[PASSED]  " << name << std::endl;
}


