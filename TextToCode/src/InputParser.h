
#ifndef GUARD
#define GUARD
#include <algorithm>
#include <vector>
#include <string>


class InputParser {
public:
    InputParser(int& argc, char** argv);

    bool optionParamExists(const std::string& option) const;

    /// @author iain
    const std::string& getOptionParam(const std::string& option) const;

    /// @author iain
    bool optionExists(const std::string& option) const;
private:
    std::vector <std::string> tokens;
};


#endif
