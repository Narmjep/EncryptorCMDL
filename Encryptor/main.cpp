#include <iostream>
#include <ppcm_pgcd.h>
#include <fstream>

#include "MyRSA.h"
#include "InputParser.h"
#include "Ipad.h"

#define PAUSE std::cout << std::endl; \
std::cin.get();

#define N std::cout << std::endl;

void printHelpPage() {
    std::cout << "\n" << "\n";
    std::cout << "##----------------------------------------------Welcome to Narmjeps RSA Encryptor----------------------------------------------##";
    std::cout << "\n" << "\n";
    std::cout << "	how to use: ./Encryptor.exe -f (inputfile name) -o (outputfile name) [options]";
    std::cout << "\n";
    std::cout << "	List of possible options:";
    std::cout << "\n";
    std::cout << "		-c (complexity) : Sets the largest prime that can be used to create the keys.";
    std::cout << "\n";
    std::cout << "		-h : Prints this help message.";
    std::cout << "\n";
    std::cout << "		-o (filename) : Sets the name of the outputfile that will be created. This will overwrite any file with the same name.";
    std::cout << "\n";
    std::cout << "		-r : Runs the program with the step by step explanation.";
    std::cout << "\n";
    std::cout << "		-f (filename) : Sets the input file to be encrypted. The file should be a text file.";
    std::cout << "\n" << "\n";
    std::cout << "##------------------------------------------------------------------------------------------------------------------------------##";
    std::cout << "\n" << "\n";
}

inline bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


int main(int argc, char** argv)
{

    bool r_switch = 0;

    //Switches
    InputParser input(argc, argv);
    if (input.optionExists("-h")) {
        printHelpPage();
        return 0;
    }

    


    r_switch = input.optionExists("-r");




    int* priv = new int[2];
    int* pub = new int[2];
    Keys(1000, pub, priv);
    PAUSE;
    /*
    //Input File
    std::string filename = "help.txt";

    std::ifstream inputFile(filename);
    */
    std::string hi = "Hello";
    size_t size = hi.size() + 1;
    int* buffer = new int[size];

    CharToInt(hi.c_str(), buffer, size);
    
    int* dig = new int[size];
    EncryptMessage(buffer, dig, size, pub);
    N;
    for (int i = 0; i < size-1; i++) {
        std::cout << dig[i] << " / ";
    }
    N;

    int* other_buffer = new int[size];

    DecryptMessage(dig, other_buffer, size, priv);
    
    char* original = new char[size];

    IntToChar(other_buffer, original, size);

    N;
    for (int i = 0; i < size; i++) {
        std::cout << original[i];
    }
    N;
    return 0;
}

