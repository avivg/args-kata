#include <Args.hpp>

using namespace Args;

void Schema::addFlag(std::string flagname) {
    _flags.insert(flagname);
}

void Schema::addInt(std::string intname) {
    _ints.insert(intname);
}

void Schema::addStr(std::string strarg) {
    _strs.insert(strarg);
}