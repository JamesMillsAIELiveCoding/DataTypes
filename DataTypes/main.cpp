#include <cstdlib>
#include <iostream>

#include "Array.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using aie::Array;

int main(int argC, char* argV[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Array<int> test = { 1, 2, 3, 4, 5 };

	std::cout << test << "\n";

	test.AddRange({ 6, 7, 8, 9 });

	std::cout << test << "\n";

	test.RemoveAt(3);

	std::cout << test << "\n";

	return EXIT_SUCCESS;
}