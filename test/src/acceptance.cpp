#include <Args.hpp>
#include <CppUTest/TestHarness.h>

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

TEST(ArgsAcceptanceTestGroup, ArgsShould_ParseIntArg) {
    // Given
    Schema schema;
    schema.addInt("num1");
    schema.addInt("num2");
    int argc = 2;
    const char *argv[2] = {"-num2", "5"};
    // When
    Parser parser(schema);
    parser.parse(argc, argv);
    // Check
    CHECK_EQUAL(parser.getInt("num1"), 0);
    CHECK_EQUAL(parser.getInt("num2"), 5);
}

TEST(ArgsAcceptanceTestGroup, ArgsShould_ParseStringArg) {
    // Given
    Schema schema;
    schema.addStr("str1");
    schema.addStr("str2");
    int argc = 2;
    const char *argv[2] = {"-str1", "string/testing/string"};
    // When
    Parser parser(schema);
    parser.parse(argc, argv);
    // Check
    CHECK(parser.getStr("str1") == "string/testing/string");
    CHECK(parser.getStr("str2") == "");
}


TEST(ArgsAcceptanceTestGroup, ArgsShould_ParseIntWithBoolArg) {
    // Given
    Schema schema;
    schema.addInt("number1");
    schema.addInt("number2");
    schema.addFlag("flag1");
    schema.addFlag("flag2");
    schema.addStr("str1");
    schema.addStr("str2");
    const char *args[5] = {"-flag1", "-number2", "3", "-str1", "-zzz/yyy/-xxx"};
    // When
    Parser parser(schema);
    parser.parse(5, args);
    // Check
    CHECK_TRUE(parser.getBool("flag1"));
    CHECK_FALSE(parser.getBool("flag2"));
    CHECK_EQUAL(0, parser.getInt("number1"));
    CHECK_EQUAL(3, parser.getInt("number2"));
    CHECK("-zzz/yyy/-xxx" == parser.getStr("str1"));
    CHECK("" == parser.getStr("str2"));
}
