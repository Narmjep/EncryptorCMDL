#include "Ipad.h"

bool CharToInt(const char* input, int* output, size_t size) {


    //try{
    for (int i = 0; i < (int)size; i++) {
        output[i] = (int)input[i];
    }
    //}
    //catch{
        //return false;
    //}
    return true;
}

bool IntToChar(int* input, char* output, size_t size) {


    //try{
    for (int i = 0; i < (int)size; i++) {
        output[i] = (char)input[i];
    }
    //}
    //catch{
        //return false;
    //}
    return true;
}

bool XOR(int key, int* input, int* output, size_t size) {
    for (int i = 0; i < size; i++) {
        int in = input[i];
        int dig = key ^ in;
        output[i] = dig;
    }

    return true;
}
