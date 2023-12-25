
#ifndef GUARD
#define GUARD
#include <algorithm>
#include <vector>
#include <string>


class InputParser {
public:
    InputParser(int& argc, char** argv);

    bool OptionParamExists(const std::string& option) const;

    /// @author iain
    const std::string& GetOptionParam(const std::string& option) const;

    /// @author iain
    bool OptionExists(const std::string& option) const;
private:
    std::vector <std::string> tokens;
};


#endif
