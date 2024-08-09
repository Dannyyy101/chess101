
#include <gtest/gtest.h>

// Simple factorial function for demonstration purposes
int Factorial(int n) {
    return (n <= 1) ? 1 : n * Factorial(n - 1);
}

TEST(FactorialTest, HandlesZeroInput) {
EXPECT_EQ(Factorial(0), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
