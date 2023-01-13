#include <iostream>
#include <fstream>
#include <MyRSA.h>
#include <vector>
#include <string>

#define DEFAULT_RANGE 1024
#define START 7

void writeToFile(std::ofstream& file, int number){
    file.write(reinterpret_cast<char*>(&number) , sizeof(number));
}

int main(int argc, char** argv){
    int range = DEFAULT_RANGE;
    try{
        if(argc > 1) range = std::stoi(argv[1]);
    } catch(...){
        std::cerr << "Invalid argument.";
    }
    RSA::Optimization::WritePrimeDecompositionToFile("data.bin", START, range);
}