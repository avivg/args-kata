#include <Args.hpp>

using namespace Args;

void Schema::addFlag(std::string flagname) {
    _flags.push_back(flagname);
}

bool Schema::hasFlag(std::string flagname) {
    for(auto iter = _flags.begin(); iter != _flags.end(); iter++) {
        if (*iter == flagname) {
            return true;
        }
    }
    return false;
}