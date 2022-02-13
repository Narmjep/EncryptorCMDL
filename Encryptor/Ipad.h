#pragma once
#include <iostream>
#include <string.h>

bool CharToInt(const char* input, int* output, size_t size);

bool IntToChar(int* input, char* output, size_t size);

bool XOR(int key, int* input, int* output, size_t size);