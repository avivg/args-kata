#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>
#include <set>
#include <map>

namespace Args
{
    class Schema {
    public:
        // Add a boolean flag name to the schema.
        void addFlag(std::string flag);
        
        // Get all flags in the schema.
        std::set<std::string> flags() { return _flags; }

        
        // Add an integer name to the schema.
        void addInt(std::string flag);

        // Get all integer names in the schema.
        std::set<std::string> intNames() { return _ints; }


        // Add a string argument name to the schema.
        void addStr(std::string strarg);

        // Get all the string argument names in the schema.
        std::set<std::string> strArgs() {return _strs; }

    private:
        std::set<std::string> _flags;
        std::set<std::string> _ints;
        std::set<std::string> _strs;
    };

    class Parser {
    public:
        Parser(Schema &schema);

        // Perform parsing over the given arguments.
        // argv is expected to have 'argc' cstrings.
        // Each identifier is expected to have '-' prceding it.
        // Values (for integers and strings) are separated from
        // the identifiers by whitespace (i.e they are in a separate
        // string in argv)
        void parse(int argc, const char **argv);
        
        // Return true if flag is mentioned in argv, false otherwise
        // Throws exception if flag was not defined by the parser schema.
        bool getBool(std::string flag);

        // Return the value given after -<intname> in argv, or DEFAULT_INT if
        // -<intname> was not given.
        // Throws exception if intname was no defined by the parser schema
        int getInt(std::string flag);
        static const int DEFAULT_INT = 0;
        
        // Return the value given after -<strarg> in argv, or DEFAULT_STR ("") if
        // -<strarg> was not given.
        // Throws exception if strarg was no defined by the parser schema
        std::string getStr(std::string strarg);
        static const std::string DEFAULT_STR; // probably ""

    protected:
        void initFromSchema(Schema &schema);
        void initBooleans(std::set<std::string> schemaFlags);
        void initIntegers(std::set<std::string> schemaIntNames);
        void initStrings(std::set<std::string> schemaStrArgs);

        inline bool isFlagValid(std::string flag);
        inline bool isIntNameValid(std::string intname);
        inline bool isStrArgValid(std::string strarg);
        
    private:
        std::map<std::string, bool> _flag_args;
        std::map<std::string, int> _int_args;
        std::map<std::string, std::string> _str_args;
    };
}

#endif // __ARGS_HPP__