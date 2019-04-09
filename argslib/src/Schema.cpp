#include <Args.hpp>

using namespace Args;

void Schema::addFlag(const ArgId &flagname) {
    _flags.insert(flagname);
}

void Schema::addInt(const ArgId &intname) {
    _ints.insert(intname);
}

void Schema::addStr(const ArgId &strarg) {
    _strs.insert(strarg);
}