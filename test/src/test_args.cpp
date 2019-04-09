#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(ArgsTestGroup) {
};

TEST(ArgsTestGroup, ArgsFirstTest) {
    // FAIL("Failing..");
}

TEST(ArgsTestGroup, ArgsSecondTest) {
    CHECK(1 + 1 == 2);
}

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
