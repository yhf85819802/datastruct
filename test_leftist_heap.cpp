#include "leftist_heap.h"

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <iterator>

TEST(test_leftist_heap, init) {
    LeftistHeap<int> lh;
    EXPECT_TRUE(lh.empty());

    lh.insert(9);
    lh.insert(8);
    EXPECT_EQ(lh.top(), 8);

    lh.insert(6);
    EXPECT_EQ(lh.top(), 6);

    lh.insert(7);
    std::vector<int> vec_int;
    lh.level_traverse(std::back_inserter(vec_int));
    EXPECT_EQ(lh.top(), 6);
    EXPECT_EQ(vec_int.size(), 4);
    EXPECT_EQ(vec_int[0], 6);
    EXPECT_EQ(vec_int[1], 8);
    EXPECT_EQ(vec_int[2], 7);
    EXPECT_EQ(vec_int[3], 9);
    
    auto lh2{lh};
    EXPECT_EQ(lh2.top(), 6);
    lh2.clear();
    EXPECT_TRUE(lh2.empty());
    lh2.insert(8);
    lh2.insert(12);
    lh2.insert(9);
    vec_int.clear();
    lh2.level_traverse(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 3);
    EXPECT_EQ(vec_int[0], 8);
    EXPECT_EQ(vec_int[1], 12);
    EXPECT_EQ(vec_int[2], 9);

    lh.merge(lh2);
    EXPECT_TRUE(lh2.empty());
    vec_int.clear();
    lh.level_traverse(std::back_inserter(vec_int));
    EXPECT_EQ(vec_int.size(), 7);
    EXPECT_EQ(vec_int[0], 6);
    EXPECT_EQ(vec_int[1], 8);
    EXPECT_EQ(vec_int[2], 7);
    EXPECT_EQ(vec_int[3], 9);
    EXPECT_EQ(vec_int[4], 8);
    EXPECT_EQ(vec_int[5], 12);
    EXPECT_EQ(vec_int[6], 9);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
