#include <Args.hpp>

using namespace Args;

template <typename T>
bool set_has_identifier(std::set<T> s, T id) {
    return (s.find(id) != s.end());
}

void Schema::addFlag(std::string flagname) {
    _flags.insert(flagname);
}

bool Schema::hasFlag(std::string flagname) {
    return set_has_identifier(_flags, flagname);
}

void Schema::addInt(std::string intname) {
    _ints.insert(intname);
}

bool Schema::hasInt(std::string intname) {
    return set_has_identifier(_ints, intname);
}