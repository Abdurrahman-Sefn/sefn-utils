#include "TestUtils.hpp"
#include <Sefn/Trie.hpp>
#include <string>

int testInsertAndFind() {
    printTestHeader("Insert and Find");
    Sefn::Trie<int> trie;
    int a = 10, b = 20;

    trie.insert(&a, "apple");
    trie.insert(&b, "app");

    ASSERT_TRUE(trie.wordExists("apple") != nullptr);
    ASSERT_TRUE(*trie.wordExists("apple") == 10);
    
    ASSERT_TRUE(trie.wordExists("app") != nullptr);
    ASSERT_TRUE(*trie.wordExists("app") == 20);

    ASSERT_TRUE(trie.wordExists("banana") == nullptr);
    
    printTestFooter("Insert and Find");
    return 0;
}

int testPrefixExists() {
    printTestHeader("Prefix Exists");
    Sefn::Trie<int> trie;
    int a = 1;
    trie.insert(&a, "hello");

    ASSERT_TRUE(trie.prefixExists("he"));
    ASSERT_TRUE(trie.prefixExists("hell"));
    ASSERT_TRUE(trie.prefixExists("hello"));
    ASSERT_TRUE(!trie.prefixExists("helloo"));
    ASSERT_TRUE(!trie.prefixExists("ha"));

    printTestFooter("Prefix Exists");
    return 0;
}

int testAutoComplete() {
    printTestHeader("Auto Complete");
    Sefn::Trie<std::string> trie;
    
    // Use static strings for simplicity in test (no delete needed)
    std::string s1 = "car";
    std::string s2 = "cat";
    std::string s3 = "cart";
    std::string s4 = "dog";

    trie.insert(&s1, "car");
    trie.insert(&s2, "cat");
    trie.insert(&s3, "cart");
    trie.insert(&s4, "dog");

    auto results = trie.autoComplete("ca");
    
    // Expect: car, cart, cat (lexicographic order depends on implementation, 
    // but usually DFS on children map results in sorted output if map is ordered)
    
    ASSERT_EQUAL(results.size(), 3);
    
    // Verify contents (order: car -> cart -> cat)
    // 'r' < 't', so car comes before cat. 
    // children map sorts keys: 'r', 't'.
    // Under 'r': end of word "car", child 't' -> "cart"
    
    ASSERT_EQUAL(*results[0], "car");
    ASSERT_EQUAL(*results[1], "cart");
    ASSERT_EQUAL(*results[2], "cat");

    printTestFooter("Auto Complete");
    return 0;
}

int testErase() {
    printTestHeader("Erase");
    Sefn::Trie<int> trie;
    int val = 100;
    
    trie.insert(&val, "test");
    ASSERT_TRUE(trie.wordExists("test"));

    // Erase existing
    ASSERT_TRUE(trie.erase("test"));
    ASSERT_TRUE(trie.wordExists("test") == nullptr);

    // Erase non-existing
    ASSERT_TRUE(!trie.erase("test"));
    ASSERT_TRUE(!trie.erase("other"));

    printTestFooter("Erase");
    return 0;
}

int main() {
    if (testInsertAndFind() != 0) return 1;
    if (testPrefixExists() != 0) return 1;
    if (testAutoComplete() != 0) return 1;
    if (testErase() != 0) return 1;
    
    std::cout << "\nAll Trie tests passed!\n";
    return 0;
}
