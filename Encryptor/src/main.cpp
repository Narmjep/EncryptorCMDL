#include <iostream>
#include <myRSA.hpp>
#include <fstream>
#include <time.h>

#include "InputParser.h"
#include "debug.hpp"
#include <char.hpp>

#define DEFAULT_COMPLEXITY 100

typedef char byte_t;

void inline printHelpPage() {
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  RSA DEMO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "" << "\n";
    std::cout << "How to use:" << "\n";
    std::cout << "" << "\n";
    std::cout << "~~Key generation~~" << "\n";
    std::cout << "First you will need a private and a public key. Those can be created using the -k switch." << "\n";         std::cout << "" << "\n";
    std::cout << "CMD: RSA [-priv] [-pub]" << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -c (x) : Set the largest prime number that can be used for the key generation. The default value is 100." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -d : Set the program in decryption mode. When decrypting, use the -k switch." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -e : Set the program in encryption mode. When encrypting, use the -k switch." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -h : Displays this help menu;" << "\n";
    std::cout << "" << "\n";
    std::cout << "         -H : Displays this help menu;" << "\n";
    std::cout << " " << "\n";
    std::cout << "         -i (file) : Set the file that will be read and encrypted / decrypted." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -k (file) : Set the key used in encryption / decryption." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -o (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it can be overwritten using the switch -O." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -priv (file) : Sets the name of the private key file that will be created. The default is 'Priv.key'." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -pub (file) : Sets the name of the public key file that will be created. The default is 'Pub.key'." << "\n";
    std::cout << "" << "\n";
    std::cout << "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
}

inline bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

bool Encrypt(const std::string& filename, std::string outputFile , RSA::Key& key) {

    //Get Input file
    std::fstream inputFile(filename);

    if (inputFile.is_open() == false || exists(filename) == false) {
        printf("Could not open the file!\n");
        return false;
    }

    std::string str_Msg;
    CopyTextFileContent(filename, str_Msg);
    printf("Message to Encrypt:");
    std::cout << str_Msg << "\n";
    const char* chr_msg = str_Msg.c_str();
    inputFile.close();

    //Encrypt
    size_t msgLen = str_Msg.length() + 1;
    int* int_msg = new int[msgLen];
    CharToInt(chr_msg, int_msg, msgLen);
    int* int_encrypted = new int[msgLen];
    RSA::EncryptMessage(int_msg, int_encrypted, msgLen, key);
    


    //Write to File
    std::ofstream file(outputFile , std::ios::out | std::ios::binary);
    for (size_t i = 0; i < msgLen; i++) {
        file.write((char*)&int_encrypted[i], sizeof(int));
    }

    return true;
}

bool Decrypt(const std::string& filename, RSA::Key& priv, std::string outputFile = "") {
    //Get Input file
    std::fstream inputFile(filename, std::ios::in | std::ios::binary);

    if (inputFile.is_open() == false) {
        printf("Could not open the file!");
        return false;
    }

    std::string str_encrypted;
    std::vector<byte_t> buffer = (std::vector<char>)CopyBinFileContent(filename);
    char* chr_encrypted = &buffer[0];
    inputFile.close();  

    //Decrypt
    size_t msgLen = buffer.size() / sizeof(int);
    int* int_decrypted = new int[msgLen];
    RSA::DecryptMessage((int*)chr_encrypted, int_decrypted, msgLen, priv);
    char* str_decrypted = new char[msgLen];
    IntToChar(int_decrypted, str_decrypted, msgLen);

    
    printf("\n----------------------------------------------\nDecrypted Message:\n");
    std::cout << str_decrypted << "\n";

    if (outputFile != "") {
        std::ofstream file(outputFile);
        file << std::string(str_decrypted);
        file.close();
    }

    return true;
}


int main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));

    enum Mode_t { encryption, decryption, keys };
    Mode_t mode = keys;
    

    //Switches
    InputParser input(argc, argv);

    //! Check mode
    
    //-d
    bool d_set = false;
    if (input.OptionExists("-d")) {
        d_set = true;
        mode = decryption;
    }

    //-e
    bool e_set = false;
    if (input.OptionExists("-e")) {
        e_set = true;
        mode = encryption;
    }
    
    //-e and -d
    if (d_set && e_set) {
        std::cout << "Cannot use encryption mode and decryption mode at the same time!";
        return -1;
    }

    //! Options

    //-c
    unsigned int complexity = DEFAULT_COMPLEXITY;
    if (input.OptionExists("-c") && input.OptionParamExists("-c")) {
        complexity = std::stoi(input.GetOptionParam("-c"));
    }

    //-k
    //int key[2];
    std::string keyfile;

    if (mode != keys) {

        if (input.OptionExists("-k") == false) {
            std::cout << "Please set a valid key file! (-k (file))!";
            return -1;
        }

        if (input.OptionParamExists("-k") == false) {
            std::cout << "Please set a valid key file! (-k (file))!";
            return -1;
        }

        keyfile = input.GetOptionParam("-k");

    }

    //-h
    if (input.OptionExists("-h") || input.OptionExists("-H")) {
        printHelpPage();
        return 0;
    }

    //-i
    std::string inputFile;
    if (mode != keys) {
        if (input.OptionExists("-i") == false) {
            std::cout << "Please set a valid input file (-i [file])!!!";
            return -1;
        }

        if (input.OptionParamExists("-i") == false) {
            std::cout << "Please set a valid input file!!!";
            return -1;
        }

        inputFile = input.GetOptionParam("-i");
        if (exists(inputFile) == false) {
            std::cout << "The file '" << inputFile << "' does not exist";
            return -1;
        }
    }

    //-priv
    std::string privKeyName = "./Keys/Priv.key";
    if (input.OptionExists("-priv") && input.OptionParamExists("-priv")) {
        privKeyName = input.GetOptionParam("-priv");
    }

    //pub
    std::string pubKeyName = "./Keys/Pub.key";
    if (input.OptionExists("-pub") && input.OptionParamExists("-pub")) {
        pubKeyName = input.GetOptionParam("-pub");
    }


    //-o
    std::string outputFile = "file.bin";

    if (input.OptionExists("-o") && input.OptionParamExists("-o")) {
        outputFile = input.GetOptionParam("-o");
    }



    //main

    switch (mode) {
    case keys:
        //Keys mode
        std::cout << "Creating keys...\n";
        int priv[2];
        int pub[2];
        RSA::CreateKeys(complexity, pub, priv);
        std::cout << "Public Key: N = " << pub[0] << " | E = " << pub[1];
        std::cout << "\nPrivate Key: N = " << priv[0] << " | D = " << priv[1];
        RSA::WriteKeyFile(pubKeyName, "public", pub[0], pub[1]);
        RSA::WriteKeyFile(privKeyName, "private", priv[0], priv[1]);
        return 0;
        break;
    case encryption:
        {
            //encryption mode
            RSA::Key publicKey(keyfile);
            Encrypt(inputFile, outputFile, publicKey);
            return 0;
            break;
        }
    case decryption:
        {
            //decryption mode
            if (input.OptionParamExists("-o") == false) {
                outputFile = "";
            }
            RSA::Key privateKey(keyfile);
            Decrypt(inputFile, privateKey, outputFile);
            return 0;
            break;
        }

    default:
        throw std::runtime_error("Invalid mode!");
    };

    return 0;
}
    

