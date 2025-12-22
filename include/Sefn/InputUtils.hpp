#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <functional>

/**
 * @file Sefn/InputUtils.hpp
 * @brief Console input utilities with validation support.
 */

namespace Sefn {
    
    /**
     * @brief Reads and validates user input from standard input.
     *
     * Prompts the user, reads a line, and parses it into type T.
     * Optionally validates the parsed value with a custom function.
     *
     * @tparam T Data type to read and return.
     * @param prompt Message to display to the user.
     * @param indentTabs Number of tabs to indent prompts and messages. Must be non-negative.
     * @param validator Callable returning true for valid values, false to reject.
     *                  nullptr or empty function skips validation.
     * @param errorMessage Custom message shown when validation fails.
     * @param formatErrorMessage Custom message shown when parsing fails.
     * @return The validated value of type T.
     * 
     * @example
     * ```cpp
     * int age = Sefn::readValidatedInput<int>(
     *     "Enter age: ", 
     *     0, 
     *     [](int a) { return a >= 18; },
     *     "Must be 18+.\n"
     * );
     * ```
     */
    template<typename T>
    T readValidatedInput(const std::string& prompt, int indentTabs = 0,
                        std::function<bool(const T&)> validator = nullptr,
                        const std::string& errorMessage = "Invalid value. Please try again.\n",
                        const std::string& formatErrorMessage = "Invalid format. Please try again.\n") {
        std::string indentStr(indentTabs, '\t');
        std::string promptStr = indentStr + prompt;
        std::string errorIndent = indentStr + '\t';
        
        T value;
        std::string line;
        
        while (true) {
            std::cout << promptStr;
            
            if (!std::getline(std::cin, line)) {
                std::cerr << errorIndent << "Error reading input.\n";
                continue;
            }
            
            std::stringstream ss(line);
            if ((ss >> value) && ss.eof()) {
                if (!validator || validator(value)) {
                    break;
                } else {
                    std::cout << errorIndent << errorMessage;
                }
            } else {
                std::cout << errorIndent << formatErrorMessage;
            }
        }
        return value;
    }
        
} // namespace Sefn
    