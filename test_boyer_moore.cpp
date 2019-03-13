#include "boyer_moore.h"

#include <gtest/gtest.h>

TEST(test_boyer_moore, boyer_moore) {
    std::string text = "HERE IS A SIMPLE EXAMPLE";
    std::string pattern1 = "EXAMPLE";
    std::string pattern2 = "HERE";
    std::string pattern3 = "A";
    std::string pattern4 = "SAMPLE";
    std::string pattern5 = "is";

    EXPECT_EQ(boyer_moore::find(text, pattern1), 17);
    EXPECT_EQ(boyer_moore::find(text, pattern2), 0);
    EXPECT_EQ(boyer_moore::find(text, pattern3), 8);
    EXPECT_EQ(boyer_moore::find(text, pattern4), -1);
    EXPECT_EQ(boyer_moore::find(text, pattern5), -1);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
