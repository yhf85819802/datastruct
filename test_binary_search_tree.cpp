#include "binary_search_tree.h"

#include <iostream>
#include <gtest/gtest.h>

TEST(bst_test, test_construct) {
    BinarySearchTree<int> bst;
    EXPECT_EQ(bst.isEmpty(), true);
    BinarySearchTree<int> bst2{bst};
    EXPECT_EQ(bst2.isEmpty(), true);
}

TEST(bst_test, test_search) {
    BinarySearchTree<int> bst;
    bst.insert(3);
    bst.insert(1);
    bst.insert(9);
    bst.insert(5);
    bst.insert(7);
    EXPECT_EQ(bst.findMin(), 1);
    EXPECT_EQ(bst.findMax(), 9);
    bst.insert(0);
    bst.insert(100);
    EXPECT_EQ(bst.findMin(), 0);
    EXPECT_EQ(bst.findMax(), 100);
    EXPECT_EQ(bst.contains(5), true);
    EXPECT_EQ(bst.contains(10), false);
}

TEST(bst_test, test_insert_delete) {
    BinarySearchTree<int> bst;
    bst.insert(1);
    bst.insert(101);
    bst.insert(99);
    BinarySearchTree<int> bst2;
    bst2 = bst;
    EXPECT_EQ(bst.findMin(), 1);
    EXPECT_EQ(bst.findMax(), 101);
    bst.remove(1);
    EXPECT_EQ(bst.findMin(), 99);
    EXPECT_EQ(bst.findMax(), 101);
    bst.remove(101);
    EXPECT_EQ(bst.findMin(), 99);
    EXPECT_EQ(bst.findMax(), 99);
    bst.remove(99);
    EXPECT_EQ(bst.isEmpty(), true);
    
    EXPECT_EQ(bst2.isEmpty(), false);
    bst2.makeEmpty();
    EXPECT_EQ(bst2.isEmpty(), true);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
