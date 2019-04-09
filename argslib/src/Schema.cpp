#include <Args.hpp>

using namespace Args;

void Schema::addFlag(std::string flagname) {
    _flags.insert(flagname);
}

bool Schema::hasFlag(std::string flagname) {
    return _flags.find(flagname) != _flags.end();
}