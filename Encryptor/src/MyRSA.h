#pragma once
#include "ppcm_pgcd.h"
#include "Defines.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iomanip>



using json = nlohmann::json;

namespace RSA {

	class Key {
	public:
		std::string type;
		int N;
		int X;
		Key(std::string path);
	};;

	std::vector<int> getMinPrimes(int N);

	bool CreateKeys(size_t range, int* publicKey, int* privateKey);

	int pow_mod(int a, int b, int c);

	bool EncryptMessage(int* input, int* output, size_t size, int* pub);

	bool EncryptMessage(int* input, int* output, size_t size, RSA::Key key);

	bool DecryptMessage(int* input, int* output, size_t size, int* priv);

	bool DecryptMessage(int* input, int* output, size_t size, RSA::Key key);

	//Json
	

	bool WriteKeyFile(std::string path, std::string type, int N, int x);
	
};