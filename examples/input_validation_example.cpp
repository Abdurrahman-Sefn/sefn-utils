#include <iostream>
#include "../include/InputUtils.hpp"

int main() {
    std::cout << "=== Input Validation Examples ===\n\n";

    // Example 1: Simple integer input
    std::cout << "Example 1: Read an integer\n";
    int number = readValidatedInput<int>("Enter a number: ");
    std::cout << "You entered: " << number << "\n\n";

    // Example 2: Integer with validation (age)
    std::cout << "Example 2: Read age (18-100)\n";
    int age = readValidatedInput<int>(
        "Enter your age: ",
        0,
        [](const int& val) { return val >= 18 && val <= 100; },
        "Age must be between 18 and 100.\n"
    );
    std::cout << "Your age: " << age << "\n\n";

    // Example 3: Double with validation (percentage)
    std::cout << "Example 3: Read percentage (0-100)\n";
    double percentage = readValidatedInput<double>(
        "Enter a percentage: ",
        0,
        [](const double& val) { return val >= 0.0 && val <= 100.0; },
        "Percentage must be between 0 and 100.\n"
    );
    std::cout << "Percentage: " << percentage << "%\n\n";

    // Example 4: String input
    std::cout << "Example 4: Read a name\n";
    std::string name = readValidatedInput<std::string>(
        "Enter your name: ",
        0,
        [](const std::string& val) { return !val.empty() && val.length() <= 50; },
        "Name must be 1-50 characters.\n"
    );
    std::cout << "Hello, " << name << "!\n";

    return 0;
}
