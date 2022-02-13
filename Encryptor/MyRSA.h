#pragma once
#include "ppcm_pgcd.h"
#include <vector>
#include <time.h>

typedef long long int TYPE;

std::vector<int> getMinPrimes(int N);

bool Keys(size_t range, int* publicKey, int* privateKey);

int pow_mod(int a, int b, int c);

bool EncryptMessage(int* input, int* output, size_t size, int* pub);

bool DecryptMessage(int* input, int* output, size_t size, int* priv);