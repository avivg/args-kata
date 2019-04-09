#include <Args.hpp>
#include <cstdlib>

using namespace Args;

Parser::Parser(Schema &schema) {
    initFromSchema(schema);
}

void Parser::initFromSchema(Schema &schema) {
    initBooleans(schema.flags());
    initIntegers(schema.intNames());
    initStrings(schema.strArgs());
}

template<typename valT>
void initArgMapWithDefaultVals(ArgMap<valT> &argmap, const ArgIdSet &keys, valT initval) {
    for (ArgIdSet::iterator it = keys.begin(); it != keys.end(); ++it) {
        argmap[*it] = initval;
    }
}

void Parser::initBooleans(const ArgIdSet &schemaFlags) {
    initArgMapWithDefaultVals(_flag_args, schemaFlags, false);
}

void Parser::initIntegers(const ArgIdSet &schemaIntNames) {
    initArgMapWithDefaultVals(_int_args, schemaIntNames, Parser::DEFAULT_INT);
}

const std::string Parser::DEFAULT_STR = "";
void Parser::initStrings(const ArgIdSet &schemaStrArgs) {
    initArgMapWithDefaultVals(_str_args, schemaStrArgs, Parser::DEFAULT_STR);
}

const char * getArgName(const char *arg) {
    // Currently only skip the '-'
    return arg + 1;
    // TODO validate arg is of pattern /-[a-zA-Z].*/
}

void Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        ArgId argname = getArgName(argv[arg]);
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

template<typename valT>
bool isIdInMap(ArgMap<valT> m, ArgId id) {
    return (m.find(id) != m.end());
}

inline bool Parser::isFlagValid(ArgId &flag) {
    return isIdInMap(_flag_args, flag);
}

bool Parser::getBool(ArgId flag) {
    if (isFlagValid(flag)) {
        return _flag_args[flag];
    }
    throw "Undefined Flag";
}

inline bool Parser::isIntNameValid(ArgId &intname) {
    return isIdInMap(_int_args, intname);
}

int Parser::getInt(ArgId intname) {
    if (isIntNameValid(intname)) {
        return _int_args[intname];
    }
    throw "Undefine Int";
}

inline bool Parser::isStrArgValid(ArgId &strarg) {
    return isIdInMap(_str_args, strarg);
}

std::string Parser::getStr(ArgId strarg) {
    if (isStrArgValid(strarg)) {
        return _str_args[strarg];
    }
    throw "Undefined String";
}