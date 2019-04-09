#include <Args.hpp>
#include <cstdlib>

using namespace Args;

Parser::Parser(Args::Schema &schema) {
    initFromSchema(schema);
}

void Parser::initFromSchema(Schema &schema) {
    initBooleans(schema.flags());
    initIntegers(schema.intNames());
}

void Parser::initBooleans(std::set<std::string> schemaFlags) {
    for (std::set<std::string>::iterator it = schemaFlags.begin();
            it != schemaFlags.end(); ++it) {
        std::string flag = *it;
        _flag_args[flag] = false;
    }
}

void Parser::initIntegers(std::set<std::string> schemaIntNames) {
    for (std::set<std::string>::iterator it = schemaIntNames.begin();
            it != schemaIntNames.end(); ++it) {
        std::string intname = *it;
        _int_args[intname] = Parser::DEFAULT_INT;
    }
}

void Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        std::string argname = (argv[arg] + 1); // skip '-'
        if (isFlagValid(argname)) {
            _flag_args[argname] = true;
        } else if (isIntNameValid(argname)) {
            _int_args[argname] = std::atoi(argv[++arg]);
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

template<typename T, typename S>
bool isIdInMap(std::map<T,S> m, T id) {
    return (m.find(id) != m.end());
}

inline bool Parser::isFlagValid(std::string flag) {
    return isIdInMap(_flag_args, flag);
}

bool Parser::getBool(std::string flag) {
    if (isFlagValid(flag)) {
        return _flag_args[flag];
    }
    throw "Undefined Flag";
}

inline bool Parser::isIntNameValid(std::string intname) {
    return isIdInMap(_int_args, intname);
}

int Parser::getInt(std::string intname) {
    if (isIntNameValid(intname)) {
        return _int_args[intname];
    }
    throw "Undefine Int";
}
