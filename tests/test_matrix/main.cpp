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

    #ifndef __clang__ /* the following code doesn't compile on clang yet */
    /* different types */
        nMatrix<unsigned int, 2, 3> mx4{2, 1, 2, 4, 5, 6};
        Display2dMatrix(mx1.operate(mx4, MultiplyIntInt));
        /* [  2  2  6
         *    0  25 6] */

        nMatrix<bool, 2, 3> mx5{false, true, true, false, true, false};
        Display2dMatrix(mx1.operate(mx5, AddIntBool));
        /*
         * */

        nMatrix<string, 2, 3> mx6{};
    //    Display2dMatrix(mx1.operate(mx6, AddIntBool)); /* this won't compile because int cannot be converted to string */

        nMatrix<double, 2, 3> mx7{1., 2., 3., 4., 5., 6.};
        Display2dMatrix(mx1.operate(mx7, AddIntDouble));

        nMatrix<int, 2, 3>::convert_t<string> mx8{};
        decltype(mx1)::convert_t<string> mx8{}; // this works but Clion doesn't understand it
    #endif

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