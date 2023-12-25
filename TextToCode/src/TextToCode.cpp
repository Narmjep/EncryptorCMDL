#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include "InputParser.h"

#define END std::cout << "\nPress enter to exit..."; \
std::cin.get(); \
return 0;

#define END return 0

const std::string functionDeclBegin = "void inline";
const std::string functionDeclEnd = "(){\n";
std::string functionName = "printText";

inline bool exists(const std::string & name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void inline printHelp() {
    std::cout << "" << "\n";
    std::cout << "" << "\n";
    std::cout << "-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << "\n";
    std::cout << "                                         Narmjep's Text To Code" << "\n";
    std::cout << "" << "\n";
    std::cout << "" << "\n";
    std::cout << " How to use:   ttc.exe -f (filename / filepath)" << "\n";
    std::cout << " " << "\n";
    std::cout << " The program will parse text from a file into a C++ void function and write the result to your console where you can copy and paste it" << "\n";
    std::cout << "" << "\n";
    std::cout << " Options:" << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -f (filename / filepath) : Selects the textfile to parse into a C++ function." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -h/-H/--help : displays this help menu." << "\n";
    std::cout << "" << "\n";
    std::cout << "" << "\n";
    std::cout << "-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << "\n";
}

int main(int argc, char** argv) {
    InputParser inputParser(argc, argv);

    if (argc == 1) {
        std::cout << "Missing file argument. Use -f to select an inputfile!";
        END;
    }

    if (inputParser.OptionExists("-f") == false) {
        if (inputParser.OptionExists("-h")) {
            printHelp();
            END;
        }

        std::cout << "Missing file argument. Use -f to select an inputfile!";
        END;
    }

    if (inputParser.OptionParamExists("-f") == false) {
        std::cout << "Missing file argument. Use -f to select an inputfile!";
        END;
    }

    const char* filepath = (inputParser.GetOptionParam("-f")).c_str();
    

    std::cout << "File: " << filepath << "\n";
    
    if (inputParser.OptionExists("-n")) {
        if (inputParser.OptionParamExists("-n")) {

        }
    }

    //Check if file exists
    if (exists(filepath) == false) {
        std::cout << "File not found! \n \n";
        END;
    }

    //Get File Name


    if (inputParser.OptionExists("-n") && inputParser.OptionParamExists("-n")) {
        functionName = inputParser.GetOptionParam("-n");
    }
    

    //Read File
    std::ifstream inputfile(filepath);

    std::string text;
    std::cout << "\n" << functionDeclBegin << functionName << functionDeclEnd;
    while (std::getline(inputfile, text)) {
        std::replace(text.begin(), text.end(), (char)34, (char)39);
        std::cout << "\t std::cout << " << (char)34 << text << (char)34 << "<<" << (char)34 << (char)92 << 'n' << (char)34 << ";" << std::endl;
    }
    std::cout << "}" << "\n";

    inputfile.close();
    

    return 0;

}


