#include "avl_tree.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <gtest/gtest.h>

TEST(bst_test, test_construct) {
    AvlTree<int> bst;
    EXPECT_EQ(bst.empty(), true);
    AvlTree<int> bst2{bst};
    EXPECT_EQ(bst2.empty(), true);
}

TEST(bst_test, test_search) {
    AvlTree<int> bst;
    bst.insert(5);
    bst.insert(2);
    bst.insert(8);
    bst.insert(1);
    bst.insert(7);
    bst.insert(4);
    bst.insert(3);

    EXPECT_TRUE(bst.contain(1));
    EXPECT_TRUE(bst.contain(5));
    EXPECT_TRUE(bst.contain(8));
    EXPECT_FALSE(bst.contain(6));

    std::vector<int> vec_int;
    bst.traverse(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 7);
    EXPECT_EQ(vec_int[0], 1);
    EXPECT_EQ(vec_int[3], 4);
    EXPECT_EQ(vec_int[5], 7);
    EXPECT_EQ(vec_int[6], 8);

    bst.clear();
    vec_int.clear();
    EXPECT_TRUE(bst.empty());
    EXPECT_TRUE(vec_int.empty());

    bst.insert(0);
    bst.insert(100);
    EXPECT_TRUE(bst.contain(0));
    EXPECT_TRUE(bst.contain(100));
    EXPECT_FALSE(bst.empty());
    EXPECT_FALSE(bst.contain(1));
    EXPECT_FALSE(bst.contain(2));

    bst.traverse(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 2);
    EXPECT_EQ(vec_int[0], 0);
    EXPECT_EQ(vec_int[1], 100);
}

TEST(bst_test, test_insert) {
    AvlTree<int> bst;
    bst.insert(5);
    bst.insert(2);
    bst.insert(8);
    bst.insert(1);
    bst.insert(4);
    bst.insert(7);
    bst.insert(3);
    bst.insert(6);

    std::vector<int> vec_int;
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 8);
    EXPECT_EQ(vec_int[0], 5);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 7);
    EXPECT_EQ(vec_int[3], 1);
    EXPECT_EQ(vec_int[4], 4);
    EXPECT_EQ(vec_int[5], 6);
    EXPECT_EQ(vec_int[6], 8);
    EXPECT_EQ(vec_int[7], 3);

    vec_int.clear();
    bst.clear();
    EXPECT_TRUE(vec_int.empty());
    EXPECT_TRUE(bst.empty());
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 5);
    EXPECT_EQ(vec_int[0], 2);
    EXPECT_EQ(vec_int[1], 1);
    EXPECT_EQ(vec_int[2], 4);
    EXPECT_EQ(vec_int[3], 3);
    EXPECT_EQ(vec_int[4], 5);

    vec_int.clear();
    bst.insert(6);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 6);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 5);
    EXPECT_EQ(vec_int[3], 1);
    EXPECT_EQ(vec_int[4], 3);
    EXPECT_EQ(vec_int[5], 6);

    vec_int.clear();
    bst.insert(7);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 7);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 6);
    EXPECT_EQ(vec_int[3], 1);
    EXPECT_EQ(vec_int[4], 3);
    EXPECT_EQ(vec_int[5], 5);
    EXPECT_EQ(vec_int[6], 7);

    vec_int.clear();
    bst.insert(16);
    bst.insert(15);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 9);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 6);
    EXPECT_EQ(vec_int[3], 1);
    EXPECT_EQ(vec_int[4], 3);
    EXPECT_EQ(vec_int[5], 5);
    EXPECT_EQ(vec_int[6], 15);
    EXPECT_EQ(vec_int[7], 7);
    EXPECT_EQ(vec_int[8], 16);

    vec_int.clear();
    bst.insert(14);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 10);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 7);
    EXPECT_EQ(vec_int[3], 1);
    EXPECT_EQ(vec_int[4], 3);
    EXPECT_EQ(vec_int[5], 6);
    EXPECT_EQ(vec_int[6], 15);
    EXPECT_EQ(vec_int[7], 5);
    EXPECT_EQ(vec_int[8], 14);
    EXPECT_EQ(vec_int[9], 16);

    vec_int.clear();
    bst.insert(13);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 11);
    EXPECT_EQ(vec_int[0], 7);
    EXPECT_EQ(vec_int[1], 4);
    EXPECT_EQ(vec_int[2], 15);
    EXPECT_EQ(vec_int[3], 2);
    EXPECT_EQ(vec_int[4], 6);
    EXPECT_EQ(vec_int[5], 14);
    EXPECT_EQ(vec_int[6], 16);
    EXPECT_EQ(vec_int[7], 1);
    EXPECT_EQ(vec_int[8], 3);
    EXPECT_EQ(vec_int[9], 5);
    EXPECT_EQ(vec_int[10], 13);

    vec_int.clear();
    bst.insert(12);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 12);
    EXPECT_EQ(vec_int[0], 7);
    EXPECT_EQ(vec_int[1], 4);
    EXPECT_EQ(vec_int[2], 15);
    EXPECT_EQ(vec_int[3], 2);
    EXPECT_EQ(vec_int[4], 6);
    EXPECT_EQ(vec_int[5], 13);
    EXPECT_EQ(vec_int[6], 16);
    EXPECT_EQ(vec_int[7], 1);
    EXPECT_EQ(vec_int[8], 3);
    EXPECT_EQ(vec_int[9], 5);
    EXPECT_EQ(vec_int[10], 12);
    EXPECT_EQ(vec_int[11], 14);
    
    vec_int.clear();
    bst.insert(11);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 13);
    EXPECT_EQ(vec_int[0], 7);
    EXPECT_EQ(vec_int[1], 4);
    EXPECT_EQ(vec_int[2], 13);
    EXPECT_EQ(vec_int[3], 2);
    EXPECT_EQ(vec_int[4], 6);
    EXPECT_EQ(vec_int[5], 12);
    EXPECT_EQ(vec_int[6], 15);
    EXPECT_EQ(vec_int[7], 1);
    EXPECT_EQ(vec_int[8], 3);
    EXPECT_EQ(vec_int[9], 5);
    EXPECT_EQ(vec_int[10], 11);
    EXPECT_EQ(vec_int[11], 14);
    EXPECT_EQ(vec_int[12], 16);

    vec_int.clear();
    bst.insert(10);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 14);
    EXPECT_EQ(vec_int[0], 7);
    EXPECT_EQ(vec_int[1], 4);
    EXPECT_EQ(vec_int[2], 13);
    EXPECT_EQ(vec_int[3], 2);
    EXPECT_EQ(vec_int[4], 6);
    EXPECT_EQ(vec_int[5], 11);
    EXPECT_EQ(vec_int[6], 15);
    EXPECT_EQ(vec_int[7], 1);
    EXPECT_EQ(vec_int[8], 3);
    EXPECT_EQ(vec_int[9], 5);
    EXPECT_EQ(vec_int[10], 10);
    EXPECT_EQ(vec_int[11], 12);
    EXPECT_EQ(vec_int[12], 14);
    EXPECT_EQ(vec_int[13], 16);

    bst.insert(8);
    bst.insert(9);
    vec_int.clear();
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 16);
    EXPECT_EQ(vec_int[0], 7);
    EXPECT_EQ(vec_int[1], 4);
    EXPECT_EQ(vec_int[2], 13);
    EXPECT_EQ(vec_int[3], 2);
    EXPECT_EQ(vec_int[4], 6);
    EXPECT_EQ(vec_int[5], 11);
    EXPECT_EQ(vec_int[6], 15);
    EXPECT_EQ(vec_int[7], 1);
    EXPECT_EQ(vec_int[8], 3);
    EXPECT_EQ(vec_int[9], 5);
    EXPECT_EQ(vec_int[10], 9);
    EXPECT_EQ(vec_int[11], 12);
    EXPECT_EQ(vec_int[12], 14);
    EXPECT_EQ(vec_int[13], 16);
    EXPECT_EQ(vec_int[14], 8);
    EXPECT_EQ(vec_int[15], 10);
}

