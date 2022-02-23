#include <iostream>
#include <ppcm_pgcd.h>
#include <fstream>
#include <time.h>

#include "MyRSA.h"
#include "InputParser.h"
#include "Ipad.h"
#include "_Debug.h"



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
    std::cout << "The program will read a text file, encrypt its content using RSA and then generate a new file with the name 'encrypted.txt'. Additionally two json files will be created containing the public and the private key." << "\n";
    std::cout << "" << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -c (x) : Set the largest prime number that can be used for the key generation. The default value is 100." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -d : Set the program in decryption mode. When decrypting, use the -p switch." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -h : Displays this help menu;" << "\n";
    std::cout << "" << "\n";
    std::cout << "         -H : Displays this help menu;" << "\n";
    std::cout << " " << "\n";
    std::cout << "         -i (file) : Set the file that will be read and encrypted." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -k (private key file name);(public key file name) : Set the name of the private and public key file. If the files already exist they can be overwritten using the switch -K." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -K (private key file name);(public key file name) : Set the name of the private and public key file. If the files already exist they will be overwritten." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -o (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it can be overwritten using the switch -O." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -O (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it will be overwritten." << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -p (Keyfile) : Set the key used during encryption / decryption. If this option isn't used when encrypting, the program will automatically create generate a key pair." << "\n";
    std::cout << "" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
}

inline bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

std::string keyFolderPath = "./Keys";




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

    if (input.optionExists("-c") && input.optionParamExists("-c")) {
        complexity = std::stoi(input.getOptionParam("-c"));
    }
    
    //-d

    bool decryptionMode = false;

    if (input.optionExists("-d")) {
        decryptionMode = true;
    }
    
    //-k & -K
    


    //-o
    //-O

    //Get Keys
    int* priv = new int[2];
    int* pub = new int[2];
    Keys(complexity, pub, priv);
    PAUSE;

    //Get Input file
    std::fstream inputFile(*filename);
    std::string str_Msg;

    if (inputFile.is_open() == false) {
        print("Could not open the file!");
        END;
    }
    inputFile >> str_Msg; //? wtf
    print("Message to Encrypt:");
    print(str_Msg);
    inputFile.close();

    //Encrypt
    const char* msg = str_Msg.c_str();
    const int msgLen = str_Msg.length()+1;
    int* int_msg = new int[msgLen];
    CharToInt(msg, int_msg, msgLen);
    int* int_encrypted = new int[msgLen];
    EncryptMessage(int_msg,int_encrypted,msgLen,pub);
    char* str_encrypted = new char[msgLen];
    IntToChar(int_encrypted, str_encrypted, msgLen);

    //Write to File
    std::ofstream outputFile("./Encrypted/EncryptedMsg.txt");
    outputFile << std::string(str_encrypted);

    END;


    //----------------------------------------------------------------------------------------------

    ////Test Program

    //INT* PRIV = NEW INT[2];
    //INT* PUB = NEW INT[2];
    //KEYS(COMPLEXITY, PUB, PRIV);
    //PAUSE;
    //
    ////Input File

    //std::ifstream inputFile(*filename);
    //std::stringstream stream;

    //stream << inputFile.rdbuf();

    //std::string hi = stream.str();
    //size_t size = hi.size() + 1;
    //int* message_intptr = new int[size];

    //CharToInt(hi.c_str(), message_intptr, size);
    //
    //int* encrypted_intptr = new int[size];
    //EncryptMessage(message_intptr, encrypted_intptr, size, pub);
   

    //int* decrypted_intptr = new int[size];

    //DecryptMessage(encrypted_intptr, decrypted_intptr, size, priv);
    //
    //char* decrypted_charptr = new char[size];

    //IntToChar(decrypted_intptr, decrypted_charptr, size);

    //NL;
    //for (int i = 0; i < size; i++) {
    //    std::cout << decrypted_charptr[i];
    //}
    //NL;


    return 0;
}

