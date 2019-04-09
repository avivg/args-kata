#include <Args.hpp>
#include <cstdlib>

using namespace Args;

Parser::Parser(Args::Schema &schema) :
    _schema(schema)
{}

void Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        std::string flag_arg = (argv[arg] + 1); // skip '-'
        if (_schema.hasFlag(flag_arg)) {
            _flag_args.insert(flag_arg);
        } else if (_schema.hasInt(flag_arg)) {
            int val = std::atoi(argv[++arg]);
            _int_args[flag_arg] = val;
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

bool Parser::getBool(std::string flag) {
    if (_schema.hasFlag(flag)) {
        return isFlagArgumentMentioned(flag);
    } else {
        throw "Undefined flag";
    }
}

bool Parser::isFlagArgumentMentioned(std::string flag) {
    return _flag_args.find(flag) != _flag_args.end();
}

int Parser::getInt(std::string intname) {
    if (_schema.hasInt(intname)) {
        return intArgValueOrDefault(intname);
    } else {
        throw "Undefined Int";
    }
}

int Parser::intArgValueOrDefault(std::string intname) {
    try {
        return _int_args[intname];
    } catch (std::exception e) {
        return Parser::DEFAULT_INT;
    }
}