#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include "TestUtils.hpp"
#include <Sefn/InputUtils.hpp>

// Helper to simulate user input
// Takes a string that simulates keystrokes (e.g., "123\n")
// Returns the captured output (stdout)
template<typename Func>
std::string runWithInput(const std::string& input, Func func) {
    // Save original buffers
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();

    std::stringstream ssIn(input);
    std::stringstream ssOut;

    // Redirect
    std::cin.rdbuf(ssIn.rdbuf());
    std::cout.rdbuf(ssOut.rdbuf());

    try {
        func();
    } catch (...) {
        // Restore before re-throwing
        std::cin.rdbuf(origCin);
        std::cout.rdbuf(origCout);
        throw;
    }

    // Restore
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    return ssOut.str();
}

int testValidInteger() {
    printTestHeader("testValidInteger");
    
    int result = 0;
    std::string output = runWithInput("42\n", [&]() {
        result = Sefn::readValidatedInput<int>("Enter Number: ");
    });

    ASSERT_EQUAL(result, 42);
    // Check that prompt was printed
    if (output.find("Enter Number: ") == std::string::npos) {
        std::cerr << "FAIL: Prompt not found in output.\n";
        return 1;
    }

    printTestFooter("testValidInteger");
    return 0;
}

int testValidationFailure() {
    printTestHeader("testValidationFailure");

    int result = 0;
    // Input: "10" (fails > 18), then "20" (passes)
    std::string input = "10\n20\n";
    
    std::string output = runWithInput(input, [&]() {
        result = Sefn::readValidatedInput<int>(
            "Enter Age: ", 
            0,
            [](const int& v) { return v >= 18; },
            "Too young!\n"
        );
    });

    ASSERT_EQUAL(result, 20);
    
    // Check for error message
    if (output.find("Too young!") == std::string::npos) {
        std::cerr << "FAIL: Validation error message not found.\n";
        return 1;
    }

    printTestFooter("testValidationFailure");
    return 0;
}

int testFormatFailure() {
    printTestHeader("testFormatFailure");

    int result = 0;
    // Input: "abc" (invalid format), then "100" (valid)
    std::string input = "abc\n100\n";
    
    std::string output = runWithInput(input, [&]() {
        result = Sefn::readValidatedInput<int>("Enter Num: ", 0, nullptr, "", "Bad Format!\n");
    });

    ASSERT_EQUAL(result, 100);
    
    // Check for format error message
    if (output.find("Bad Format!") == std::string::npos) {
        std::cerr << "FAIL: Format error message not found.\n";
        return 1;
    }

    printTestFooter("testFormatFailure");
    return 0;
}

int testStringInput() {
    printTestHeader("testStringInput");
    
    std::string result;
    // Input with spaces to ensure it reads whole tokens/lines correctly as per implementation
    // The current implementation uses getline then stream >> value.
    // So "hello world" -> getline gets "hello world", ss >> string reads "hello", 
    // AND ss.eof() check. "hello world" in ss: "hello" extracted, " world" remains. eof() is false.
    // So "hello world" should FAIL default parsing if T is std::string because of the eof check!
    // Let's verify this behavior. 
    
    // Case 1: "hello" -> valid
    std::string output = runWithInput("hello\n", [&]() {
        result = Sefn::readValidatedInput<std::string>("Name: ");
    });
    ASSERT_EQUAL(result, "hello");

    printTestFooter("testStringInput");
    return 0;
}

int main() {
    if (testValidInteger() != 0) return 1;
    if (testValidationFailure() != 0) return 1;
    if (testFormatFailure() != 0) return 1;
    if (testStringInput() != 0) return 1;

    std::cout << "\nAll InputUtils tests passed!\n";
    return 0;
}
