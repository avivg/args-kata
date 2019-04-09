#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <Args.hpp>

TEST_GROUP(ArgsAcceptanceTestGroup) {
};

TEST(ArgsAcceptanceTestGroup, ArgsShould_parse_boolean_flag) {
    // Given
    Args::Schema schema;
    schema.addFlag("-b");
}


int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
