#include <CppUTest/TestHarness.h>

#include <Args.hpp>

using namespace Args;

TEST_GROUP(ParserUnitTestGroup) {
};

TEST(ParserUnitTestGroup, ParserShould_RetTrue_ForSuppliedFlag) {
    // Given
    std::string flagname = "bflag";
    const char *arg = "-bflag";
    Schema sch;
    sch.addFlag(flagname);
    Parser parser(sch);
    // When
    parser.parse(1, &arg);
    // Check
    CHECK_TRUE(parser.getBool(flagname));
}

TEST(ParserUnitTestGroup, ParserShould_RetFalse_ForNotSuppliedFlag) {
    // Given
    std::string flagname = "bflag";
    Schema sch;
    sch.addFlag(flagname);
    Parser parser(sch);
    // When
    parser.parse(0, nullptr);
    // Check
    CHECK_FALSE(parser.getBool(flagname));
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedFlag) {
    // Given
    Schema sch;
    sch.addFlag("abc");
    Parser parser(sch);
    // When
    const char *arg = "-cba";
    // Check
    try {
        parser.parse(1, &arg);
        FAIL("Expected exception to be raised.. :(");
    } catch (const char * msg) {
        
    }
}