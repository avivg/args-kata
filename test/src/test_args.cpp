#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <Args.hpp>

TEST_GROUP(ArgsAcceptanceTestGroup) {
};

TEST(ArgsAcceptanceTestGroup, ArgsShould_parse_boolean_flag) {
    // Given
    Args::Schema schema;
    schema.addFlag("a");
    schema.addFlag("b");
    int argc = 1;
    char argv[1][4] = {"-b"};
    // When
    Args::Parser parser(schema);
    parser.parse(1, (char**)argv);
    // Check
    CHECK(parser.getBool("a") == false)
    CHECK(parser.getBool("b") == true)
}


int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
