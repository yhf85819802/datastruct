#include "binary_heap.h"

#include <gtest/gtest.h>

TEST(binary_heap, init) {
    BinaryHeap<int> bh1;
    EXPECT_TRUE(bh1.empty());
    EXPECT_EQ(bh1.size(), 0);

    std::vector<int> vec_int{3, 5, 2, 1, 8};
    
    BinaryHeap<int> bh2{vec_int.begin(), vec_int.end()};
    EXPECT_FALSE(bh2.empty());
    EXPECT_EQ(bh2.size(), 5);
    std::vector<int> vec_int_out;
    while (!bh2.empty()) {
       vec_int_out.push_back(bh2.top()); 
       bh2.pop();
    }
    EXPECT_EQ(vec_int_out, (std::vector<int>{1, 2, 3, 5, 8}));
    EXPECT_TRUE(bh2.empty());
    bh2.insert(3);
    bh2.insert(5);
    bh2.insert(2);
    EXPECT_EQ(bh2.top(), 2);
    bh2.insert(1);
    EXPECT_EQ(bh2.top(), 1);
    bh2.insert(8);
    EXPECT_EQ(bh2.top(), 1);


    BinaryHeap<int, std::greater<int>> bh3{vec_int.begin(), vec_int.end()};
    EXPECT_FALSE(bh3.empty());
    EXPECT_EQ(bh3.size(), 5);
    vec_int_out.clear();
    while (!bh3.empty()) {
       vec_int_out.push_back(bh3.top()); 
       bh3.pop();
    }
    EXPECT_EQ(vec_int_out, (std::vector<int>{8, 5, 3, 2, 1}));
    EXPECT_TRUE(bh3.empty());

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
