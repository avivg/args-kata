#include <Args.hpp>
#include <cstdlib>

using namespace Args;

Parser::Parser(Args::Schema &schema) {
    initFromSchema(schema);
}

void Parser::initFromSchema(Schema &schema) {
    initBooleans(schema.flags());
    initIntegers(schema.intNames());
    initStrings(schema.strArgs());
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

const std::string Parser::DEFAULT_STR = "";
void Parser::initStrings(std::set<std::string> schemaStrArgs) {
    for (std::set<std::string>::iterator it = schemaStrArgs.begin();
            it != schemaStrArgs.end(); ++it) {
        std::string strarg = *it;
        _str_args[strarg] = Parser::DEFAULT_STR;
    }
}

const char * getArgName(const char *arg) {
    // Currently only skip the '-'
    return arg + 1;
    // TODO validate arg is of pattern /-[a-zA-Z].*/
}

void Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        std::string argname = getArgName(argv[arg]);
        if (isFlagValid(argname)) {
            _flag_args[argname] = true;
        } else if (isIntNameValid(argname)) {
            _int_args[argname] = std::atoi(argv[++arg]);
        } else if (isStrArgValid(argname)) {
            _str_args[argname] = argv[++arg];
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

inline bool Parser::isStrArgValid(std::string strarg) {
    return isIdInMap(_str_args, strarg);
}

std::string Parser::getStr(std::string strarg) {
    if (isStrArgValid(strarg)) {
        return _str_args[strarg];
    }
    throw "Undefined String";
}