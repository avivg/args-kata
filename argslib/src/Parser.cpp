#include <Args.hpp>

Args::Parser::Parser(Args::Schema &schema) :
    _schema(schema)
{}

void Args::Parser::parse(int argc, const char** argv) {
    for (int arg = 0; arg < argc; arg++) {
        std::string flag_arg = (argv[arg] + 1); // skip '-'
        if (_schema.hasFlag(flag_arg)) {
            _flag_args.push_back(flag_arg);
        } else {
            // Unknown flag
            throw "Invalid Argument";
        }
    }
}

bool Args::Parser::getBool(std::string flag) {
    if (_schema.hasFlag(flag))
    {
        for (auto flag_arg = _flag_args.begin(); flag_arg != _flag_args.end(); flag_arg++) {
            if (flag == *flag_arg) {
                return true;
            }
        }
    } else {
        throw "Undefined flag";
    }
    return false;
}