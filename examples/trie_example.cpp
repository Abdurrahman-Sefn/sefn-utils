#include <iostream>
#include <string>
#include <vector>
#include "../include/Trie.hpp"

int main() {
    Trie<std::string> dictionary;

    // Create some sample data
    auto apple = new std::string("A red fruit");
    auto application = new std::string("A software program");
    auto apply = new std::string("To make a request");
    auto banana = new std::string("A yellow fruit");

    // Insert words
    dictionary.insert(apple, "apple");
    dictionary.insert(application, "application");
    dictionary.insert(apply, "apply");
    dictionary.insert(banana, "banana");

    // Auto-complete example
    std::cout << "Words starting with 'app':\n";
    auto results = dictionary.autoComplete("app");
    
    for (const auto* result : results) {
        std::cout << "  - " << *result << "\n";
    }

    // Exact word search
    std::cout << "\nSearch for 'apple': ";
    if (auto obj = dictionary.wordExists("apple")) {
        std::cout << *obj << "\n";
    } else {
        std::cout << "Not found\n";
    }

    // Prefix check
    std::cout << "Prefix 'ban' exists: " 
              << (dictionary.prefixExists("ban") ? "yes" : "no") << "\n";

    // Cleanup
    delete apple;
    delete application;
    delete apply;
    delete banana;

    return 0;
}
