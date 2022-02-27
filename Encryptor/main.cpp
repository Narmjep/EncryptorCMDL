#include <iostream>
#include "ppcm_pgcd.h"
#include <fstream>
#include <time.h>

#include "MyRSA.h"
#include "InputParser.h"
#include "Char.h"
#include "Defines.h"

#define fori(x) for(int i = 0 ; i < x ; i++)

typedef char byte_t;

void printHelpPage() {
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
    std::cout << "         -d : Set the program in decryption mode. When decrypting, use the -p switch." << "\n";
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
    std::cout << "         -O (file) : Set the name of the outputfile containing the encrypted data, that will be generated. If the file already exists it will be overwritten." << "\n";
    std::cout << "         " << "\n";
    std::cout << "         -priv (file) : Sets the name of the private key file that will be created. The default is 'Priv.key'." << "\n";
    std::cout << "" << "\n";
    std::cout << "         -pub (file) : Sets the name of the public key file that will be created. The default is 'Pub.key'." << "\n";
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

bool Encrypt(const std::string& filename, std::string outputFile , RSA::Key key) {

    //Get Input file
    std::fstream inputFile(filename);

    if (inputFile.is_open() == false || exists(filename) == false) {
        print("Could not open the file!");
        END;
    }

    std::string str_Msg;
    CopyTextFileContent(filename, str_Msg);
    print("Message to Encrypt:");
    print(str_Msg << "\n");
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
    fori(msgLen) {
        file.write((char*)&int_encrypted[i], sizeof(int));
    }
    
    return true;
}

bool Decrypt(const std::string& filename, RSA::Key priv, std::string outputFile = "") {
    //Get Input file
    std::fstream inputFile(filename, std::ios::in | std::ios::binary);

    if (inputFile.is_open() == false) {
        print("Could not open the file!");
        END;
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

    
    print("\n----------------------------------------------\nDecrypted Message:\n");
    print(str_decrypted);

    if (outputFile != "") {
        std::ofstream file(outputFile);
        file << std::string(str_decrypted);
        file.close();
    }

    return true;
}




int main(int argc, char** argv)
{
    srand(time(NULL));

    enum Mode_t { encryption, decryption, keys };
    Mode_t mode = keys;
    

    //Switches
    InputParser input(argc, argv);

    //! Check mode
    
    //-d
    //TODO Decryption Mode
    if (input.optionExists("-d")) {
        mode = decryption;
    }

    //-e
    if (input.optionExists("-e")) {
        mode = encryption;
    }
 
    if (input.optionExists("-e") && input.optionExists("-d")) {
        std::cout << "Cannot use encryption mode and decryption mode at the same time!";
        END;
    }

    //! Options

    //-c
    unsigned int complexity = 100;
    if (input.optionExists("-c") && input.optionParamExists("-c")) {
        complexity = std::stoi(input.getOptionParam("-c"));
    }

    //-k
    int key[2];
    std::string keyfile;

    if (mode != keys) {

        if (input.optionExists("-k") == false) {
            std::cout << "Please set a valid key file! (-k (file))!";
            END;
        }

        if (input.optionParamExists("-k") == false) {
            std::cout << "Please set a valid key file! (-k (file))!";
            END;
        }

        keyfile = input.getOptionParam("-k");

    }

    //-h
    if (input.optionExists("-h") || input.optionExists("-H")) {
        printHelpPage();
        END;
    }

    //-i
    std::string inputFile;
    if (mode != keys) {
        if (input.optionExists("-i") == false) {
            std::cout << "Please set a valid input file (-i [file])!!!";
            END;
        }

        if (input.optionParamExists("-i") == false) {
            std::cout << "Please set a valid input file!!!";
            END;
        }

        inputFile = input.getOptionParam("-i");
        if (exists(inputFile) == false) {
            std::cout << "The file '" << inputFile << "' does not exist";
            END;
        }
    }

    //-priv
    std::string privKeyName = "./Keys/Priv.key";
    if (input.optionExists("-priv") && input.optionParamExists("-priv")) {
        privKeyName = input.getOptionParam("-priv");
    }

    //pub
    std::string pubKeyName = "./Keys/Pub.key";
    if (input.optionExists("-pub") && input.optionParamExists("-pub")) {
        privKeyName = input.getOptionParam("-pub");
    }


    //-o
    std::string outputFile = "EncryptedMsg.bin";
    bool overwrite = false;

    if (input.optionExists("-o") && input.optionParamExists("-o")) {
        outputFile = input.getOptionParam("-o");
    }
    //-O
    if (input.optionExists("-O") && input.optionParamExists("-O")) {
        outputFile = input.getOptionParam("-O");
        overwrite = true;
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
        END;
        break;
    case encryption:
        {
            //encryption mode
            RSA::Key publicKey(pubKeyName);
            Encrypt(inputFile, outputFile, publicKey);
            END;
            break;
        }
    case decryption:
        {
            //decryption mode
            if (input.optionParamExists("-o") == false) {
                outputFile = "";
            }
            RSA::Key privateKey(privKeyName);
            Decrypt(inputFile, privateKey, outputFile);
            END;
            break;
        }
    };

    END;
}
    

