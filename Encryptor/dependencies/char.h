#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstddef>
#include <vector>

bool CopyTextFileContent(const std::string& path, std::string& output);

std::vector<char> CopyBinFileContent(const std::string& path);

bool CharToInt(const char* input, int* output, size_t size);

bool IntToChar(int* input, char* output, size_t size);

bool XOR(int key, int* input, int* output, size_t size);