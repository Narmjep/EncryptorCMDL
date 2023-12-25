#include "inputParser.h"



    InputParser::InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    const std::string& InputParser::GetOptionParam(const std::string& option) const {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }

    bool InputParser::OptionParamExists(const std::string& option) const {
        if (GetOptionParam(option) == "") return false;
        return true;
    }

    /// @author iain
    bool InputParser::OptionExists(const std::string& option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
    }


