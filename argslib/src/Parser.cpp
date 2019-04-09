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
            int val = std::atoi(argv[++arg]);
            _int_args[argname] = val;
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

inline bool Parser::isFlagValid(std::string flag) {
    return (_flag_args.find(flag) != _flag_args.end());
}

bool Parser::getBool(std::string flag) {
    if (isFlagValid(flag)) {
        return _flag_args[flag];
    }
    throw "Undefined Flag";
}

inline bool Parser::isIntNameValid(std::string intname) {
    return (_int_args.find(intname) != _int_args.end());
}

int Parser::getInt(std::string intname) {
    if (isIntNameValid(intname)) {
        return _int_args[intname];
    }
    throw "Undefine Int";
}
