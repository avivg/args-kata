#include <CppUTest/TestHarness.h>
#include <Args.hpp>

using namespace Args;

TEST_GROUP(ArgsAcceptanceTestGroup) {
};

TEST(ArgsAcceptanceTestGroup, ArgsShould_parseBooleanFlag) {
    // Given
    Schema schema;
    schema.addFlag("aflag");
    schema.addFlag("bflag");
    int argc = 1;
    const char *argv[1] = {"-bflag"};
    // When
    Parser parser(schema);
    parser.parse(argc, argv);
    // Check
    CHECK_FALSE(parser.getBool("aflag"));
    CHECK_TRUE(parser.getBool("bflag"));
}

// TEST(ArgsAcceptanceTestGroup, ArgsShould_ParseIntArg) {
//     // Given
//     Schema schema;
//     schema.addInt("num1");
//     schema.addInt("num2");
//     int argc = 2;
//     const char *argv[2] = {"-num2", "5"};
//     // When
//     Parser parser(schema);
//     parser.parse(argc, argv);
//     // Check
//     CHECK_EQUAL(parser.getInt("num1"), 0);
//     CHECK_EQUAL(parser.getInt("num2"), 5);
// }