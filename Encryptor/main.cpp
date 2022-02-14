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
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  RSA DEMO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "" << "\n";
    std::cout << "How to use:" << "\n";
    std::cout << "" << "\n";
    std::cout << "~~Encryption~~" << "\n";
    std::cout << "" << "\n";
    std::cout << "rsa.exe -i (input file) [options]" << "\n";
    std::cout << "" << "\n";
    std::cout << "The program will read a text file, encrypt its content using RSA and then generate a new file with the name 'encrypted.txt'." << "\n";
    std::cout << "" << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -c (x) : Set the largest prime number that can be used for the key generation." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -d : Set the program in decryption mode. When decrypting, use the -p switch." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -h : Displays this help menu;" << "\n";
    std::cout << "" << "\n";
    std::cout << "         -H : Displays this help menu;" << "\n";
    std::cout << " " << "\n";
    std::cout << "         -i (file) : Set the file that will be read and encrypted." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -k : Writes the private and public key to a file with the name 'keys.txt'. If a file with the same name already exists it can be overwritten using the switch -K." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -K : Writes the private and public key to a file with the name 'keys.txt'. If a file with the same name already exists it will be overwritten." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -o (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it can be overwritten using the switch -O." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -O (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it will be overwritten." << "\n";
    std::cout << "         " << "\n";
    std::cout << "" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
}



inline bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


int main(int argc, char** argv)
{

    unsigned int complexity = 100;

    bool r_switch = 0;

    //Switches

    // -h
    InputParser input(argc, argv);
    if (input.optionExists("-h") || input.optionExists("-H")){
        printHelpPage();
        return 0;
    }

    //-c
    
    //-d
    //-i
    //-k
    //-K
    //-o
    //-O





    int* priv = new int[2];
    int* pub = new int[2];
    Keys(complexity, pub, priv);
    PAUSE;
    
    //Input File
    std::string filename = "help.txt";
    std::ifstream inputFile(filename);
    std::stringstream stream;

    stream << inputFile.rdbuf();

    std::string hi = stream.str();
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

