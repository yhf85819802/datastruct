#include "trie.h"

#include <gtest/gtest.h>
#include <string>

TEST(test_trie, trie) {
    Trie<char> char_trie{[](char c){return c - 'a';}, 26};
    EXPECT_FALSE(char_trie.has(std::string("abc")));

    char_trie.insert(std::string("abc"));
    EXPECT_TRUE(char_trie.has(std::string("abc")));
    EXPECT_FALSE(char_trie.has(std::string("ab")));
    EXPECT_FALSE(char_trie.has(std::string("a")));

    char_trie.insert(std::string("ab"));
    EXPECT_TRUE(char_trie.has(std::string("abc")));
    EXPECT_TRUE(char_trie.has(std::string("ab")));
    EXPECT_FALSE(char_trie.has(std::string("a")));

    char_trie.erase(std::string("abc"));
    EXPECT_FALSE(char_trie.has(std::string("abc")));
    EXPECT_TRUE(char_trie.has(std::string("ab")));
    EXPECT_FALSE(char_trie.has(std::string("a")));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
