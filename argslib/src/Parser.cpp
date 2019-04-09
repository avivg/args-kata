#include <Args.hpp>

Args::Parser::Parser(Args::Schema &schema) :
    _schema(schema)
{}

void Args::Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        std::string flag_arg = (argv[arg] + 1); // skip '-'
        if (_schema.hasFlag(flag_arg)) {
            _flag_args.insert(flag_arg);
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

bool Args::Parser::getBool(std::string flag) {
    if (_schema.hasFlag(flag))
    {
        return isFlagArgumentMentioned(flag);
    } else {
        throw "Undefined flag";
    }
}

bool Args::Parser::isFlagArgumentMentioned(std::string flag) {
    return _flag_args.find(flag) != _flag_args.end();
}