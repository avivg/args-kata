#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>
#include <set>
#include <map>

namespace Args
{
    class Schema {
    public:
        void addFlag(std::string flag);
        bool hasFlag(std::string flag);

        void addInt(std::string flag);
        bool hasInt(std::string flag);

    private:
        std::set<std::string> _flags;
        std::set<std::string> _ints;
    };

    class Parser {
    public:
        Parser(Schema &schema);
        void parse(int argc, const char **argv);
        
        // Return true if flag is mentioned in argv, false otherwise
        // Throws exception if flag was not defined by the parser schema.
        bool getBool(std::string flag);

        // Return the value given after -<intname> in argv, or DEFAULT_INT if
        // -<intname> was not given.
        // Throws exception if intname was no defined by the parser schema
        int getInt(std::string flag);
        static const int DEFAULT_INT = 0;
        

    protected:
        bool isFlagArgumentMentioned(std::string flag);
        int intArgValueOrDefault(std::string intname);
    
    private:
        Schema& _schema;
        std::set<std::string> _flag_args;
        std::map<std::string, int> _int_args;
    };
}

#endif // __ARGS_HPP__