#include <Args.hpp>

using namespace Args;

void Schema::addFlag(ArgId flagname) {
    _flags.insert(flagname);
}

void Schema::addInt(ArgId intname) {
    _ints.insert(intname);
}

void Schema::addStr(ArgId strarg) {
    _strs.insert(strarg);
}