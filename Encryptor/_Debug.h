#pragma once

#ifdef _DEBUG
#define print(x) std::cout << x << "\n";

#define PAUSE std::cout << std::endl; \
std::cin.get();

#define NL std::cout << std::endl;

#define END std::cout << std::endl; \
            return 0;
#else
#define print(x);
#endif // _DEBUG