TEST(bst_test, test_erase) {
    AvlTree<int> bst;
    std::vector<int> vec_int;

    bst.insert(3);
    bst.insert(2);
    bst.erase(2);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 1);
    EXPECT_EQ(vec_int[0], 3);
    
    vec_int.clear();
    bst.insert(4);
    bst.erase(4);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 1);
    EXPECT_EQ(vec_int[0], 3);

    vec_int.clear();
    bst.insert(2);
    bst.insert(4);
    bst.erase(3);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 2);
    EXPECT_EQ(vec_int[0], 4);

    vec_int.clear();
    bst.insert(6);
    bst.insert(1);
    bst.insert(8);
    bst.erase(6);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 4);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 8);
    EXPECT_EQ(vec_int[3], 1);

    // LL
    vec_int.clear();
    bst.erase(8);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 3);
    EXPECT_EQ(vec_int[0], 2);
    EXPECT_EQ(vec_int[1], 1);
    EXPECT_EQ(vec_int[2], 4);

    // RR
    bst.insert(6);
    bst.erase(1);
    vec_int.clear();
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 3);
    EXPECT_EQ(vec_int[0], 4);
    EXPECT_EQ(vec_int[1], 2);
    EXPECT_EQ(vec_int[2], 6);

    // LR
    vec_int.clear();
    bst.clear();
    bst.insert(80);
    bst.insert(50);
    bst.insert(100);
    bst.insert(40);
    bst.insert(45);
    bst.insert(60);
    bst.insert(90);
    bst.insert(140);
    bst.insert(83);
    bst.insert(95);
    bst.insert(150);
    bst.insert(96);
    bst.erase(140);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 11);
    EXPECT_EQ(vec_int[0], 80);
    EXPECT_EQ(vec_int[1], 50);
    EXPECT_EQ(vec_int[2], 95);
    EXPECT_EQ(vec_int[3], 40);
    EXPECT_EQ(vec_int[4], 60);
    EXPECT_EQ(vec_int[5], 90);
    EXPECT_EQ(vec_int[6], 100);
    EXPECT_EQ(vec_int[7], 45);
    EXPECT_EQ(vec_int[8], 83);
    EXPECT_EQ(vec_int[9], 96);
    EXPECT_EQ(vec_int[10], 150);

    // RL
    vec_int.clear();
    bst.erase(100);
    bst.erase(96);
    bst.erase(50);
    bst.erase(40);
    bst.erase(60);
    bst.traverse_by_level(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 6);
    EXPECT_EQ(vec_int[0], 90);
    EXPECT_EQ(vec_int[1], 80);
    EXPECT_EQ(vec_int[2], 95);
    EXPECT_EQ(vec_int[3], 45);
    EXPECT_EQ(vec_int[4], 83);
    EXPECT_EQ(vec_int[5], 150);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
