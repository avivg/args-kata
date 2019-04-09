#include <Args.hpp>
#include <string>

using namespace Args;

Parser::Parser(Schema &schema) {
    initFromSchema(schema);
}

void Parser::initFromSchema(Schema &schema) {
    initBooleans(schema.flags());
    initIntegers(schema.intNames());
    initStrings(schema.strArgs());
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

template<typename valT>
void Parser::initArgMapWithDefaultVals(
    ArgMap<valT> &argmap,
    const ArgIdSet &keys,
    const valT initval) {
    for (auto key : keys) {
        argmap[key] = initval;
    }
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
            _int_args[argname] = std::stoi(argv[++arg]);
        } else if (isStrArgValid(argname)) {
            _str_args[argname] = argv[++arg];
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

inline bool Parser::isFlagValid(const ArgId &flag) {
    return isIdInMap(_flag_args, flag);
}

bool Parser::getBool(const ArgId flag) {
    if (isFlagValid(flag)) {
        return _flag_args[flag];
    }
    throw "Undefined Flag";
}

inline bool Parser::isIntNameValid(const ArgId &intname) {
    return isIdInMap(_int_args, intname);
}

int Parser::getInt(const ArgId intname) {
    if (isIntNameValid(intname)) {
        return _int_args[intname];
    }
    throw "Undefine Int";
}

inline bool Parser::isStrArgValid(const ArgId &strarg) {
    return isIdInMap(_str_args, strarg);
}

std::string Parser::getStr(const ArgId strarg) {
    if (isStrArgValid(strarg)) {
        return _str_args[strarg];
    }
    throw "Undefined String";
}

template<typename valT>
bool Parser::isIdInMap(const ArgMap<valT> argmap, const ArgId id) {
    return (argmap.find(id) != argmap.end());
}
