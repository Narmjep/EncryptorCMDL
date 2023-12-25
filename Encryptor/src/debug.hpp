#pragma once

#ifdef _DEBUG

#define PAUSE std::cout << std::endl; \
std::cin.get()

#else

#define PAUSE


#endif // _DEBUG

