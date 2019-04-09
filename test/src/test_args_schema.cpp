#include <CppUTest/TestHarness.h>

#include <Args.hpp>

using namespace Args;

TEST_GROUP(SchemaUnitTestGroup) {
};

TEST(SchemaUnitTestGroup, SchemaShould_save_boolean_flags) {
    // Given
    Schema sch;
    std::string flagname = "FLAG";
    // When
    sch.addFlag(flagname);
    // Check
    CHECK_TRUE(sch.hasFlag(flagname));
}