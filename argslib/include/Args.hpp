#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>
#include <vector>

namespace Args
{
    class Schema {
    public:
        void addFlag(std::string flag);
        bool hasFlag(std::string flag);

    private:
        std::vector<std::string> _flags;
    };

    class Parser {
    public:
        Parser(Schema &schema);
        void parse(int argc, const char **argv);
        bool getBool(std::string flag);

    private:
        Schema& _schema;
        std::vector<std::string> _flag_args;
    };
}

#endif // __ARGS_HPP__