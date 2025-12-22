#pragma once

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

/**
 * @file Trie.hpp
 * @brief Generic Trie data structure for prefix-based operations.
 */

namespace Sefn {
    
    /**
     * @details
     * Efficient for:
     * - Prefix searches: O(m) where m is prefix length
     * - Auto-completion: Fast retrieval of all words with a given prefix
     * - Word lookups: O(m) where m is word length
     * - Memory efficiency: Shares common prefixes among words
     * - Lexicographic ordering: Results are naturally sorted
     *
     * @tparam T Type of object to associate with each word.
     *
     * @note
     * - Does not take ownership of T* pointers; user is responsible for memory management.
     * - Uses std::map<char, Trie*> for efficient navigation.
     *
     * @example
     * ```cpp
     * Trie<std::string> dict;
     * auto hello = new std::string("Hello");
     * auto help = new std::string("Help");
     *
     * dict.insert(hello, "hello");
     * dict.insert(help, "help");
     *
     * if (auto obj = dict.wordExists("hello")) {
     *     std::cout << "Found: " << *obj << std::endl;
     * }
     *
     * auto results = dict.autoComplete("hel");  // Returns sorted results
     * for (auto* obj : results) {
     *     std::cout << *obj << "\n";
     * }
     *
     * // Remove a word
     * if (dict.erase("hello")) {
     *     std::cout << "Removed 'hello'\n";
     * }
     * 
     * delete hello;
     * delete help;
     * ```
     */
    template<class T>
    class Trie {
    private:
        /**
         * @brief Pointer to the object associated with this node if it represents a complete word.
         * @details nullptr if this node is not an end-of-word marker.
         */
        T* object = nullptr;

        /**
         * @brief Map of child nodes, keyed by character.
         */
        std::map<char, Trie*> children;

        /**
         * @brief Locates the node for a given prefix.
         * @param prefix String to search for.
         * @return Const pointer to the node, or nullptr if not found.
         */
        const Trie* find(const std::string &prefix) const {
            const Trie* current = this;
            for (char ch : prefix) {
                auto it = current->children.find(ch);
                if (it == current->children.cend()) {
                    return nullptr;
                }
                current = it->second;
            }
            return current;
        }

        /**
         * @brief Non-const overload of find().
         */
        Trie* find(const std::string &prefix) {
            return const_cast<Trie*>(static_cast<const Trie*>(this)->find(prefix));
        }

        /**
         * @brief Collects all objects in this subtree.
         */
        void getAllObjects(std::vector<T*> &results) const {
            this->traverseRecursive([&results](T* obj) {
                results.push_back(obj);
            });
        }

        /**
         * @brief Applies a function to each object in the subtree.
         * @tparam Func Callable type.
         * @param function Called with each T* object.
         */
        template<typename Func>
        void traverseRecursive(Func function) const {
            if (object) {
                function(object);
            }
            for (auto const& [key, child] : children) {
                child->traverseRecursive(function);
            }
        }

        /**
         * @brief Removes a word from the Trie (internal recursive helper).
         * @param word Word to remove.
         * @param index Current character index in the word.
         * @return True if this node and its subtree can be deleted, false otherwise.
         */
        bool removeRecursive(const std::string &word, int index = 0) {
            if (index == word.size()) {
                // Reached end of word - clear the marker
                if (!object) {
                    return false; // Word doesn't exist
                }
                object = nullptr;
                // Return true if this node has no children (can be deleted)
                return children.empty();
            }

            char ch = word[index];
            auto it = children.find(ch);
            if (it == children.end()) {
                return false; // Character doesn't exist, word not in Trie
            }

            Trie* child = it->second;
            bool canDeleteChild = child->removeRecursive(word, index + 1);

            // If child can be deleted, remove it
            if (canDeleteChild) {
                delete child;
                children.erase(it);
                // Return true if this node has no object and no children
                return object == nullptr && children.empty();
            }

            return false;
        }
    public:
        /**
         * @brief Default constructor.
         */
        Trie() = default;

        /**
         * @brief Copy constructor is deleted to prevent shallow copies and double frees.
         */
        Trie(const Trie &) = delete;

        /**
         * @brief Copy assignment operator is deleted to prevent shallow copies.
         */
        Trie &operator=(const Trie&) = delete;

        /**
         * @brief Destructor. Frees the memory allocated for child nodes.
         * @note This does NOT deallocate the `T* object` pointers.
         */
        ~Trie() {
            clear();
        }

        /**
         * @brief Inserts a word with an associated object.
         * @param object Pointer to associate with the word (not owned by Trie).
         * @param word String to insert.
         * @note Overwrites the object if the word already exists.
         */
        void insert(T *object, const std::string &word) {
            Trie* current = this;
            for (char ch : word) {
                Trie* &child = current->children[ch];
                if (!child) {
                    child = new Trie;
                }
                current = child;
            }
            current->object = object;
        }

        /**
         * @brief Removes a word from the Trie.
         * @param word Word to remove.
         * @return True if word was found and removed, false if word doesn't exist.
         * @note Does not deallocate the associated object; user must manage that.
         *       Automatically cleans up empty nodes after removal.
         */
        bool erase(const std::string &word) {
            if(!wordExists(word)) {
                return false;
            }
            removeRecursive(word);
            return true;
        }

        /**
         * @brief Checks if a word exists and returns its associated object.
         * @param word Word to search for.
         * @return Object pointer if found, nullptr otherwise.
         */
        T* wordExists(const std::string &word) {
            return const_cast<T*>(static_cast<const Trie*>(this)->wordExists(word));
        }

        /**
         * @brief Const overload of wordExists().
         */
        const T* wordExists(const std::string &word) const {
            const Trie *current = find(word);
            return current && current->object ? current->object : nullptr;
        }

        /**
         * @brief Checks if a prefix exists.
         * @param prefix Prefix to search for.
         * @return True if any word starts with this prefix.
         */
        bool prefixExists(const std::string &prefix) const {
            return find(prefix) != nullptr;
        }

        /**
         * @brief Applies a function to all objects in the Trie.
         * @tparam Func Callable type.
         * @param function Called with each T* in the Trie.
         */
        template<typename Func>
        void traverse(Func function) const {
            this->traverseRecursive(function);
        }

        /**
         * @brief Retrieves all objects matching a prefix in lexicographic order.
         * @param prefix String prefix to search for.
         * @return Vector of pointers to matching objects, sorted lexicographically.
         */
        std::vector<T*> autoComplete(const std::string &prefix) const {
            std::vector<T*> results;
            const Trie* root = find(prefix);
            if (root) {
                root->getAllObjects(results);
            }
            return results;
        }

        /**
         * @brief Deallocates all nodes. Does not deallocate associated objects.
         */
        void clear() {
            for (auto &[ch, child] : children) {
                delete child;
                child = nullptr;
            }
            children.clear();
        }
    };
} // namespace Sefn
