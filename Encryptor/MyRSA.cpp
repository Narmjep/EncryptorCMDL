#include "MyRSA.h"

#include "_Debug.h"





std::vector<int> RSA::getMinPrimes(int N) {
    std::vector<int> returnlist = getprimes(N);
    for (int i = 0; i <= 4; i++) {
        returnlist.erase(returnlist.begin());
    }


    return returnlist;
}

bool RSA::Keys(size_t range, int* publicKey, int* privateKey) {

    int p;
    int q;
    int N;
    int k;
    //int k = (p-1)*(q-1);

    int x;

    //Keys
    int pub[2];
    int priv[2];

    std::vector<int> dval;
    int d = 0;
    std::vector<int> eval;
    int e = 0;



    //Get p and q
    std::vector<int> minPrimes = getMinPrimes(range);
    x = rand() % minPrimes.size();
    p = minPrimes[x];
    q = p;

    while (q == p) {
        x = rand() % minPrimes.size();
        q = minPrimes[x];
    }





    //Get N
    N = p * q;
    //Get k
    k = (p - 1) * (q - 1);


    //Get e
    std::vector<int> eprimes;
    std::vector<int> kprimes;
    std::vector<int> evalues;
    kprimes = decompose(k);


    for (int i = 7; i < range; i++) {
        eprimes = decompose(i);
        if (checkIfCommonInt(kprimes, eprimes) == false) {
            //e = i;
            //break;
            evalues.push_back(i);
            
        }
    }

    spell(evalues, "possible e values");

    int random = rand() % evalues.size();

    e = evalues[random];



    //Get D

    std::vector<int> emult = multiples(e, k);

    for (int i = 0; i <= k; i++) {
        if (emult[i] % k == 1) {
            d = i;
            break;
        }
    }





    //Generate Keys
    pub[0] = N;
    pub[1] = e;

    priv[0] = N;
    priv[1] = d;


    std::string keys = std::to_string(pub[0]) + "," + std::to_string(pub[1]) + "," + std::to_string(priv[0]) + "," + std::to_string(priv[1]);

#ifdef _DEBUG
    std::cout << "Public Key: " << std::to_string(pub[0]) + "," + std::to_string(pub[1]);
    std::cout << "Private Key: " << std::to_string(priv[0]) + "," + std::to_string(priv[1]);
#endif

    privateKey[0] = priv[0];
    privateKey[1] = priv[1];
    std::cout << std::endl;
    publicKey[0] = pub[0];
    publicKey[1] = pub[1];


    return true;
}


int RSA::pow_mod(int m, int e, int n) {
    int x = m;
    for (int i = 1; i < e; i++) {
        x = (x * m) % n;
    }
    return x;
}

bool RSA::EncryptMessage(int* input , int* output, size_t size, int* pub) {

    int c;
    int m;
    int n = pub[0];
    int e = pub[1];
    
    print("Begin encryption:");
    NL;
    for (int i = 0; i < size; i++) {

        m = input[i];
        //std::cout << "m: " << m << "\n";
        c = pow_mod(m, e, n);
        output[i] = c;
        print(m << " >> " << c);
    }
    print("End encryption");

    return true;
}

bool RSA::DecryptMessage(int* input, int* output, size_t size, int* priv) {

    int c;
    int m;
    int n = priv[0];
    print("n: " << n);
    int d = priv[1];
    print("d: " << d);

    print("Begin decryption:");
    NL;
    for (int i = 0; i < size; i++) {

        c = input[i];
        m = pow_mod(c, d, n);
        output[i] = m;
        print(m << " >> " << c);
    }
    print("End decryption");

    return true;
}
