#include <iostream>
#include <ppcm_pgcd.h>
#include <fstream>
#include <time.h>

#include "MyRSA.h"
#include "InputParser.h"
#include "Ipad.h"

#define PAUSE std::cout << std::endl; \
std::cin.get();

#define N std::cout << std::endl;

#define END std::cout << std::endl; \
            return 0;

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
    std::cout << "         -c (x) : Set the largest prime number that can be used for the key generation. The default values is " << "\n";
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
    srand(time(NULL));

    unsigned int complexity = 100;

    bool r_switch = 0;

    //Switches
    InputParser input(argc, argv);

    //-i

    if (input.optionExists("-i") == false) {
        std::cout << "Please set a valid input file!!!";
        END;
    }

    if (input.optionParamExists("-i") == false) {
        std::cout << "Please set a valid input file!!!";
        END;
    }

    std::string* filename = new std::string;
    *filename = input.getOptionParam("-i");
    if (exists(*filename) == false) {
        std::cout << "The file '" << *filename << "' does not exist";
        END;
    }
    



    //h

    if (input.optionExists("-h") || input.optionExists("-H")){
        printHelpPage();
        END;
    }

    //-c
    
    //-d
    
    //-k
    //-K
    //-o
    //-O





    int* priv = new int[2];
    int* pub = new int[2];
    Keys(complexity, pub, priv);
    PAUSE;
    
    //Input File

    std::ifstream inputFile(*filename);
    std::stringstream stream;

    stream << inputFile.rdbuf();

    std::string hi = stream.str();
    size_t size = hi.size() + 1;
    int* message_intptr = new int[size];

    CharToInt(hi.c_str(), message_intptr, size);
    
    int* encrypted_intptr = new int[size];
    EncryptMessage(message_intptr, encrypted_intptr, size, pub);
   

    int* decrypted_intptr = new int[size];

    DecryptMessage(encrypted_intptr, decrypted_intptr, size, priv);
    
    char* decrypted_charptr = new char[size];

    IntToChar(decrypted_intptr, decrypted_charptr, size);

    N;
    for (int i = 0; i < size; i++) {
        std::cout << decrypted_charptr[i];
    }
    N;
    return 0;
}

