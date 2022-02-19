#include <MyRSA.h>


int test() {
	int priv[2];
	int pub[2];

	unsigned int complexity = 100;

	Keys(complexity, pub , priv);

	return 0;
}

int main() {

	/*spell(getMinPrimes(100), " minprimes");
	spell(getprimes(100), "\n primes");*/

	test();
	
	
}