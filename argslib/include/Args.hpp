#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>
#include <set>
#include <map>

namespace Args
{
    typedef std::string ArgId;
    typedef std::set<ArgId> ArgIdSet;
    
    class Schema {
    public:
        // Add a boolean flag name to the schema.
        void addFlag(const ArgId &flag);
        
        // Get all flags in the schema.
        const ArgIdSet flags() { return _flags; }

        
        // Add an integer name to the schema.
        void addInt(const ArgId &flag);

        // Get all integer names in the schema.
        const ArgIdSet intNames() { return _ints; }


        // Add a string argument name to the schema.
        void addStr(const ArgId &strarg);

        // Get all the string argument names in the schema.
        const ArgIdSet strArgs() {return _strs; }

    private:
        ArgIdSet _flags;
        ArgIdSet _ints;
        ArgIdSet _strs;
    };


    template<typename valT>
    class ArgMap : public std::map<ArgId, valT> {};

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
        bool getBool(const ArgId flag);

        // Return the value given after -<intname> in argv, or DEFAULT_INT if
        // -<intname> was not given.
        // Throws exception if intname was no defined by the parser schema
        int getInt(const ArgId flag);
        static const int DEFAULT_INT = 0;
        
        // Return the value given after -<strarg> in argv, or DEFAULT_STR ("") if
        // -<strarg> was not given.
        // Throws exception if strarg was no defined by the parser schema
        std::string getStr(const ArgId strarg);
        static const std::string DEFAULT_STR; // probably ""

    protected:
        void initFromSchema(Schema &schema);
        void initBooleans(const ArgIdSet &schemaFlags);
        void initIntegers(const ArgIdSet &schemaIntNames);
        void initStrings(const ArgIdSet &schemaStrArgs);

        inline bool isFlagValid(const ArgId &flag);
        inline bool isIntNameValid(const ArgId &intname);
        inline bool isStrArgValid(const ArgId &strarg);
        
    private:
        ArgMap<bool> _flag_args;
        ArgMap<int> _int_args;
        ArgMap<std::string> _str_args;

        template<typename valT>
        static void initArgMapWithDefaultVals(
            ArgMap<valT> &argmap,
            const ArgIdSet &keys,
            const valT initval);
        
        template<typename valT>
        static bool isIdInMap(const ArgMap<valT> argmap, const ArgId id);
    };
}

#endif // __ARGS_HPP__