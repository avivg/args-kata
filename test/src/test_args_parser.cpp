
#include <Args.hpp>
#include <CppUTest/TestHarness.h>

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
    parser.parse(0, NULL);
    // Check
    CHECK_FALSE(parser.getBool(flagname));
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedFlagWhileParsing) {
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

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedFlagWhileGetting) {
    // Given
    Schema sch;
    sch.addFlag("abc");
    Parser parser(sch);
    const char *arg = "-abc";
    // When
    parser.parse(1, &arg);
    // Check
    try {
        parser.getBool("cba");
        FAIL("Expected exception to be raised.. :(");
    } catch (const char * msg) {
        
    }
}

TEST(ParserUnitTestGroup, ParserShould_ReturnValForSuppliedInt) {
    // Given
    Schema sch;
    sch.addInt("number");
    Parser parser(sch);
    const char *argv[2] = {"-number", "13"};
    // When
    parser.parse(2, argv);
    // Check
    CHECK_EQUAL(13, parser.getInt("number"));
}

TEST(ParserUnitTestGroup, ParserShould_ReturnZeroForNotSuppliedInt) {
    // Given
    Schema sch;
    sch.addInt("number");
    Parser parser(sch);
    // When
    parser.parse(0, NULL);
    // Check
    CHECK_EQUAL(0, parser.getInt("number"));
}

TEST(ParserUnitTestGroup, ParserShould_ReturnNegativeValues) {
    // Given
    Schema sch;
    sch.addInt("num");
    Parser parser(sch);
    // When
    const char *args[2] = {"-num", "-65536"};
    parser.parse(2, args);
    // Check
    CHECK_EQUAL(-65536, parser.getInt("num"));
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedIntWhileParsing) {
    // Given
    Schema sch;
    sch.addInt("number");
    Parser parser(sch);
    // When
    const char *argv[2] = {"-abc", "5"};
    // Check
    try {
        parser.parse(2, argv);
        FAIL("Expected exception.. :(");
    } catch (const char * msg) {

    }
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedIntWhileGetting) {
    // Given
    Schema sch;
    sch.addInt("number");
    Parser parser(sch);
    const char *argv[2] = {"-number", "5"};
    // When
    parser.parse(2, argv);
    // Check
    try {
        parser.getInt("abc");
        FAIL("Expected exception.. :(");
    } catch (const char * msg) {

    }
}

TEST(ParserUnitTestGroup, ParserShould_ReturnValForSuppliedStr) {
    // Given
    Schema sch;
    sch.addStr("dir");
    Parser parser(sch);
    const char *argv[2] = {"-dir", "some/string"};
    // When
    parser.parse(2, argv);
    // Check
    CHECK("some/string" == parser.getStr("dir"));
}

TEST(ParserUnitTestGroup, ParserShould_ReturnEmptyForNotSuppliedStr) {
    // Given
    Schema sch;
    sch.addStr("dir");
    Parser parser(sch);
    // When
    parser.parse(0, NULL);
    // Check
    CHECK("" == parser.getStr("dir"));
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedStrWhileParsing) {
    // Given
    Schema sch;
    sch.addStr("str1");
    Parser parser(sch);
    // When
    const char *argv[2] = {"-str2", "blabla"};
    // Check
    try {
        parser.parse(2, argv);
        FAIL("Expected exception.. :(");
    } catch (const char * msg) {

    }
}

TEST(ParserUnitTestGroup, ParserShould_Raise_ForNotDefinedStrWhileGetting) {
    // Given
    Schema sch;
    sch.addStr("str1");
    Parser parser(sch);
    const char *argv[2] = {"-str1", "foo/bar"};
    // When
    parser.parse(2, argv);
    // Check
    try {
        parser.getStr("abc");
        FAIL("Expected exception.. :(");
    } catch (const char * msg) {

    }
}