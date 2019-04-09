
#include <Args.hpp>
#include <CppUTest/TestHarness.h>

using namespace Args;

TEST_GROUP(SchemaUnitTestGroup) {
};

TEST(SchemaUnitTestGroup, SchemaShould_SaveBooleanFlags) {
    // Given
    Schema sch;
    std::string flagname = "FLAG";
    // When
    sch.addFlag(flagname);
    // Check
    CHECK_EQUAL(1, sch.flags().size());
    CHECK(*sch.flags().begin() == flagname);
}

TEST(SchemaUnitTestGroup, SchemaShould_SaveIntArgs) {
        // Given
    Schema sch;
    std::string intname = "NUMBER";
    // When
    sch.addInt(intname);
    // Check
    CHECK_EQUAL(1, sch.intNames().size());
    CHECK(intname == *sch.intNames().begin());
}

TEST(SchemaUnitTestGroup, SchemaShould_SaveStringArgs) {
        // Given
    Schema sch;
    std::string argname = "STR";
    // When
    sch.addStr(argname);
    // Check
    CHECK_EQUAL(1, sch.strArgs().size());
    CHECK(argname == *sch.strArgs().begin());
}
