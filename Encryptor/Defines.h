#pragma once

#ifdef _DEBUG
#define print_db(x) std::cout << x << "\n";

#define PAUSE_db std::cout << std::endl; \
std::cin.get();

#define NL_db std::cout << std::endl;

#define END_db std::cout << std::endl; \
            std::cin.get(); \
            return 0;
#else
#define print(x);
#define PAUSE;

#define NL;

#define END;
#endif // _DEBUG


//All

#define print(x) std::cout << x << "\n";

#define PAUSE std::cout << std::endl; \
std::cin.get();

#define NL std::cout << std::endl;

#define END std::cout << std::endl; \
            std::cout << "\nPress enter to exit..."; \
            std::cin.get(); \
            return 0;


