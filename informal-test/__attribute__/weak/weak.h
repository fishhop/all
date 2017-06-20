#include <iostream>

/*
int __attribute__((weak)) fun(int arg)
{
	std::cout << "weak" << std::endl;
	return 0;
}
*/

int __attribute__((weak)) fun(int arg);