#include "functional.hpp"
#include "gtest/gtest.h"

using namespace std;
namespace {
class FunctionalTest
    : public ::testing::Test {
protected:
    FunctionalTest() {}

public:

};

int add1(int k) { return k + 1; }

int mul2(int k) { return k * 2; }

int sub3(int k) { return k - 3; }


TEST_F(FunctionalTest, RunTest1) {
    EXPECT_EQ(FP::Run(3, &add1, &mul2, &add1, &sub3), 6);
}

TEST_F(FunctionalTest, PipelineTest1) {
    FP::Pipeline<int> math;
    math.Register(&add1).Register(&mul2).Register(&add1).Register(&sub3);
    EXPECT_EQ(math(3), 6);
}

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
