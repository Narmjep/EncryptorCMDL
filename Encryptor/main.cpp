#include <iostream>
#include "ppcm_pgcd.h"
#include <fstream>
#include <time.h>

#include "MyRSA.h"
#include "InputParser.h"
#include "Char.h"
#include "_Debug.h"

#define fori(x) for(int i = 0 ; i < x ; i++)

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

bool Encrypt(const std::string& filename, int* pub) {

    //Get Input file
    std::fstream inputFile(filename);

    if (inputFile.is_open() == false) {
        print("Could not open the file!");
        END;
    }

    std::string str_Msg;
    CopyTextFileContent(filename, str_Msg);
    print("Message to Encrypt:");
    print(str_Msg << "\n");
    const char* msg = str_Msg.c_str();
    inputFile.close();

    //Encrypt
    size_t msgLen = str_Msg.length() + 1;
    print("Length");
    print(msgLen);
    NL;
    int* int_msg = new int[msgLen];
    CharToInt(msg, int_msg, msgLen);
    int* int_encrypted = new int[msgLen];
    RSA::EncryptMessage(int_msg, int_encrypted, msgLen, pub);
    


    //Write to File
    std::ofstream outputFile("EncryptedMsg.txt" , std::ios::out | std::ios::binary); //TODO save in folder
    //? outputFile << std::string(str_encrypted); //? Save as char !!!
    fori(msgLen) {
        outputFile.write((char*)&int_encrypted[i], sizeof(int_encrypted[i]));
    }
    print("\n Encrypted:");
    print("STRLEN: " << strlen((char*)int_encrypted));
    print(std::string((char*)&int_encrypted[0]));


        return true;
}

bool Decrypt(const std::string& filename, int* priv) {
    //Get Input file
    std::fstream inputFile(filename, std::ios::in | std::ios::binary);

    if (inputFile.is_open() == false) {
        print("Could not open the file!");
        END;
    }

    std::string str_encrypted;
    std::vector<char> buffer = CopyBinFileContent(filename);
    char* chr_encrypted = &buffer[0];
    str_encrypted = std::string(chr_encrypted);
    print("Message to decrypt:");
    print(str_encrypted);
    print((int)str_encrypted[0]);
    inputFile.close();

    //Decrypt

    size_t msgLen = buffer.size();
    print("Length");
    print(msgLen);
    NL;
    int* int_decrypted = new int[msgLen];
    RSA::DecryptMessage((int*)chr_encrypted, int_decrypted, msgLen, priv);
    char* str_decrypted = new char[msgLen];
    IntToChar(int_decrypted, str_decrypted, msgLen);

    //Write to File
    std::ofstream outputFile("EncryptedMsg.txt"); //TODO save in folder
    outputFile << std::string(str_decrypted);
    print("\n decrypted:");
    print(str_decrypted);

    return true;
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

    if (input.optionExists("-h") || input.optionExists("-H")) {
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
    RSA::Keys(complexity, pub, priv);
    PAUSE;
    
    //Testing

    Encrypt("example.txt", pub);
    PAUSE;
    NL;
    print("---------------------------------------------------------------");
    NL;
    NL;
    Decrypt("EncryptedMsg.txt", priv);
    END;
}
    

