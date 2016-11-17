#include <string>
#include "matrix.hpp"
#include "gtest/gtest.h"

using namespace std;

namespace {
class MatrixTest
    : public ::testing::Test {
protected:
    MatrixTest()
        :
        mx1{1, 2, 3, 0, 5, 1}, mx2{2, 2, 2, 2, 2, 2} {
    }
public:
    nMatrix<int, 2, 3> mx1;
    nMatrix<int, 2, 3> mx2;
};
} // end of namespace

TEST_F(MatrixTest, ArithmeticTests) {
    auto mx3 = mx1 + mx2;
    EXPECT_TRUE(mx3(0, 0) == (2 + 1));
    EXPECT_TRUE(mx3(0, 1) == (2 + 2));
    EXPECT_TRUE(mx3(0, 2) == (2 + 3));
    EXPECT_TRUE(mx3(1, 0) == (2 + 0));
    EXPECT_TRUE(mx3(1, 1) == (2 + 5));
    EXPECT_TRUE(mx3(1, 2) == (2 + 1));

    auto mx21 = mx1 + 3;
    EXPECT_TRUE(mx21(0, 0) == (3 + 1));
    EXPECT_TRUE(mx21(0, 1) == (3 + 2));
    EXPECT_TRUE(mx21(0, 2) == (3 + 3));
    EXPECT_TRUE(mx21(1, 0) == (3 + 0));
    EXPECT_TRUE(mx21(1, 1) == (3 + 5));
    EXPECT_TRUE(mx21(1, 2) == (3 + 1));

    auto mx22 = 3 * mx1;
    EXPECT_TRUE(mx22(0, 0) == (3 * 1));
    EXPECT_TRUE(mx22(0, 1) == (3 * 2));
    EXPECT_TRUE(mx22(0, 2) == (3 * 3));
    EXPECT_TRUE(mx22(1, 0) == (3 * 0));
    EXPECT_TRUE(mx22(1, 1) == (3 * 5));
    EXPECT_TRUE(mx22(1, 2) == (3 * 1));

    mx1 += 3;
    EXPECT_TRUE(mx1(0, 0) == (3 + 1));
    EXPECT_TRUE(mx1(0, 1) == (3 + 2));
    EXPECT_TRUE(mx1(0, 2) == (3 + 3));
    EXPECT_TRUE(mx1(1, 0) == (3 + 0));
    EXPECT_TRUE(mx1(1, 1) == (3 + 5));
    EXPECT_TRUE(mx1(1, 2) == (3 + 1));

    mx1 /= 2;
    EXPECT_TRUE(mx1(0, 0) == (3 + 1) / 2);
    EXPECT_TRUE(mx1(0, 1) == (3 + 2) / 2);
    EXPECT_TRUE(mx1(0, 2) == (3 + 3) / 2);
    EXPECT_TRUE(mx1(1, 0) == (3 + 0) / 2);
    EXPECT_TRUE(mx1(1, 1) == (3 + 5) / 2);
    EXPECT_TRUE(mx1(1, 2) == (3 + 1) / 2);

    auto mx23 = 10 / mx2;
    EXPECT_TRUE(mx23(0, 0) == (10 / 2));
    EXPECT_TRUE(mx23(0, 1) == (10 / 2));
    EXPECT_TRUE(mx23(0, 2) == (10 / 2));
    EXPECT_TRUE(mx23(1, 0) == (10 / 2));
    EXPECT_TRUE(mx23(1, 1) == (10 / 2));
    EXPECT_TRUE(mx23(1, 2) == (10 / 2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}