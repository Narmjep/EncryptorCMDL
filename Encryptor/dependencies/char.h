#pragma once
#include <iostream>
#include <fstream>
#include <string.h>

bool CopyFileContent(const std::string& path, std::string& output);

bool CharToInt(const char* input, int* output, size_t size);

bool IntToChar(int* input, char* output, size_t size);

bool XOR(int key, int* input, int* output, size_t size);