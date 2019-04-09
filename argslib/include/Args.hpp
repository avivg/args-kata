#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>

namespace Args
{
    class Schema {
    public:
        void addFlag(std::string flag);
    };

    class Parser {
    public:
        Parser(Schema &schema);
        void parse(int argc, char **argv);
        bool getBool(std::string flag);
    };
}

#endif // __ARGS_HPP__