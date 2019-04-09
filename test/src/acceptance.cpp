#include <CppUTest/TestHarness.h>
#include <Args.hpp>

TEST_GROUP(ArgsAcceptanceTestGroup) {
};

TEST(ArgsAcceptanceTestGroup, ArgsShould_parse_boolean_flag) {
    // Given
    Args::Schema schema;
    schema.addFlag("aflag");
    schema.addFlag("bflag");
    int argc = 1;
    const char *argv[1] = {"-bflag"};
    // When
    Args::Parser parser(schema);
    parser.parse(argc, argv);
    // Check
    CHECK_FALSE(parser.getBool("aflag"));
    CHECK_TRUE(parser.getBool("bflag"));
}
